#include "../utils/readFile.h"
#include "../utils/split.h"
#include <regex>
#include <iostream>

// Part 1
bool isHex(const std::string& s) {
  return s.size() == 2 && std::isxdigit(s[0]) && std::isxdigit(s[1]);
}

int countChars(std::string line){
  int size = 0;

  size_t i = 1;
  while(i < line.size() - 1){
    size++;
    if(line[i] != '\\'){
      i++;
      continue;
    }

    bool is_in_range = i + 1 < line.size() - 1;
    if(!is_in_range){
      i++;
      continue;
    }

    if(line[i + 1] == '\\' || line[i + 1] == '"'){
      i += 2;
    }
    else if(line[i + 1] == 'x'){
      if(i + 3 >= line.size()){
        i++;
        continue;
      }

      std::string potentialHex{line[i + 2], line[i + 3]};
      if(isHex(potentialHex)){
        i += 4;
        continue;
      }

      i++;
    } else {
      i++;
    }
  }

  return size;
}

void part1(std::vector<std::string> data){
  int total = 0;
  int fullTotal = 0;

  for(const auto& line : data){
    int count = countChars(line);
    total += count;
    fullTotal += int(line.size());
  }

  std::cout << fullTotal - total << std::endl;
}

// Part 2
std::string encode(char c){
  if(c == '"'){
    return "\\\"";
  }
  else if(c == '\\'){
    return "\\\\";
  }
  return std::string{c};
}

std::string encodeLine(std::string line){
  std::string encodedLine = "\"";

  for(const auto& c : line){
    encodedLine += encode(c);
  }

  return encodedLine + "\"";
}

void part2(std::vector<std::string> data){
  size_t total = 0;
  size_t fullTotal = 0;

  for(const auto& line : data){
    std::string encodedLine = encodeLine(line);
    total += encodedLine.size();
    fullTotal += line.size();
  }

  std::cout << total - fullTotal << std::endl;
}

int main(){
  std::vector<std::string> data = readFileLines("./08/input.txt");
  part1(data);
  part2(data);
}