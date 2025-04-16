#include <regex>
#include <iostream>
#include <map>
#include <deque>
#include "../utils/readFile.h"
#include "../utils/split.h"

struct Operation {
  std::string operation;
  std::string operand1;
  std::string operand2;
  std::string destination;
};

Operation parseLine(std::string line){
  std::vector<std::string> parts = splitByString(line, " -> ");

  Operation operation;
  operation.destination = parts[1];

  std::regex binaryOperators(R"(AND|OR|RSHIFT|LSHIFT)");
  std::smatch binaryMatch;
  if(std::regex_search(parts[0], binaryMatch, binaryOperators)){
    std::vector<std::string> operationParts = splitByString(parts[0], " ");
    operation.operand1 = operationParts[0];
    operation.operation = operationParts[1];
    operation.operand2 = operationParts[2];
  }
  else if(parts[0].find("NOT") == 0){
    std::vector<std::string> operationParts = splitByString(parts[0], " ");
    operation.operation = "NOT";
    operation.operand1 = operationParts[1];
  }
  else {
    operation.operation = "";
    operation.operand1 = parts[0];
  }

  return operation;
}

bool isNumber(const std::string& s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int getValue(std::string& operand, std::map<std::string, unsigned short>& map){
  if(isNumber(operand)){
    return std::stoi(operand);
  }

  if(map.find(operand) != map.end()){
    return map[operand];
  }

  return -1;
}

bool executeOperation(Operation operation, std::map<std::string, unsigned short>& map){
  if(operation.operation == "AND"){
    int operand1 = getValue(operation.operand1, map);
    int operand2 = getValue(operation.operand2, map);

    if(operand1 == -1 || operand2 == -1){
      return false;
    }

    map[operation.destination] = operand1 & operand2;
  }
  else if(operation.operation == "OR"){
    int operand1 = getValue(operation.operand1, map);
    int operand2 = getValue(operation.operand2, map);

    if(operand1 == -1 || operand2 == -1){
      return false;
    }

    map[operation.destination] = operand1 | operand2;
  }
  else if(operation.operation == "RSHIFT"){
    int operand1 = getValue(operation.operand1, map);
    int operand2 = getValue(operation.operand2, map);

    if(operand1 == -1 || operand2 == -1){
      return false;
    }

    map[operation.destination] = operand1 >> operand2;
  }
  else if(operation.operation == "LSHIFT"){
    int operand1 = getValue(operation.operand1, map);
    int operand2 = getValue(operation.operand2, map);

    if(operand1 == -1 || operand2 == -1){
      return false;
    }

    map[operation.destination] = operand1 << operand2;
  }
  else if(operation.operation == "NOT"){
    int operand1 = getValue(operation.operand1, map);

    if(operand1 == -1){
      return false;
    }

    map[operation.destination] = ~operand1;
  }
  else {
    int operand1 = getValue(operation.operand1, map);

    if(operand1 == -1){
      return false;
    }

      map[operation.destination] = operand1;
  }

  return true;
}

void part1(std::vector<std::string> data){
  std::map<std::string, unsigned short> map;
  std::deque<Operation> operations;

  for(const auto& line : data){
    operations.push_back(parseLine(line));
  }

  while(operations.size()){
    Operation operation = operations.front();
    operations.pop_front();

    bool executed = executeOperation(operation, map);
    if(!executed){
      operations.push_back(operation);
    }
  }

  std::cout << map["a"] << std::endl;
}

void part2(std::vector<std::string> data){
  std::map<std::string, unsigned short> map;
  std::deque<Operation> operations;

  for(const auto& line : data){
    operations.push_back(parseLine(line));
  }

  while(operations.size()){
    Operation operation = operations.front();
    operations.pop_front();

    bool executed = executeOperation(operation, map);
    if(!executed){
      operations.push_back(operation);
    }
  }

  std::cout << map["a"];
}

int main(){
  std::vector<std::string> data = readFileLines("./07/input.txt");
  part1(data);

  std::vector<std::string> data2 = readFileLines("./07/input-2.txt");
  part2(data2);

  return 0;
}