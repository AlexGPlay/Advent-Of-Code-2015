#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> getDivisors(int n) {
  std::vector<int> divisors;
  int limit = std::sqrt(n);
  for (int i = 1; i <= limit; ++i) {
      if (n % i == 0) {
          divisors.push_back(i);
          if (i != n / i) {
              divisors.push_back(n / i);
          }
      }
  }
  std::sort(divisors.begin(), divisors.end());
  return divisors;
}


// Part 1
int getHouseScore(std::vector<int> divisors){
  int score = 0;
  for(int value : divisors){
    score += value * 10;
  }
  return score;
}

int lowestHouseToScore(int score){
  int to = score / 10;

  for(int i = 0; i < to; i++){
    auto divisors = getDivisors(i);
    auto houseScore = getHouseScore(divisors);
    if (houseScore >= score){
      return i;
    }
  }

  return -1;
}

void part1(){
  int lowestHouse = lowestHouseToScore(29000000);
  std::cout << lowestHouse << std::endl;
}

// Part 2
int getHouseScore2(std::vector<int> divisors, int currentHouse){
  int score = 0;
  for(int value : divisors){
    if (currentHouse / value <= 50) {
      score += value * 11;
    }
  }
  return score;
}

int lowestHouseToScore2(int score){
  int to = score / 11;

  for(int i = 0; i < to; i++){
    auto divisors = getDivisors(i);
    auto houseScore = getHouseScore2(divisors, i);
    if (houseScore >= score){
      return i;
    }
  }

  return -1;
}

void part2(){
  int lowestHouse = lowestHouseToScore2(29000000);
  std::cout << lowestHouse << std::endl;
}

int main(){
  part1();
  part2();

  return 0;
}