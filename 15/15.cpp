#include <iostream>
#include <map>
#include <tuple>
#include "../utils/readFile.h"
#include "../utils/split.h"

std::vector<std::vector<int>> parseLines(const std::vector<std::string>& lines) {
  std::vector<std::vector<int>> parsedLines;

  for(auto line : lines){
    std::vector<std::string> parts = split(line, ' ');

    int capacity = std::stoi(parts[2]);
    int durability = std::stoi(parts[4]);
    int flavor = std::stoi(parts[6]);
    int texture = std::stoi(parts[8]);
    int calories = std::stoi(parts[10]);

    std::vector<int> ingredient = {capacity, durability, flavor, texture, calories};
    parsedLines.push_back(ingredient);
  }

  return parsedLines;
}

int calculateScore(std::vector<std::vector<int>> ingredients, std::vector<int> ingredientQuantities, int maxQuantity, int maxCalories) {  
  int remainingAmount = maxQuantity;
  for(int quantity : ingredientQuantities) remainingAmount -= quantity;
  
  if(ingredientQuantities.size() == ingredients.size()){
    if(remainingAmount != 0) return 0;

    std::vector<int> propertyScores(5, 0);
    
    for(unsigned int i = 0; i < ingredientQuantities.size(); i++){
      int ingredientQuantity = ingredientQuantities[i];

      for(unsigned int j = 0; j < 5; j++){
        propertyScores[j] += ingredients[i][j] * ingredientQuantity;
      }
    }
    
    for(unsigned int i = 0; i < propertyScores.size(); i++){
      if(propertyScores[i] < 0) propertyScores[i] = 0;
    }
    
    int totalScore = 1;
    for(unsigned int i = 0; i < 4; i++){
      totalScore *= propertyScores[i];
    }

    int totalCalories = 0;
    for(unsigned int i = 0; i < ingredientQuantities.size(); i++){
      totalCalories += ingredients[i][4] * ingredientQuantities[i];
    }
    if(maxCalories != -1 && totalCalories != maxCalories) return 0;

    return totalScore;
  }

  int bestScore = 0;
  for(int i = 0; i <= remainingAmount; i++){
    std::vector<int> newQuantities = ingredientQuantities;
    newQuantities.push_back(i);
    int score = calculateScore(ingredients, newQuantities, maxQuantity, maxCalories);
    if(score > bestScore) bestScore = score;
  }

  return bestScore;
}

int main(){
  auto lines = readFileLines("15/input.txt");

  auto parsedLines = parseLines(lines);

  int part1 = calculateScore(parsedLines, {}, 100, -1);
  std::cout << part1 << std::endl;

  int part2 = calculateScore(parsedLines, {}, 100, 500);
  std::cout << part2 << std::endl;

  return 0;
}