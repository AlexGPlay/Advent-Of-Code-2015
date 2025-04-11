#include <iostream>
#include "../utils/readFile.h"

void part1(std::string input){
  int result = 0;

  for(char c : input){
    if(c == '('){
      result += 1;
    }
    else if(c == ')') {
      result -= 1;
    }
  }

  std::cout << result << std::endl;
}

void part2(std::string input){
  int result = 0;
  int position = 0;

  for(char c : input){
    if(c == '('){
      result += 1;
    }
    else if(c == ')') {
      result -= 1;
    }

    position++;

    if(result < 0){
      break;
    }
  }

  std::cout << position << std::endl;
}


int main(){
  std::string fileContent = readFile("./01/input.txt");

  part1(fileContent);
  part2(fileContent);

  return 0;
}