// If we list all the natural numbers below 10 that are multiples of 3 or 5, we
// get 3, 5, 6 and 9. The sum of these multiples is 23.
//
// Find the sum of all the multiples of 3 or 5 below 1000.

#pragma once
#include "ProblemBase.h"

class Problem1 : public ProblemBase
{
public:
  void Run();
private:
  static int Method0();
  static int Method1();
};