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
