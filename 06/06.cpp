#include <iostream>
#include <regex>
#include "../utils/readFile.h"

struct Line {
  std::string action;
  int fromX;
  int fromY;
  int toX;
  int toY;
};

Line parseLine(std::string line){
  std::regex toParse(R"(^(toggle|turn on|turn off) (\d+),(\d+) through (\d+),(\d+)$)");
  std::smatch match;

  if(!std::regex_search(line, match, toParse)){
    throw std::runtime_error("Invalid input format: " + line);
  }

  Line toReturn;
  toReturn.action = match[1].str();
  toReturn.fromX = std::stoi(match[2].str());
  toReturn.fromY = std::stoi(match[3].str());
  toReturn.toX = std::stoi(match[4].str());
  toReturn.toY = std::stoi(match[5].str());

  return toReturn;
}

// Part 1
void runLinePart1(std::string line, bool lights[1000][1000]){
  Line parsedLine = parseLine(line);

  for(int i=parsedLine.fromX;i<=parsedLine.toX;i++){
    for(int j=parsedLine.fromY;j<=parsedLine.toY;j++){
      if(parsedLine.action == "toggle"){
        lights[i][j] = !lights[i][j];
      }

      else if(parsedLine.action == "turn on"){
        lights[i][j] = true;
      }

      else if(parsedLine.action == "turn off"){
        lights[i][j] = false;
      }
    }
  }
}

int countLights(bool lights[1000][1000]){
  int count = 0;

  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      if (lights[i][j]) ++count;
    }
  }

  return count;
}

void part1(std::vector<std::string> data){
  bool lights[1000][1000] = {{false}};

  for(std::string line : data){
    runLinePart1(line, lights);
  }

  std::cout << countLights(lights) << std::endl;
}

// Part 2
void runLinePart2(std::string line, std::vector<std::vector<int>>& lights){
  Line parsedLine = parseLine(line);

  for(int i=parsedLine.fromX;i<=parsedLine.toX;i++){
    for(int j=parsedLine.fromY;j<=parsedLine.toY;j++){
      if(parsedLine.action == "toggle"){
        lights[i][j] += 2;
      }

      else if(parsedLine.action == "turn on"){
        lights[i][j] += 1;
      }

      else if(parsedLine.action == "turn off"){
        lights[i][j] -= 1;

        if(lights[i][j] < 0){
          lights[i][j] = 0;
        }
      }
    }
  }
}

long countTotalIntensity(std::vector<std::vector<int>> lights){
  long count = 0;

  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 1000; ++j) {
      count += lights[i][j];
    }
  }

  return count;
}

void part2(std::vector<std::string> data){
  std::vector<std::vector<int>> lights(1000, std::vector<int>(1000, 0));

  for(const auto& line : data){
    runLinePart2(line, lights);
  }

  std::cout << countTotalIntensity(lights) << std::endl;
}

int main(){
  std::vector<std::string> data = readFileLines("./06/input.txt");

  part1(data);
  part2(data);
}