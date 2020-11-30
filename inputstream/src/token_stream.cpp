#include "token_stream.hpp"

std::vector<Token> TokenStream::read() {
  std::vector<Token> result;
  while (!m_cstream.eof()) {
    result.push_back(read_next());
  }
  return result;
}

Token TokenStream::read_next() {
  skip_whitespace();
  auto next = m_cstream.next();
  if (is_comment(next)) {
    skip_comment();
  } else if (is_string(next)) {
    return read_string();
  } else if (is_number(next)) {
    return read_number(next);
  }
  Token def;
  def.type = TokenType::KEYWORD;
  def.value = "asd";
  return def;
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
  std::string value = "";
  while (!m_cstream.eof()) {
    auto next = m_cstream.next();
    if (next == '"') {
      result.value = value;
      return result;
    } else {
      value += next;
    }
  }
  result.value = value;
  return result;
}

Token TokenStream::read_number(char in) {
  Token result;
  result.type = TokenType::NUMBER;
  std::string value = {in};
  while (!m_cstream.eof()) {
    auto next = m_cstream.next();
    if (!is_number(next)) {
      result.value = value;
      return result;
    } else {
      value += next;
    }
  }
  result.value = value;
  return result;
}