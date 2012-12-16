// A palindromic number reads the same both ways. The largest palindrome made
// from the product of two 2-digit numbers is 9009 = 91 99.
//
// Find the largest palindrome made from the product of two 3-digit numbers.

#pragma once

#include "ProblemBase.h"

class Problem4 : public ProblemBase
{
public:
  void Run();
private:
  static int Method0();
  static int Method1();

  static bool IsPalindrome1(unsigned number);
};

