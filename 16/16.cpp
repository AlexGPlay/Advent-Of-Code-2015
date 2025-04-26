#include <iostream>
#include <map>
#include <regex>
#include "../utils/readFile.h"
#include "../utils/split.h"

std::map<std::string, std::tuple<std::string, int>> getPrint(){
  return {
    {"children", {"equal_to", 3}},
    {"cats", {"greater_than", 7}},
    {"samoyeds", {"equal_to", 2}},
    {"pomeranians", {"lower_than", 3}},
    {"akitas", {"equal_to", 0}},
    {"vizslas", {"equal_to", 0}},
    {"goldfish", {"lower_than", 5}},
    {"trees", {"greater_than", 3}},
    {"cars", {"equal_to", 2}},
    {"perfumes", {"equal_to", 1}}
  };
}

std::vector<std::map<std::string, int>> parseLines(const std::vector<std::string>& lines) {
  std::vector<std::map<std::string, int>> parsedLines;

  for(auto line : lines){
    std::map<std::string, int> properties;
    
    std::regex regex("Sue (\\d+): (\\w+): (\\d+), (\\w+): (\\d+), (\\w+): (\\d+)");
    std::smatch match;

    if (std::regex_search(line, match, regex)) {
      properties[match[2]] = std::stoi(match[3]);
      properties[match[4]] = std::stoi(match[5]);
      properties[match[6]] = std::stoi(match[7]);
    }

    parsedLines.push_back(properties);
  }

  return parsedLines;
}

int getValidSue(std::map<std::string, std::tuple<std::string, int>> print, std::vector<std::map<std::string, int>> sues, bool useOperations){
  std::vector<int> validSues;

  for(unsigned int i = 0; i < sues.size(); i++){
    bool valid = true;
    for(auto [key, value] : sues[i]){
      std::string operation = std::get<0>(print[key]);
      if(!useOperations){
        operation = "equal_to";
      }

      int printValue = std::get<1>(print[key]);

      if(operation == "equal_to"){
        if(value != printValue) valid = false;
      } else if(operation == "greater_than"){
        if(value <= printValue) valid = false;
      } else if(operation == "lower_than"){
        if(value >= printValue) valid = false;
      }
    }
    if(valid) validSues.push_back(i + 1);
  }

  if(validSues.size() != 1){
    std::cout << "Error: " << validSues.size() << " valid Sues found." << std::endl;
    return -1;
  }

  return validSues[0];
}

int main(){
  std::vector<std::string> lines = readFileLines("16/input.txt");
  auto parsedLines = parseLines(lines);

  auto print = getPrint();

  int part1 = getValidSue(print, parsedLines, false);
  std::cout << part1 << std::endl;

  int part2 = getValidSue(print, parsedLines, true);
  std::cout << part2 << std::endl;

  return 0;
}