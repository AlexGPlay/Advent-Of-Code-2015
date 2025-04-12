#include <iostream>
#include <map>
#include <regex>
#include "../utils/readFile.h"

// Part 1
int countVowels(std::string string){
  int vowelsCount = 0;
  std::regex vowels("[aeiou]");

  std::sregex_iterator it(string.begin(), string.end(), vowels);
  std::sregex_iterator end;

  while(it != end){
    std::smatch match = *it;
    std::string found = match.str();

    vowelsCount++;

    it++;
  }

  return vowelsCount;
}

bool containsCharacterAppearingTwiceInARow(std::string string){
  std::regex appearsTwice(R"((.)\1)");
  return std::regex_search(string, appearsTwice);
}

bool containsForbiddenStrings(std::string string){
  std::regex forbiddenStrings("ab|cd|pq|xy");
  return std::regex_search(string, forbiddenStrings);
}

void part1(std::vector<std::string> data){
  int count = 0;

  for(std::string line : data){
    bool hasThreeVowels = countVowels(line) >= 3;
    bool twiceInArow = containsCharacterAppearingTwiceInARow(line);
    bool forbideenStrings = !containsForbiddenStrings(line);

    if(hasThreeVowels && twiceInArow && forbideenStrings){
      count++;
    }
  }

  std::cout << count << std::endl;
}

// Part 2
bool hasLetterThatRepeats(std::string string){
  std::regex repeatedLetter(R"((.).\1)");
  return std::regex_search(string, repeatedLetter);
}

bool hasRepeatedGroup(std::string string){
  std::regex pairRepeated(R"((..).*\1)");
  return std::regex_search(string, pairRepeated);
}

void part2(std::vector<std::string> data){
  int count = 0;

  for(std::string line : data){
    if(hasLetterThatRepeats(line) && hasRepeatedGroup(line)){
      count++;
    }
  }

  std::cout << count;
}

int main(){
  std::vector<std::string> data = readFileLines("./05/input.txt");

  part1(data);
  part2(data);

  return 0;
}