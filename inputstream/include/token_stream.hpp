#pragma once

#include <memory>
#include <string>
#include <vector>

#include "char_stream.hpp"

enum TokenType {
  PUNCTUATION,
  NUMBER,
  STRING,
  KEYWORD,
  VARIABLE,
  OPERATION,
};

struct Token {
  TokenType type;
  std::string value;
};

class TokenStream {
 public:
  TokenStream(std::string program) : m_cstream{CharacterStream(program)} {};
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
