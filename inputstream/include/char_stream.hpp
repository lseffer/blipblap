#pragma once

#include <string>

class CharacterStream {
 private:
  uint32_t position = 0;
  std::string program;

 public:
  CharacterStream(std::string program) : program{program} {};
  char current();
  char next();
  char peek();
  bool eof();
};
