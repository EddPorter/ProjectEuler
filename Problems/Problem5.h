// 2520 is the smallest number that can be divided by each of the numbers from
// 1 to 10 without any remainder.
//
// What is the smallest positive number that is evenly divisible by all of the
// numbers from 1 to 20?

#pragma once
#include "problembase.h"

class Problem5 : public ProblemBase
{
public:
  void Run();
private: 
  static int Method0();
  static int Method1();
};

