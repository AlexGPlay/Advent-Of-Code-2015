#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>
#include "../utils/readFile.h"
#include "../utils/split.h"

std::map<std::string, std::vector<std::tuple<std::string, int>>> getConnections(std::vector<std::string> input){
  std::map<std::string, std::vector<std::tuple<std::string, int>>> connections;

  for(const auto& line : input){
    std::vector<std::string> parts = split(line, ' ');
    std::string name1 = parts.front();
    std::string name2 = parts.back().substr(0, parts.back().size() - 1);

    int operation = parts[2] == "gain" ? 1 : -1;
    int value = std::stoi(parts[3]);

    if(connections.find(name1) == connections.end()){
      connections[name1] = std::vector<std::tuple<std::string, int>>();
    }

    connections[name1].push_back({name2, operation * value});
  }

  return connections;
}

// Tbh this is not ideal as the permutations have repeated combinations and I could probably backtrack this to get the solution
std::vector<std::string> generatePermutations(std::vector<std::string> input){
  std::vector<std::string> result;
  std::sort(input.begin(), input.end());
  do {
    std::string combination;
    for(const auto& str : input){
      combination += str + " ";
    }
    result.push_back(combination);
  } while(std::next_permutation(input.begin(), input.end()));
  return result;
}

std::vector<std::string> getKeys(std::map<std::string, std::vector<std::tuple<std::string, int>>> connections){
  std::vector<std::string> keys;
  for(const auto& pair : connections){
    keys.push_back(pair.first);
  }
  return keys;
}

int getPermutationHappiness(std::vector<std::string> permutation, std::map<std::string, std::vector<std::tuple<std::string, int>>> connections){
  int happiness = 0;
  for(size_t i = 0; i < permutation.size(); i++){
    std::string currentName = permutation[i];
    std::string leftName = permutation[(i - 1 + permutation.size()) % permutation.size()];
    std::string rightName = permutation[(i + 1) % permutation.size()];

    for(const auto& connection : connections[currentName]){
      std::string neighborName = std::get<0>(connection);
      int value = std::get<1>(connection);
      if(neighborName == leftName || neighborName == rightName){
        happiness += value;
      }
    }
  }
  return happiness;
}

void part1(std::map<std::string, std::vector<std::tuple<std::string, int>>> connections){
  std::vector<std::string> keys = getKeys(connections);
  std::vector<std::string> permutations = generatePermutations(keys);
  
  int bestHappiness = 0;

  for(const auto& perm : permutations){
    std::vector<std::string> names = split(perm, ' ');
    int happiness = getPermutationHappiness(names, connections);
    if(happiness > bestHappiness){
      bestHappiness = happiness;
    }
  }

  std::cout << bestHappiness << std::endl;
}

void part2(std::map<std::string, std::vector<std::tuple<std::string, int>>> connections){
  std::vector<std::string> keys = getKeys(connections);
  keys.push_back("Me");
  
  std::vector<std::string> permutations = generatePermutations(keys);
  
  int bestHappiness = 0;

  for(const auto& perm : permutations){
    std::vector<std::string> names = split(perm, ' ');
    int happiness = getPermutationHappiness(names, connections);
    if(happiness > bestHappiness){
      bestHappiness = happiness;
    }
  }

  std::cout << bestHappiness << std::endl;
}

int main(){
  std::vector<std::string> input = readFileLines("./13/input.txt");
  std::map<std::string, std::vector<std::tuple<std::string, int>>> connections = getConnections(input);
  
  part1(connections);
  part2(connections);

  return 0;
}