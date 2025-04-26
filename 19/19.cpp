#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include "../utils/readFile.h"
#include "../utils/split.h"

std::tuple<std::vector<std::tuple<std::string, std::string>>, std::string> parseFile(std::string filename){
  std::vector<std::string> lines = readFileLines(filename);

  std::vector<std::tuple<std::string, std::string>> replacements;
  for(size_t i=0;i<lines.size() - 2;i++){
    std::string line = lines[i];
    std::vector<std::string> parts = splitByString(line, " => ");
    std::string from = parts[0];
    std::string to = parts[1];
    replacements.push_back(std::make_tuple(from, to));
  }

  return std::make_tuple(replacements, lines[lines.size() - 1]);
}

// Part 1
std::set<std::string> calculateReplacementResults(std::tuple<std::string, std::string> replacement, std::string molecule){
  std::set<std::string> results;
  std::string from = std::get<0>(replacement);
  std::string to = std::get<1>(replacement);

  for(size_t i = 0; i < molecule.size(); i++){
    if(molecule.substr(i, from.size()) != from) continue;

    std::string left = molecule.substr(0, i);
    std::string right = molecule.substr(i + from.size(), molecule.size() - i - from.size());
    results.insert(left + to + right);
  }

  return results;
}

std::set<std::string> calculateAllReplacements(std::vector<std::tuple<std::string, std::string>> replacements, std::string molecule){
  std::set<std::string> results;
  for(auto replacement : replacements){
    std::set<std::string> replacementResults = calculateReplacementResults(replacement, molecule);
    results.insert(replacementResults.begin(), replacementResults.end());
  }

  return results;
}

void part1(std::tuple<std::vector<std::tuple<std::string, std::string>>, std::string> input){
  auto replacements = std::get<0>(input);
  auto molecule = std::get<1>(input);

  int result = calculateAllReplacements(replacements, molecule).size();
  std::cout << result << std::endl;
}

void part2(std::tuple<std::vector<std::tuple<std::string, std::string>>, std::string> input){
  auto replacements = std::get<0>(input);
  auto molecule = std::get<1>(input);

  std::sort(replacements.begin(), replacements.end(), [](auto& a, auto& b){
    return std::get<1>(a).size() > std::get<1>(b).size();
  });

  int steps = 0;
  while(molecule != "e"){
    for(auto& [from, to] : replacements){
      size_t pos = molecule.find(to);
      if(pos == std::string::npos) continue;

      molecule = molecule.substr(0, pos) + from + molecule.substr(pos + to.size());
      steps++;
      break;
    }
  }

  std::cout << steps << std::endl;
}


int main(){
  auto input = parseFile("./19/input.txt");
  
  part1(input);
  part2(input);

  return 0;
}