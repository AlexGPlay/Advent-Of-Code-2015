#include "../utils/readFile.h"
#include <iostream>
#include <regex>
#include <tuple>

const unsigned long long INITIAL = 20151125;
const unsigned long long MULTIPLIER = 252533;
const unsigned long long MODULUS = 33554393;

unsigned long long powmod(unsigned long long base, unsigned long long exp,
                          unsigned long long mod) {
  unsigned long long result = 1;
  base %= mod;

  while (exp > 0) {
    if (exp % 2 == 1)
      result = (result * base) % mod;
    base = (base * base) % mod;
    exp /= 2;
  }

  return result;
}

unsigned long long getIndex(int row, int col) {
  unsigned long long n = row + col - 1;
  unsigned long long diagonalStart = (n * (n - 1)) / 2;
  return diagonalStart + col;
}

std::tuple<int, int> getInput(const std::string &filename) {
  auto line = readFile(filename);

  // Define the regex to match the row and column numbers
  std::regex re(
      R"(To continue, please consult the code grid in the manual.  Enter the code at row (\d+), column (\d+).)");
  std::smatch match;
  std::tuple<int, int> result = {0, 0};

  if (std::regex_search(line, match, re)) {
    std::get<0>(result) = std::stoi(match[1].str()); // Extract row
    std::get<1>(result) = std::stoi(match[2].str()); // Extract column
  } else {
    throw std::runtime_error("Invalid input format");
  }

  return result;
}

int main() {
  auto [row, col] = getInput("./25/input.txt");

  unsigned long long index = getIndex(row, col);
  unsigned long long code =
      (INITIAL * powmod(MULTIPLIER, index - 1, MODULUS)) % MODULUS;

  std::cout << code << std::endl;

  return 0;
}