#include "../utils/readFile.h"
#include "../utils/split.h"
#include <iostream>
#include <map>

typedef std::tuple<std::string, int, int, int, int, int, int, int> Spell;

int PLAYER_WINS = 1;
int BOSS_WINS = 0;
int NOT_FINISHED = -1;

struct Character {
  int hitPoints;
  int damage;
  int armor;
  int mana;
};

// name, cost, damage, heal, duration, extra armor, damage, recovered mana
std::vector<Spell> spells = {{"Magic Missile", 53, 4, 0, 0, 0, 0, 0},
                             {"Drain", 73, 2, 2, 0, 0, 0, 0},
                             {"Shield", 113, 0, 0, 6, 7, 0, 0},
                             {"Poison", 173, 0, 0, 6, 0, 3, 0},
                             {"Recharge", 229, 0, 0, 5, 0, 0, 101}};

int play(Character &player, Character &enemy, std::vector<Spell> &effects,
         int selectedSpell, bool hardMode) {
  int characterArmor = player.armor;

  // Apply effects
  if (hardMode) {
    player.hitPoints -= 1;
    if (player.hitPoints <= 0) {
      return BOSS_WINS;
    }
  }

  for (unsigned int i = 0; i < effects.size(); i++) {
    auto effect = effects[i];

    int extraArmor = std::get<5>(effect);
    int damage = std::get<6>(effect);
    int mana = std::get<7>(effect);

    characterArmor += extraArmor;
    enemy.hitPoints -= damage;
    player.mana += mana;

    // Reduce duration
    int duration = std::get<4>(effect) - 1;
    effects[i] = std::make_tuple(std::get<0>(effect), std::get<1>(effect),
                                 std::get<2>(effect), std::get<3>(effect),
                                 duration, std::get<5>(effect),
                                 std::get<6>(effect), std::get<7>(effect));
  }

  if (enemy.hitPoints <= 0) {
    return PLAYER_WINS;
  }

  // Remove finished effects
  for (int i = effects.size() - 1; i >= 0; i--) {
    auto effect = effects[i];
    if (std::get<4>(effect) <= 0) {
      effects.erase(effects.begin() + i);
    }
  }

  // Run character action
  auto spell = spells[selectedSpell];
  std::string selectedName = std::get<0>(spells[selectedSpell]);
  for (const auto &eff : effects) {
    if (std::get<0>(eff) == selectedName && std::get<4>(eff) > 0) {
      return BOSS_WINS; // Invalid move
    }
  }

  if (std::get<1>(spell) > player.mana) {
    return BOSS_WINS;
  }

  int cost = std::get<1>(spell);
  player.mana -= cost;

  int damage = std::get<2>(spell);
  enemy.hitPoints -= damage;

  if (enemy.hitPoints <= 0) {
    return PLAYER_WINS;
  }

  int heal = std::get<3>(spell);
  player.hitPoints += heal;

  int duration = std::get<4>(spell);
  if (duration > 0) {
    effects.push_back(spell);
  }

  characterArmor = player.armor;

  // Apply effects
  for (unsigned int i = 0; i < effects.size(); i++) {
    auto effect = effects[i];

    int extraArmor = std::get<5>(effect);
    int damage = std::get<6>(effect);
    int mana = std::get<7>(effect);

    characterArmor += extraArmor;
    enemy.hitPoints -= damage;
    player.mana += mana;

    // Reduce duration
    int duration = std::get<4>(effect) - 1;
    effects[i] = std::make_tuple(std::get<0>(effect), std::get<1>(effect),
                                 std::get<2>(effect), std::get<3>(effect),
                                 duration, std::get<5>(effect),
                                 std::get<6>(effect), std::get<7>(effect));
  }

  if (enemy.hitPoints <= 0) {
    return PLAYER_WINS;
  }

  // Remove finished effects
  for (int i = effects.size() - 1; i >= 0; i--) {
    auto effect = effects[i];
    if (std::get<4>(effect) <= 0) {
      effects.erase(effects.begin() + i);
    }
  }

  // Boss hits
  int bossDamage = std::max(1, enemy.damage - characterArmor);
  player.hitPoints -= bossDamage;

  if (player.hitPoints <= 0) {
    return BOSS_WINS;
  }

  return NOT_FINISHED;
}

std::vector<std::vector<Spell>> playLoop(Character &player, Character &enemy,
                                         std::vector<Spell> effects,
                                         std::vector<Spell> usedSpells,
                                         bool hardMode = false) {
  if (usedSpells.size() > 10) {
    return {}; // Too many spells used, stop recursion
  }

  std::vector<std::vector<Spell>> winningSpells;

  for (unsigned int i = 0; i < spells.size(); i++) {
    auto characterClone = player;
    auto enemyClone = enemy;
    auto effectsCopy = std::vector<Spell>(effects);
    auto result = play(characterClone, enemyClone, effectsCopy, i, hardMode);
    if (result == PLAYER_WINS) {
      auto usedSpellsCopy = std::vector<Spell>(usedSpells);
      usedSpellsCopy.push_back(spells[i]);
      winningSpells.push_back(usedSpellsCopy);
    } else if (result == BOSS_WINS) {
      // just continue this loop
    } else if (result == NOT_FINISHED) {
      auto usedSpellsCopy = std::vector<Spell>(usedSpells);
      usedSpellsCopy.push_back(spells[i]);
      auto winningResults = playLoop(characterClone, enemyClone, effectsCopy,
                                     usedSpellsCopy, hardMode);
      for (auto winningResult : winningResults) {
        winningSpells.push_back(winningResult);
      }
    }
  }

  return winningSpells;
}

Character getBoss(std::string filename) {
  auto lines = readFileLines(filename);
  int hp = std::stoi(split(lines[0], ' ').back());
  int damage = std::stoi(split(lines[1], ' ').back());
  return {hp, damage, 0, 0};
}

void playMode(Character player, Character boss, bool hardMode) {
  auto results = playLoop(player, boss, {}, {}, hardMode);
  int minMana = INT_MAX;
  for (auto &path : results) {
    int manaUsed = 0;
    for (auto &spell : path) {
      manaUsed += std::get<1>(spell);
    }
    if (manaUsed < minMana)
      minMana = manaUsed;
  }
  std::cout << minMana << std::endl;
}

int main() {
  Character player = {50, 0, 0, 500};
  Character boss = getBoss("./22/input.txt");

  playMode(player, boss, false);
  playMode(player, boss, true);

  return 0;
}