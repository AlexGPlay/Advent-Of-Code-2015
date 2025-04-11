#include <iostream>
#include <algorithm>
#include "../utils/readFile.h"
#include "../utils/split.h"

// Utils

std::vector<int> getSides(std::string line){
  std::vector<std::string> parts = split(line, 'x');
  std::vector<int> result(parts.size());

  std::transform(parts.begin(), parts.end(), result.begin(), [](const std::string& dimension) {
    return std::stoi(dimension);
  });

  return result;
}

std::vector<int> findSmallestSides(std::string line){
  std::vector<int> result = getSides(line);
  std::sort(result.begin(), result.end());
  return result;
}

// Part 1

int calculateWrappingPaper(std::string line){
  std::vector<int> sides = getSides(line);

  int l = sides[0];
  int w = sides[1];
  int h = sides[2];

  return 2*l*w + 2*w*h + 2*h*l;
}

int calculateSmallestSide(std::string line){
  std::vector<int> result = findSmallestSides(line);
  return result[0] * result[1];
}

void part1(std::vector<std::string> input){
  int total = 0;

  for(std::string line : input){
    int wrappingPaper = calculateWrappingPaper(line);
    int smallestSide = calculateSmallestSide(line);

    total += wrappingPaper + smallestSide;
  }

  std::cout << total << std::endl;
}

// Part 2

int calculateRibbonWrap(std::string line){
  std::vector<int> result = findSmallestSides(line);
  return result[0] * 2 + result[1] * 2;
}

int calculateRibbonBow(std::string line){
  std::vector<int> sides = getSides(line);
  return sides[0]*sides[1]*sides[2];
}

void part2(std::vector<std::string> input){
  int total = 0;

  for(std::string line : input){
    int ribbonWrap = calculateRibbonWrap(line);
    int ribbonBow = calculateRibbonBow(line);

    total += ribbonWrap + ribbonBow;
  }

  std::cout << total << std::endl;
}

int main(){
  std::vector<std::string> input = readFileLines("./02/input.txt");
  
  part1(input);
  part2(input);

  return 0; 
}