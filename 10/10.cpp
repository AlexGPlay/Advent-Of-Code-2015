#include "../utils/readFile.h"
#include <iostream>

std::vector<std::tuple<int, char>> getCount(std::string input){
  std::vector<std::tuple<int, char>> counts;
  
  char current = input[0];
  int count = 0;

  for(const auto& c : input){
    if(c != current){
      counts.push_back({count, current});

      current = c;
      count = 0;
    }
    count++;
  }
  counts.push_back({count, current});

  return counts;
}

std::string transform(std::string input){
  std::vector<std::tuple<int, char>> counts = getCount(input);
  std::string s = "";

  for(const auto& [count, value] : counts){
    s += std::to_string(count);
    s += value;
  }

  return s;
}

void runNTimes(std::string input, int n){
  std::string current = input;

  for(int i=0;i<n;i++){
    current = transform(current);
  }

  std::cout << current.size() << std::endl;
}

int main(){
  std::string input = readFile("./10/input.txt");

  runNTimes(input, 40); // Part 1
  runNTimes(input, 50); // Part 2

  return 0;
}