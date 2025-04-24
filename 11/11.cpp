#include <iostream>
#include <set>
#include "../utils/readFile.h"

std::string increase(std::string password){
  int position = password.size() - 1;
  bool carry = true;

  while(carry && position >= 0){
    char currentChar = password[position];
    char newChar = currentChar + 1;
    if(newChar > 'z'){
      newChar = 'a';
      carry = true;
    } else {
      carry = false;
    }

    password[position] = newChar;
    position--;
  }

  return password;
}

bool containsIncreasingSequence(const std::string password, unsigned int length){
  for(size_t i = 0; i <= password.size() - length; i++){
    bool increasing = true;
    for(size_t j = 1; j < length; j++){
      if(password[i + j] != password[i + j - 1] + 1){
        increasing = false;
        break;
      }
    }
    if(increasing) return true;
  }
  return false;
}

bool containsForbiddenLetters(const std::string password, const std::string forbidden){
  for(char c : forbidden){
    if(password.find(c) != std::string::npos) return true;
  }
  return false;
}

bool containsTwoDifferentPairs(const std::string password){
  std::set<char> pairsSet;

  for(size_t i = 0; i < password.size() - 1; i++){
    if(password[i] == password[i + 1]){
      pairsSet.insert(password[i]);
      i++;
    }
  }

  return pairsSet.size() >= 2;
}

std::string makeNextPassword(std::string password){
  bool isValid = false;

  while(!isValid){
    password = increase(password);

    if(containsIncreasingSequence(password, 3) && 
       !containsForbiddenLetters(password, "iol") && 
       containsTwoDifferentPairs(password)){
      isValid = true;
    }
  }

  return password;
}

int main(){
  std::string password = readFile("./11/input.txt");

  std::string part1Password = makeNextPassword(password);
  std::string part2Password = makeNextPassword(part1Password);

  std::cout << part1Password << std::endl;
  std::cout << part2Password << std::endl;

  return 0;
}