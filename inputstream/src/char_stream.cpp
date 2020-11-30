#include "char_stream.hpp"

char CharacterStream::peek() { return m_program[m_position + 1]; }

char CharacterStream::current() { return m_program[m_position]; }

char CharacterStream::next() {
  auto result = m_program[m_position];
  m_position++;
  return result;
}

bool CharacterStream::eof() { return m_position + 1 > m_program.size(); }
