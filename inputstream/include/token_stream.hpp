#pragma once

#include <string>
#include <vector>

#include "char_stream.hpp"

struct Token {
  std::string type;
  std::string value;
};

class TokenStream {
 public:
  TokenStream(CharacterStream cstream) : m_cstream{cstream} {};
  bool is_whitespace(char in) { return in == ' ' || in == '\t' || in == '\n'; }
  void skip_whitespace();
  void skip_comment();
  Token read_number();
  Token read_string();
  Token read_op();
  std::vector<Token> read();
  CharacterStream m_cstream;

  Token read_next();

 private:
};
