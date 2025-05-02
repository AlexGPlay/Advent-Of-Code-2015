#include "../utils/readFile.h"
#include "../utils/split.h"
#include <iostream>
#include <map>

int getRegisterValue(std::string reg, std::map<std::string, int> &registers) {
  if (registers.find(reg) != registers.end()) {
    return registers[reg];
  } else {
    return 0;
  }
}

int runInstruction(std::string instruction,
                   std::map<std::string, int> &registers) {
  std::vector<std::string> parts = split(instruction, ' ');
  std::string op = parts[0];
  std::string reg = parts[1];

  if (op == "hlf") {
    registers[reg] = getRegisterValue(reg, registers) / 2;
  } else if (op == "tpl") {
    registers[reg] = getRegisterValue(reg, registers) * 3;
  } else if (op == "inc") {
    registers[reg] = getRegisterValue(reg, registers) + 1;
  } else if (op == "jmp") {
    return std::stoi(reg);
  } else if (op == "jie") {
    int offset = std::stoi(parts[2]);
    if (getRegisterValue(reg, registers) % 2 == 0) {
      return offset;
    }
  } else if (op == "jio") {
    int offset = std::stoi(parts[2]);
    if (getRegisterValue(reg, registers) == 1) {
      return offset;
    }
  }

  return 1;
}

void part1(std::vector<std::string> lines) {
  std::map<std::string, int> registers;

  unsigned int instructionPointer = 0;
  while (instructionPointer < lines.size()) {
    // Remove ,
    auto splittedLine = split(lines[instructionPointer], ',');
    std::string cleanedLine = splittedLine[0];
    if (splittedLine.size() > 1) {
      cleanedLine += splittedLine[1];
    }

    instructionPointer += runInstruction(cleanedLine, registers);
  }

  std::cout << registers["b"] << std::endl;
}

void part2(std::vector<std::string> lines) {
  std::map<std::string, int> registers;
  registers["a"] = 1;

  unsigned int instructionPointer = 0;
  while (instructionPointer < lines.size()) {
    // Remove ,
    auto splittedLine = split(lines[instructionPointer], ',');
    std::string cleanedLine = splittedLine[0];
    if (splittedLine.size() > 1) {
      cleanedLine += splittedLine[1];
    }

    instructionPointer += runInstruction(cleanedLine, registers);
  }

  std::cout << registers["b"] << std::endl;
}

int main() {
  auto lines = readFileLines("./23/input.txt");

  part1(lines);
  part2(lines);

  return 0;
}