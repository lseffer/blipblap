#pragma once

#include <string>

class CharacterStream {
 public:
  CharacterStream(std::string program) : m_program{program} {};
  char current();
  char next();
  char peek();
  bool eof();

 private:
  uint32_t m_position = 0;
  std::string m_program;
};
