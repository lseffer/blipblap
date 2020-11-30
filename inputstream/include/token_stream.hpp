#pragma once

#include <memory>
#include <regex>
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
  bool is_one_of(char in, std::string chars) {
    for (auto compare : chars) {
      if (compare == in) {
        return true;
      }
    }
    return false;
  }
  bool is_comment(char in) { return is_one_of(in, "#"); }
  bool is_string(char in) { return is_one_of(in, "\""); }
  bool is_whitespace(char in) { return is_one_of(in, "\t\n "); }
  bool is_number(char in) { return is_one_of(in, "0123456789"); }
  void skip_whitespace();
  void skip_comment();
  Token read_number(char in);
  Token read_string();
  Token read_op();
  std::vector<Token> read();
  CharacterStream m_cstream;

  Token read_next();

 private:
};
