#include <iostream>
#include <map>
#include <tuple>
#include "../utils/readFile.h"
#include "../utils/split.h"

std::tuple<int, int, int> getReindeer(std::string line){
  auto parts = split(line, ' ');
  int speed = std::stoi(parts[3]);
  int time = std::stoi(parts[6]);
  int rest = std::stoi(parts[13]);
  return std::make_tuple(speed, time, rest);
}

std::vector<std::tuple<int, int, int>> getReindeerList(std::vector<std::string> lines){
  std::vector<std::tuple<int, int, int>> reindeerList;
  for(auto line : lines){
    reindeerList.push_back(getReindeer(line));
  }
  return reindeerList;
}

int getBiggestDistance(std::vector<std::tuple<int, int, int>> reindeerData){
  int biggestDistance = 0;
  for(auto data : reindeerData){
    if(std::get<0>(data) > biggestDistance) biggestDistance = std::get<0>(data);
  }
  return biggestDistance;
}

void runSimulation(std::vector<std::tuple<int, int, int>> reindeerList, int times){
  std::vector<std::tuple<int, int, int>> reindeerData;
  std::vector<int> reindeerPoints(reindeerList.size(), 0);

  for(auto reinder : reindeerList){
    reindeerData.push_back(std::make_tuple(0, std::get<1>(reinder), 0));
  }

  for(int i=0;i<times;i++){
    for(unsigned int j=0;j<reindeerList.size();j++){
      auto reindeer = reindeerList[j];
      auto data = reindeerData[j];

      int distance = std::get<0>(data);
      int timeLeft = std::get<1>(data);
      int restLeft = std::get<2>(data);

      if(timeLeft > 0){
        distance += std::get<0>(reindeer);
        timeLeft--;

        if(timeLeft == 0) restLeft = std::get<2>(reindeer);
      } else if(restLeft > 0){
        restLeft--;

        if(restLeft == 0) timeLeft = std::get<1>(reindeer);
      }

      reindeerData[j] = std::make_tuple(distance, timeLeft, restLeft);
    }

    int biggestDistance = getBiggestDistance(reindeerData);
    for(unsigned int j=0;j<reindeerList.size();j++){
      if(std::get<0>(reindeerData[j]) == biggestDistance){
        reindeerPoints[j]++;
      }
    }
  }

  std::cout << getBiggestDistance(reindeerData) << std::endl;
  int biggestPoints = 0;
  for(auto points : reindeerPoints){
    if(points > biggestPoints) biggestPoints = points;
  }
  std::cout << biggestPoints << std::endl;
}

int main(){
  std::vector<std::string> input = readFileLines("./14/input.txt");
  auto reindeerList = getReindeerList(input);
  runSimulation(reindeerList, 2503);

  return 0;
}