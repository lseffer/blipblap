#include "char_stream.hpp"

char CharacterStream::peek() { return this->program[this->position + 1]; }

char CharacterStream::current() { return this->program[this->position]; }

char CharacterStream::next() {
  auto result = this->program[this->position];
  position++;
  return result;
}

bool CharacterStream::eof() { return this->position + 1 > this->program.size(); }
