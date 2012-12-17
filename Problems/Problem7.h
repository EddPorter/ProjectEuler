// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see
// that the 6th prime is 13.
//
// What is the 10,001st prime number?

#pragma once
#include "problembase.h"

class Problem7 : public ProblemBase
{
public:
  void Run();
private:
  static int Method0();
  static int Method1();

  static bool IsPrime1(unsigned number);
};

