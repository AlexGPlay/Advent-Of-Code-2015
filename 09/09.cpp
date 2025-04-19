#include "../utils/readFile.h"
#include "../utils/split.h"
#include <iostream>
#include <map>
#include <set>

// Utils
struct Connection {
  std::string from;
  std::string to;
  int weight;
};

std::map<std::string, std::vector<Connection>> buildConnections(std::vector<std::string> data){
  std::map<std::string, std::vector<Connection>> map;

  for(const auto& line : data){
    std::vector<std::string> parts = splitByString(line, " = ");
    std::vector<std::string> locations = splitByString(parts[0], " to ");

    Connection connection1;
    connection1.from = locations[0];
    connection1.to = locations[1];
    connection1.weight = std::stoi(parts[1]);

    if(map.find(connection1.from) == map.end()){
      std::vector<Connection> elems;
      map[connection1.from] = elems;
    }

    map[connection1.from].push_back(connection1);

    Connection connection2;
    connection2.to = locations[0];
    connection2.from = locations[1];
    connection2.weight = std::stoi(parts[1]);

    if(map.find(connection2.from) == map.end()){
      std::vector<Connection> elems;
      map[connection2.from] = elems;
    }

    map[connection2.from].push_back(connection2);
  }

  return map;
}

// Part 1
int shortestPathToEverything(std::string currentNode, int currentCost, std::map<std::string, std::vector<Connection>> connections, std::set<std::string>& visited){
  if(visited.size() == connections.size()){
    return currentCost;
  }

  int minCost = -1;
  for(const auto& connection : connections[currentNode]){
    if(visited.find(connection.to) != visited.end()) continue;

    std::set<std::string> visitedClone(visited);
    visitedClone.insert(connection.to);

    int cost = shortestPathToEverything(connection.to, currentCost + connection.weight, connections, visitedClone);
    if(cost == -1) continue;
    if(minCost == -1 || cost < minCost) minCost = cost;
  }

  return minCost;
}

void part1(std::map<std::string, std::vector<Connection>> connections){
  int minCost = 99999999;

  for(const auto& [key, _] : connections){
    std::set<std::string> visited;
    visited.insert(key);
    int result = shortestPathToEverything(key, 0, connections, visited);
    if(result == -1) continue;
    if(result < minCost) minCost = result;
  }

  std::cout << minCost << std::endl;
}

// part 2
int longestPathToEverything(std::string currentNode, int currentCost, std::map<std::string, std::vector<Connection>> connections, std::set<std::string>& visited){
  if(visited.size() == connections.size()){
    return currentCost;
  }

  int minCost = -1;
  for(const auto& connection : connections[currentNode]){
    if(visited.find(connection.to) != visited.end()) continue;

    std::set<std::string> visitedClone(visited);
    visitedClone.insert(connection.to);

    int cost = longestPathToEverything(connection.to, currentCost + connection.weight, connections, visitedClone);
    if(cost == -1) continue;
    if(cost > minCost) minCost = cost;
  }

  return minCost;
}

void part2(std::map<std::string, std::vector<Connection>> connections){
  int minCost = -1;

  for(const auto& [key, _] : connections){
    std::set<std::string> visited;
    visited.insert(key);
    int result = longestPathToEverything(key, 0, connections, visited);
    if(result == -1) continue;
    if(result > minCost) minCost = result;
  }

  std::cout << minCost << std::endl;
}

int main(){
  std::vector<std::string> data = readFileLines("./09/input.txt");
  std::map<std::string, std::vector<Connection>> connections = buildConnections(data);

  part1(connections);
  part2(connections);

  return 0;
}