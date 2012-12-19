#include "Text.h"

#include <algorithm>  // reverse
#include <string>     // string

bool IsPalindrome(unsigned number) {
  char word[10];
  _ultoa_s(number, word, sizeof(word), 10);
  
  char *b = word, *e = word + strnlen_s(word, 10) - 1;

  while (*b++ == *e--)
    if (b > e) { return true; }
  return false;
}
