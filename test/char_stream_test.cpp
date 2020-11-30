#include "char_stream.hpp"

#include "catch2/catch_all.hpp"
#include "token_stream.hpp"

TEST_CASE("Character stream correctly traverses") {
  std::string tester = "my cool string\nwith some special chars.";
  auto obj = CharacterStream(tester);
  REQUIRE(obj.eof() == false);
  for (int i = 0; i < tester.size(); ++i) {
    REQUIRE(obj.peek() == tester[i + 1]);
    REQUIRE(obj.next() == tester[i]);
  }
}

TEST_CASE("is whitespace works correctly") {
  std::string tester = "\t \n1";
  auto cobj = CharacterStream(tester);
  auto tobj = TokenStream(cobj);
  REQUIRE(tobj.is_whitespace(' '));
  REQUIRE(tobj.is_whitespace('a') == false);
  REQUIRE(tobj.is_whitespace('1') == false);
  REQUIRE(tobj.is_whitespace('\n'));
  REQUIRE(tobj.is_whitespace('\t'));
}

TEST_CASE("skip whitespace correctly skips until next char") {
  struct tester {
    std::string input;
    char expected;
  };
  auto input_with_expected =
      GENERATE(tester{"\n asd", 'a'}, tester{"\tyou", 'y'}, tester{"asd", 'a'}, tester{"\n ", 0});
  auto cobj = CharacterStream(input_with_expected.input);
  auto tobj = TokenStream(cobj);
  tobj.skip_whitespace();
  REQUIRE(tobj.m_cstream.next() == input_with_expected.expected);
}

TEST_CASE("skip comment correctly skips one line") {
  std::string tester = "#asd\ncool";
  auto cobj = CharacterStream(tester);
  auto tobj = TokenStream(cobj);
  tobj.skip_comment();
  REQUIRE(tobj.m_cstream.peek() == 'c');
}
