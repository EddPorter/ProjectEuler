#include "Problem6.h"
#include <numeric>

void Problem6::Run()
{
  time_method<0>(Method0);
  time_method<1>(Method1);
}


int Problem6::Method0()
{
  return 25164150;
}

int Problem6::Method1()
{
  // use well-known formula for calculating triangular numbers
  unsigned sum = (100 * 101) / 2;
  int squared_sum = sum * sum;

  unsigned sum_squares = 0;
  for (unsigned short n = 1; n <= 100; ++n) {
    sum_squares += n * n;
  }

  return squared_sum - sum_squares;
}
