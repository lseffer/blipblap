#pragma once

#include <string>
#include <vector>

#include "char_stream.hpp"

struct Token {
  std::string type;
  std::string value;
};

class TokenStream {
 private:
 public:
  CharacterStream cstream;
  bool is_whitespace(char in) { return in == ' ' || in == '\t' || in == '\n'; }
  void skip_whitespace();
  void skip_comment();
  Token read_number();
  Token read_string();
  Token read_op();

  Token read_next();
  TokenStream(CharacterStream cstream) : cstream{cstream} {};
  std::vector<Token> read();
};
