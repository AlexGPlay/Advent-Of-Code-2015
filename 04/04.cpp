#include <iostream>
// I couldn't run this code because openSSL refuses to work but... so more like a draft
#include <openssl/md5.h>
#include "../utils/readFile.h"

std::string hash(std::string input){
  unsigned char digest[MD5_DIGEST_LENGTH];

  MD5_CTX context;
  MD5_Init(&context);
  MD5_Update(&context, input.c_str(), input.length());
  MD5_Final(digest, &context);

  std::stringstream ss;
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
      ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
  }

  return ss.str();
}

void part1(std::string data){
  int i = 0;

  while(true){
    std::string toHash = data + std::to_string(i);

    std::string hashedData = hash(toHash);
    if(hashedData.find("0000") == 0){
      break;
    }
  }

  std::cout << i << std::endl;
}

void part2(std::string data){
  int i = 0;

  while(true){
    std::string toHash = data + std::to_string(i);

    std::string hashedData = hash(toHash);
    if(hashedData.find("00000") == 0){
      break;
    }
  }

  std::cout << i << std::endl;
}

int main(){
  std::string data = readFile("./04/example.txt");

  part1(data);
  part2(data);

  return 0;
}