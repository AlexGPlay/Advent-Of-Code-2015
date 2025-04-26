#include <iostream>
#include "../utils/readFile.h"

std::vector<int> getContainers(const std::string& filename) {
    std::vector<int> containers;

    auto lines = readFileLines(filename);
    for(auto line : lines){
      containers.push_back(std::stoi(line));
    }

    return containers;
}

std::vector<std::vector<int>> getCombinations(const std::vector<int>& containers, int target) {
    std::vector<std::vector<int>> combinations;
    int n = containers.size();

    for (int i = 0; i < (1 << n); ++i) {
        std::vector<int> combination;
        int sum = 0;

        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                combination.push_back(containers[j]);
                sum += containers[j];
            }
        }

        if (sum == target) {
            combinations.push_back(combination);
        }
    }

    return combinations;
}

void part1(std::vector<int> lines){
  auto combinations = getCombinations(lines, 150);
  std::cout << combinations.size() << std::endl;
}

void part2(std::vector<int> lines){
  auto combinations = getCombinations(lines, 150);

  std::vector<int> minimums;
  unsigned int minSize = INT_MAX;

  for(auto combination : combinations){
    if(combination.size() < minSize){
      minSize = combination.size();
      minimums.clear();
      minimums.push_back(combination.size());
    } else if(combination.size() == minSize){
      minimums.push_back(combination.size());
    }
  }

  std::cout << minimums.size() << std::endl;
}

int main(){
  auto lines = getContainers("17/input.txt");

  part1(lines);
  part2(lines);

  return 0;
}