#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "token_stream.hpp"

int main(int argc, char** argv) {
  auto blap = std::string("a = \"1\"\nb = 2\nprintln(a)");
  auto bla = TokenStream(blap);
  auto res = bla.read();
  for (auto& token : res) {
    std::cout << token.value << token.type << std::endl;
  }
  // int sum = 0;
  // for (std::string line; std::getline(input, line);) {
  //   sum += std::stoi(line);
  // }
  // std::cout << "\nThe sum is: " << sum << "\n";
  return 0;
}
