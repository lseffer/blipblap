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
  if (next == '#') {
    skip_comment();
  }
  Token def;
  def.type = "asd";
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