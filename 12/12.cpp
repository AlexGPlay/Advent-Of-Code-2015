#include <iostream>
#include <regex>
#include <tuple>
#include "../utils/readFile.h"

std::vector<int> findAllInts(std::string input){
  std::vector<int> result;
  std::regex intRegex("-?\\d+");
  std::smatch match;

  while (std::regex_search(input, match, intRegex)) {
    result.push_back(std::stoi(match[0]));
    input = match.suffix().str();
  }

  return result;
}

int sum(std::vector<int> input){
  int result = 0;
  for (int i : input) {
    result += i;
  }
  return result;
}

void part1(std::string input){
  std::vector<int> numbers = findAllInts(input);
  int result = sum(numbers);
  std::cout << result << std::endl;
}

// Part 2
std::tuple<int, int> balanceRed(std::string input, std::tuple<char, int> start){
  std::vector<char> chars = {'{'};
  
  int i = std::get<1>(start) + 1;
  while(chars.size() != 0){
    if(input[i] == '{' || input[i] == '[') chars.push_back(input[i]);
    else if(input[i] == '}' || input[i] == ']') chars.pop_back();
    i++;
  }

  return {std::get<1>(start), i};
}

std::vector<std::tuple<int, int>> findPairsToIgnore(std::string input){
  std::vector<std::tuple<int, int>> toIgnore;
  std::vector<std::tuple<char, int>> chars;

  for(size_t i = 0; i < input.size(); i++){
    if(input[i] == '{' || input[i] == '[') chars.push_back({input[i], i});
    else if(input[i] == '}' || input[i] == ']') chars.pop_back();
    else if(input[i] == 'r') {
      if(i + 1 < input.size() && input[i + 1] == 'e' && i + 2 < input.size() && input[i + 2] == 'd'){
        std::tuple<char, int> lastOne = chars.back();
        if(std::get<0>(lastOne) == '[') {
          continue;
        }

        std::tuple<int, int> result = balanceRed(input, lastOne);
        toIgnore.push_back(result);
      }
    }
  }

  return toIgnore;
}

int skipTo(int position, std::vector<std::tuple<int, int>> pairs){
  for(const auto& pair : pairs){
    int startPosition = std::get<0>(pair);
    if(position == startPosition){
      return std::get<1>(pair);
    }
  }

  return -1;
}

std::string removeRedLevels(std::string input){
  std::vector<std::tuple<int, int>> pairs = findPairsToIgnore(input);

  std::string result = "";
  size_t i = 0;

  while(i < input.size()){
    int skipPosition = skipTo(i, pairs);
    if(skipPosition != -1){
      i = skipPosition;
    } else {
      result += input[i];
      i++;
    }
  }

  return result;
}

void part2(std::string input){
  std::string cleanedInput = removeRedLevels(input);
  std::vector<int> numbers = findAllInts(cleanedInput);
  int result = sum(numbers);
  std::cout << result << std::endl;
}

int main(){
  std::string input = readFile("./12/input.json");

  part1(input);
  part2(input);

  return 0;
}