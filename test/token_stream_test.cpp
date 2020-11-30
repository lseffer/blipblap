
#include "token_stream.hpp"

#include "catch2/catch_all.hpp"

TEST_CASE("is whitespace works correctly") {
  std::string tester = "\t \n1";
  auto tobj = TokenStream(tester);
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
  auto tobj = TokenStream(input_with_expected.input);
  tobj.skip_whitespace();
  REQUIRE(tobj.m_cstream.next() == input_with_expected.expected);
}

TEST_CASE("skip comment correctly skips one line") {
  std::string tester = "#asd\ncool";
  auto tobj = TokenStream(tester);
  tobj.skip_comment();
  REQUIRE(tobj.m_cstream.peek() == 'c');
}

TEST_CASE("Reading a string works correctly") {
  std::string tester = "\"coolstring\"";
  auto tobj = TokenStream(tester);
  auto result = tobj.read();
  REQUIRE(result[0].type == 2);
  REQUIRE(result[0].value == "coolstring");
}
