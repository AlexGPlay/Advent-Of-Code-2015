#include <iostream>
#include <map>
#include "../utils/readFile.h"
#include "../utils/split.h"

void move(int* position, char movement){
  if(movement == '>'){
    position[1] += 1;
  }
  else if(movement == '<'){
    position[1] -= 1;
  }
  else if(movement == '^'){
    position[0] -= 1;
  }
  else if(movement == 'v'){
    position[0] += 1;
  }
}

void part1(std::string data){
  std::map<std::string, int> map;

  int* position = new int[2]{0, 0};
  map["0,0"] = 1;

  for(char c : data){
    move(position, c);
    std::string strPosition = std::to_string(position[0]) + "," + std::to_string(position[1]);

    if(map.find(strPosition) != map.end()){
      int currentCount = map[strPosition];
      map[strPosition] = currentCount + 1;
    } 
    else {
      map[strPosition] = 1;
    }
  }

  std::cout << map.size() << std::endl;
}

void part2(std::string data){
  std::map<std::string, int> map;

  int* santaPosition = new int[2]{0, 0};
  int* roboSantaPosition = new int[2]{0, 0};

  map["0,0"] = 2;

  int str_size = static_cast<int>(data.size());

  for(int i=0;i<str_size;i++){
    int* positionToUse = i % 2 == 0 ? santaPosition : roboSantaPosition;
    move(positionToUse, data[i]);

    std::string strPosition = std::to_string(positionToUse[0]) + "," + std::to_string(positionToUse[1]);

    if(map.find(strPosition) != map.end()){
      int currentCount = map[strPosition];
      map[strPosition] = currentCount + 1;
    } 
    else {
      map[strPosition] = 1;
    }
  }

  std::cout << map.size() << std::endl;
}

int main(){
  std::string data = readFile("./03/input.txt");

  part1(data);
  part2(data);

  return 0;
}