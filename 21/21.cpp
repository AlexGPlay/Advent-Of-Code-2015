#include "../utils/readFile.h"
#include "../utils/split.h"
#include <iostream>
#include <map>

struct Item {
  std::string name;
  std::string category;
  int cost;
  int damage;
  int armor;
};

struct Character {
  int hitPoints;
  int damage;
  int armor;
  std::vector<Item> items;
};

std::vector<Item> getAvailableItems() {
  return {
      {"Dagger", "weapon", 8, 4, 0},     {"Shortsword", "weapon", 10, 5, 0},
      {"Warhammer", "weapon", 25, 6, 0}, {"Longsword", "weapon", 40, 7, 0},
      {"Greataxe", "weapon", 74, 8, 0},

      {"Leather", "armor", 13, 0, 1},    {"Chainmail", "armor", 31, 0, 2},
      {"Splintmail", "armor", 53, 0, 3}, {"Bandedmail", "armor", 75, 0, 4},
      {"Platemail", "armor", 102, 0, 5},

      {"Defense +1", "ring", 20, 0, 1},  {"Damage +1", "ring", 25, 1, 0},
      {"Defense +2", "ring", 40, 0, 2},  {"Damage +2", "ring", 50, 2, 0},
      {"Defense +3", "ring", 80, 0, 3},  {"Damage +3", "ring", 100, 3, 0},
  };
}

Character getEnemy(std::string filename) {
  auto lines = readFileLines(filename);
  int hp = std::stoi(split(lines[0], ' ').back());
  int damage = std::stoi(split(lines[1], ' ').back());
  int armor = std::stoi(split(lines[2], ' ').back());

  return {hp, damage, armor, {}};
}

bool play(Character player, Character enemy) {
  for (auto item : player.items) {
    player.damage += item.damage;
    player.armor += item.armor;
  }

  for (auto item : enemy.items) {
    enemy.damage += item.damage;
    enemy.armor += item.armor;
  }

  while (true) {
    enemy.hitPoints -= std::max(1, player.damage - enemy.armor);
    if (enemy.hitPoints <= 0)
      return true;

    player.hitPoints -= std::max(1, enemy.damage - player.armor);
    if (player.hitPoints <= 0)
      return false;
  }
}

std::vector<std::vector<Item>>
getCombinationsWithRings(std::vector<Item> availableItems,
                         std::vector<Item> weaponsAndArmor) {
  std::vector<std::vector<Item>> combinations;
  // There's the possibility of not having rings at all, so that's the
  // combinaton itself
  combinations.push_back(weaponsAndArmor);

  // Now we can have 1 ring
  for (auto ring : availableItems) {
    if (ring.category == "ring") {
      std::vector<Item> combination = weaponsAndArmor;
      combination.push_back(ring);
      combinations.push_back(combination);
    }
  }

  // Now we can have 2 rings, but we can't have 2 rings of the same type
  for (size_t i = 0; i < availableItems.size(); i++) {
    if (availableItems[i].category == "ring") {
      for (size_t j = i + 1; j < availableItems.size(); j++) {
        if (availableItems[j].category == "ring") {
          std::vector<Item> combination = weaponsAndArmor;
          combination.push_back(availableItems[i]);
          combination.push_back(availableItems[j]);
          combinations.push_back(combination);
        }
      }
    }
  }

  return combinations;
}

std::vector<std::vector<Item>>
getCombinationsWithArmor(std::vector<Item> availableItems,
                         std::vector<Item> weapons) {
  std::vector<std::vector<Item>> combinations;

  // Armor is optional so let's start with no armor
  auto ringCombinations = getCombinationsWithRings(availableItems, weapons);
  for (auto combination : ringCombinations) {
    combinations.push_back(combination);
  }

  // Now let's add one armor
  for (auto armor : availableItems) {
    if (armor.category == "armor") {
      std::vector<Item> combination = weapons;
      combination.push_back(armor);

      auto ringCombinations =
          getCombinationsWithRings(availableItems, combination);
      for (auto combination : ringCombinations) {
        combinations.push_back(combination);
      }
    }
  }

  return combinations;
}

std::vector<std::vector<Item>>
getCombinationsWithWeapons(std::vector<Item> availableItems) {
  std::vector<std::vector<Item>> combinations;
  for (auto weapon : availableItems) {
    if (weapon.category == "weapon") {
      std::vector<std::vector<Item>> combination =
          getCombinationsWithArmor(availableItems, {weapon});
      for (auto comb : combination) {
        combinations.push_back(comb);
      }
    }
  }
  return combinations;
}

std::vector<std::vector<Item>>
getCombinations(std::vector<Item> availableItems) {
  return getCombinationsWithWeapons(availableItems);
}

std::tuple<int, int> playAllCombinations(std::vector<Item> availableItems,
                                         Character player, Character enemy) {
  auto combinations = getCombinations(availableItems);

  int minWinningCost = INT_MAX;
  int maxLosingCost = 0;

  for (auto combination : combinations) {
    int cost = 0;
    for (auto item : combination) {
      cost += item.cost;
    }

    player.items = combination;
    if (play(player, enemy)) {
      minWinningCost = std::min(minWinningCost, cost);
    } else {
      maxLosingCost = std::max(maxLosingCost, cost);
    }
  }
  return {minWinningCost, maxLosingCost};
}

int main() {
  Character player = {100, 0, 0, {}};
  Character enemy = getEnemy("./21/input.txt");

  auto results = playAllCombinations(getAvailableItems(), player, enemy);

  std::cout << std::get<0>(results) << std::endl;
  std::cout << std::get<1>(results) << std::endl;

  return 0;
}