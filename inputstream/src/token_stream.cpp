#include "token_stream.hpp"

bool matches_keyword(std::string value, const std::vector<std::string> &keywords) {
  return std::find(keywords.begin(), keywords.end(), value) != keywords.end();
}

bool TokenStream::is_one_of(char in, std::string chars) {
  for (auto compare : chars) {
    if (compare == in) {
      return true;
    }
  }
  return false;
}
bool TokenStream::is_comment(char in) { return TokenStream::is_one_of(in, "#"); }
bool TokenStream::is_string(char in) { return TokenStream::is_one_of(in, "\""); }
bool TokenStream::is_whitespace(char in) { return TokenStream::is_one_of(in, "\t\n ;"); }
bool TokenStream::is_number(char in) { return TokenStream::is_one_of(in, "0123456789."); }
bool TokenStream::is_operation(char in) { return TokenStream::is_one_of(in, "+-*/="); }
bool TokenStream::is_punctuation(char in) { return TokenStream::is_one_of(in, "(),:"); }
bool TokenStream::is_keyword_or_variable(char in) {
  return TokenStream::is_one_of(in, "abcdefghijklmnopqrstuvwxyz") || is_number(in);
}

std::vector<Token> TokenStream::read() {
  std::vector<Token> result;
  while (!m_cstream.eof()) {
    result.push_back(read_next());
  }
  return result;
}

Token TokenStream::read_next() {
  skip_whitespace();
  auto current = m_cstream.current();
  if (is_comment(current)) {
    skip_comment();
  } else if (is_string(current)) {
    return read_string();
  } else if (is_number(current)) {
    return read_number();
  } else if (is_operation(current)) {
    return read_operation();
  } else if (is_punctuation(current)) {
    return read_punctuation();
  } else if (is_keyword_or_variable(current)) {
    return read_keyword_variable();
  }
  throw std::string{"Unrecognized token: "} + current;
}

void TokenStream::skip_whitespace() {
  while (is_whitespace(m_cstream.current())) {
    m_cstream.next();
  }
}

void TokenStream::skip_comment() {
  while (m_cstream.peek() != '\n' && !m_cstream.eof()) {
    m_cstream.next();
  }
  if (m_cstream.peek() == '\n') {
    m_cstream.next();
  }
}

Token TokenStream::read_string() {
  Token result;
  result.type = TokenType::STRING;
  std::string value;
  // Before starting we move the pointer beyond the start quote
  m_cstream.next();
  while (!m_cstream.eof()) {
    auto next = m_cstream.peek();
    value += m_cstream.next();
    if (next == '"') {
      // Before exiting we move the pointer beyond the end quote
      m_cstream.next();
      result.value = value;
      return result;
    }
  }
  result.value = value;
  return result;
}

Token TokenStream::read_number() {
  Token result;
  result.type = TokenType::NUMBER;
  std::string value;
  while (!m_cstream.eof()) {
    auto next = m_cstream.peek();
    value += m_cstream.next();
    if (!is_number(next)) {
      result.value = value;
      return result;
    }
  }
  result.value = value;
  return result;
}

Token TokenStream::read_operation() {
  Token result;
  result.type = TokenType::OPERATION;
  std::string value;
  while (!m_cstream.eof()) {
    auto next = m_cstream.peek();
    value += m_cstream.next();
    if (!is_operation(next)) {
      result.value = value;
      return result;
    }
  }
  result.value = value;
  return result;
}

Token TokenStream::read_punctuation() {
  Token result;
  result.type = TokenType::PUNCTUATION;
  std::string value = {m_cstream.next()};
  result.value = value;
  return result;
}

Token TokenStream::read_keyword_variable() {
  Token result;
  std::string value;
  while (!m_cstream.eof()) {
    auto next = m_cstream.peek();
    value += m_cstream.next();
    if (!is_keyword_or_variable(next)) {
      if (matches_keyword(value)) {
        result.type = TokenType::KEYWORD;
      } else {
        result.type = TokenType::VARIABLE;
      }
      result.value = value;
      return result;
    }
  }
  result.value = value;
  return result;
}
