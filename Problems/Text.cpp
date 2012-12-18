#include "Text.h"

#include <algorithm>  // reverse
#include <string>     // string

bool IsPalindrome(unsigned number) {
  char word[10];
  _ultoa_s(number, word, sizeof(word), 10);
  
  std::string input(word);
  std::string reverse(word);
  std::reverse(reverse.begin(), reverse.end());

  return input == reverse;
}
