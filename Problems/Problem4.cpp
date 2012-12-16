#include "Problem4.h"

#include <algorithm>  // reverse
#include <climits>    // INT_MAX
#include <string>     // string

void Problem4::Run() {
  time_method<0>(Method0);
  time_method<1>(Method1);
}

int Problem4::Method0() {
  return 906609;
}

int Problem4::Method1() {
  unsigned largest_palindrome = 0;

  for (unsigned first = 999; first >= 100; --first) {
    for(unsigned second = 999; second >= 100; --second) {
      unsigned product = first * second;
      if (IsPalindrome1(product) && product > largest_palindrome) {
        largest_palindrome = product;
      }
    }
  }

  return largest_palindrome;
}

bool Problem4::IsPalindrome1(unsigned number) {
  char word[10];
  _ultoa_s(number, word, sizeof(word), 10);
  
  std::string input(word);
  std::string reverse(word);
  std::reverse(reverse.begin(), reverse.end());

  return input == reverse;
}