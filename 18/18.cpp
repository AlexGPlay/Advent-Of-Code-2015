#include <iostream>
#include "../utils/readFile.h"

bool isValidPosition(int i, int j, std::vector<std::string> grid){
  return i >= 0 && i < grid.size() && j >= 0 && j < grid[i].size();
}

int countOnNeighbors(int i, int j, std::vector<std::string> grid){
  int count = 0;

  int positions[8][2] = {
    {i + 1, j},
    {i - 1, j},
    {i, j + 1},
    {i, j - 1},
    {i + 1, j + 1},
    {i + 1, j - 1},
    {i - 1, j + 1},
    {i - 1, j - 1},
  };

  for(auto position : positions){
    if(!isValidPosition(position[0], position[1], grid)){
      continue;
    }

    char neighbor = grid[position[0]][position[1]];
    if(neighbor == '#'){
      count++;
    }
  }

  return count;
}

std::vector<std::string> simulate(std::vector<std::string> grid, bool cornersAreAlwaysOn){
  std::vector<std::string> newGrid = grid;

  for(size_t i = 0; i < grid.size(); i++){
    for(size_t j = 0; j < grid[i].size(); j++){
      char currentLight = grid[i][j];
      bool isCorner = i == 0 && j == 0 || 
                      i == 0 && j == grid[i].size() - 1 ||
                      i == grid.size() - 1 && j == 0 || 
                      i == grid.size() - 1 && j == grid[i].size() - 1;
      if(cornersAreAlwaysOn && isCorner){
        newGrid[i][j] = '#';
        continue;
      }

      int onNeighbors = countOnNeighbors(i, j, grid);

      if(currentLight == '#'){
        if(onNeighbors == 2 || onNeighbors == 3){
          newGrid[i][j] = '#';
        } else {
          newGrid[i][j] = '.';
        }
      } else {
        if(onNeighbors == 3){
          newGrid[i][j] = '#';
        } else {
          newGrid[i][j] = '.';
        }
      }
    }
  }

  return newGrid;
}

void part1(std::vector<std::string> lines){
  for(int i = 0; i < 100; i++){
    lines = simulate(lines, false);
  }

  int count = 0;
  for(auto line : lines){
    for(auto light : line){
      if(light == '#'){
        count++;
      }
    }
  }

  std::cout << count << std::endl;
}

void part2(std::vector<std::string> lines){
  lines[0][0] = '#';
  lines[0][lines[0].size() - 1] = '#';
  lines[lines.size() - 1][0] = '#';
  lines[lines.size() - 1][lines[0].size() - 1] = '#';

  for(int i = 0; i < 100; i++){
    lines = simulate(lines, true);
  }

  int count = 0;
  for(auto line : lines){
    for(auto light : line){
      if(light == '#'){
        count++;
      }
    }
  }

  std::cout << count << std::endl;
}

int main(){
  auto lines = readFileLines("./18/input.txt");

  part1(lines);
  part2(lines);

  return 0;
}