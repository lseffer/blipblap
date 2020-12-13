#pragma once

#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "char_stream.hpp"

inline const std::array<std::string_view, 2> KEYWORDS = {"func", "lambda"};

bool matches_keyword(std::string value);

enum TokenType {
  PUNCTUATION,
  NUMBER,
  STRING,
  KEYWORD,
  VARIABLE,
  OPERATOR,
};

struct Token {
  TokenType type;
  std::string value;
};

class TokenStream {
 public:
  TokenStream(std::string program) : m_cstream{CharacterStream(program)} {};
  void skip_whitespace();
  void skip_comment();
  Token read_number();
  Token read_string();
  Token read_operation();
  Token read_keyword_variable();
  Token read_punctuation();
  std::vector<Token> read();
  CharacterStream m_cstream;

  Token read_next();
  static bool is_one_of(char in, std::string chars);
  static bool is_comment(char in);
  static bool is_string(char in);
  static bool is_whitespace(char in);
  static bool is_number(char in);
  static bool is_operation(char in);
  static bool is_punctuation(char in);
  static bool is_keyword_or_variable(char in);

 private:
};
