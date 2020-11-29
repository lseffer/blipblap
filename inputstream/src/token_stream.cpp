#include "token_stream.hpp"

std::vector<Token> TokenStream::read() {
  std::vector<Token> result;
  while (!this->cstream.eof()) {
    result.push_back(this->read_next());
  }
  return result;
}

Token TokenStream::read_next() {
  this->skip_whitespace();
  auto next = this->cstream.next();
  if (next == '#') {
    this->skip_comment();
  }
  Token def;
  def.type = "asd";
  def.value = "asd";
  return def;
}

void TokenStream::skip_whitespace() {
  while (is_whitespace(this->cstream.current())) {
    this->cstream.next();
  }
}

void TokenStream::skip_comment() {
  while (this->cstream.peek() != '\n' && !this->cstream.eof()) {
    this->cstream.next();
  }
  if (this->cstream.peek() == '\n') {
    this->cstream.next();
  }
}