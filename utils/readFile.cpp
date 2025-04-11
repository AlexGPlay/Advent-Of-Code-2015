#include "readFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::string readFile(const std::string& path){
  std::ifstream file(path);

  if (!file) {
      std::cerr << "Error opening file\n";
      return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::vector<std::string> readFileLines(const std::string& filePath) {
  std::ifstream file(filePath);
  std::string line;
  std::vector<std::string> lines;

  if (!file.is_open()) {
      std::cerr << "Error opening file!" << std::endl;
      return lines;
  }

  while (std::getline(file, line)) {
      lines.push_back(line);
  }

  file.close();
  return lines;
}