// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
// 
// Find the sum of all the primes below two million.

#pragma once
#include "problembase.h"

class Problem10 : public ProblemBase
{
public:
  void Run();
private:
  static int Method0();
  static int Method1();
};

