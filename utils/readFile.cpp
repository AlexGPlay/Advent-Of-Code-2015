#include "readFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string readFile(std::string path){
  std::ifstream file(path);

  if (!file) {
      std::cerr << "Error opening file\n";
      return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}