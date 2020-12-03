
#include "token_stream.hpp"

#include "catch2/catch_all.hpp"

TEST_CASE("is whitespace works correctly") {
  REQUIRE(TokenStream::is_whitespace(' '));
  REQUIRE(TokenStream::is_whitespace('a') == false);
  REQUIRE(TokenStream::is_whitespace('1') == false);
  REQUIRE(TokenStream::is_whitespace('\n'));
  REQUIRE(TokenStream::is_whitespace('\t'));
}

TEST_CASE("Keyword matching works correctly") {
  struct keytest {
    std::string input;
    bool expected;
  };
  auto cases = GENERATE(keytest{"func", true}, keytest{"lambda", true}, keytest{"gibberish", false});
  REQUIRE(matches_keyword(cases.input) == cases.expected);
}

TEST_CASE("Token stream unit tests") {
  struct chartest {
    std::string input;
    char expected;
  };

  SECTION("whitespace skipping works correctly") {
    auto input_with_expected =
        GENERATE(chartest{"\n asd", 'a'}, chartest{"\tyou", 'y'}, chartest{"asd", 'a'}, chartest{"\n ", 0});
    auto tobj = TokenStream(input_with_expected.input);
    tobj.skip_whitespace();
    REQUIRE(tobj.m_cstream.current() == input_with_expected.expected);
  }

  SECTION("simple read number") {
    std::string tester = "123 ";
    auto tobj = TokenStream(tester);
    auto res = tobj.read_number();
    REQUIRE(res.value == "123");
  }

  SECTION("skip comment correctly skips one line") {
    std::string tester = "#asd\ncool";
    auto tobj = TokenStream(tester);
    tobj.skip_comment();
    REQUIRE(tobj.m_cstream.peek() == 'c');
  }

  SECTION("Reading a string works correctly") {
    std::string tester = "\"coolstring\"";
    auto tobj = TokenStream(tester);
    auto result = tobj.read();
    REQUIRE(result[0].type == 2);
    REQUIRE(result[0].value == "coolstring");
  }

  SECTION("Reading a number works correctly") {
    std::string tester = "123";
    auto tobj = TokenStream(tester);
    auto result = tobj.read();
    REQUIRE(result[0].type == 1);
    REQUIRE(result[0].value == "123");
  }

  SECTION("Reading a number and a string works correctly") {
    std::string tester = "123.0 \"asd\" b";
    auto tobj = TokenStream(tester);
    auto result = tobj.read();
    REQUIRE(result[0].type == 1);
    REQUIRE(result[0].value == "123.0");
    REQUIRE(result[1].type == 2);
    REQUIRE(result[1].value == "asd");
  }

  SECTION("Reading a full program correctly") {
    std::string tester = "a = \"asd\"\nb = 1.0;print(a + b)";
    auto tobj = TokenStream(tester);
    auto result = tobj.read();
    REQUIRE(result.size() == 12);
    REQUIRE(result[0].type == 4);
    REQUIRE(result[0].value == "a");
    REQUIRE(result[1].type == 5);
    REQUIRE(result[1].value == "=");
    REQUIRE(result[2].type == 2);
    REQUIRE(result[2].value == "asd");
    REQUIRE(result[3].type == 4);
    REQUIRE(result[3].value == "b");
    REQUIRE(result[4].type == 5);
    REQUIRE(result[4].value == "=");
    REQUIRE(result[5].type == 1);
    REQUIRE(result[5].value == "1.0");
    REQUIRE(result[6].type == 4);
    REQUIRE(result[6].value == "print");
    REQUIRE(result[7].type == 0);
    REQUIRE(result[7].value == "(");
    REQUIRE(result[8].type == 4);
    REQUIRE(result[8].value == "a");
    REQUIRE(result[9].type == 5);
    REQUIRE(result[9].value == "+");
    REQUIRE(result[10].type == 4);
    REQUIRE(result[10].value == "b");
    REQUIRE(result[11].type == 0);
    REQUIRE(result[11].value == ")");
  }

  SECTION("Reading syntactic crap correctly results in error") {
    std::string tester = "a?``of a / )( A# _* *";
    auto tobj = TokenStream(tester);
    REQUIRE_THROWS(tobj.read());
  }
}
