#include "../utils/readFile.h"
#include <algorithm>
#include <iostream>
#include <set>

void combineHelper(const std::vector<int> &nums, unsigned int k, int start,
                   std::vector<int> &current,
                   std::vector<std::vector<int>> &result) {
  if (current.size() == k) {
    result.push_back(current);
    return;
  }

  for (unsigned int i = start; i < nums.size(); ++i) {
    current.push_back(nums[i]);
    combineHelper(nums, k, i + 1, current, result);
    current.pop_back();
  }
}

std::vector<std::vector<int>> combinations(const std::vector<int> &nums,
                                           int k) {
  std::vector<std::vector<int>> result;
  std::vector<int> current;
  combineHelper(nums, k, 0, current, result);
  return result;
}

std::vector<int> difference(const std::vector<int> &packages,
                            const std::vector<int> &combo) {
  std::vector<int> remaining = packages;
  std::multiset<int> comboSet(combo.begin(), combo.end());

  auto it = remaining.begin();
  while (it != remaining.end()) {
    auto found = comboSet.find(*it);
    if (found != comboSet.end()) {
      comboSet.erase(found);
      it = remaining.erase(it);
    } else {
      ++it;
    }
  }

  return remaining;
}

int sum(const std::vector<int> &nums) {
  int total = 0;
  for (auto num : nums) {
    total += num;
  }
  return total;
}

unsigned long long calculateQuantumEntanglement(const std::vector<int> &nums) {
  unsigned long long product = 1;
  for (auto num : nums) {
    product *= num;
  }
  return product;
}

std::vector<int> getOptimalCombination(const std::vector<int> &nums,
                                       int groups) {
  std::vector<int> result;
  unsigned long long minQuantumEntanglement = ULLONG_MAX;

  for (unsigned int i = 1; i < nums.size() - 2; i++) {
    result.clear();
    minQuantumEntanglement = ULLONG_MAX;

    auto sizeCombinations = combinations(nums, i);

    for (auto sizeCombination : sizeCombinations) {
      auto remainingNumbers = difference(nums, sizeCombination);

      float remainingSum = sum(remainingNumbers) / groups;
      float sizeCombinationSum = sum(sizeCombination);

      if (remainingSum == sizeCombinationSum) {
        auto quantumEntanglement =
            calculateQuantumEntanglement(sizeCombination);
        if (quantumEntanglement < minQuantumEntanglement) {
          minQuantumEntanglement = quantumEntanglement;
          result = sizeCombination;
        }
      }
    }

    if (!result.empty()) {
      return result;
    }
  }

  return {};
}

void part1(std::vector<int> lines) {
  auto result = getOptimalCombination(lines, 2);
  std::cout << calculateQuantumEntanglement(result) << std::endl;
}

void part2(std::vector<int> lines) {
  auto result = getOptimalCombination(lines, 3);
  std::cout << calculateQuantumEntanglement(result) << std::endl;
}

std::vector<int> getPackages(const std::string &filename) {
  auto lines = readFileLines(filename);
  std::vector<int> result;
  for (auto line : lines)
    result.push_back(std::stoi(line));

  std::sort(result.begin(), result.end(), std::greater<int>());

  return result;
}

int main() {
  auto lines = getPackages("./24/input.txt");

  part1(lines);
  part2(lines);

  return 0;
}