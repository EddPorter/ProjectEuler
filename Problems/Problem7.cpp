#include "Problem7.h"

#include <cmath>    // sqrt

void Problem7::Run() {
  time_method<0>(Method0);
  time_method<1>(Method1);
}

int Problem7::Method0() {
  return 104743;
}

int Problem7::Method1() {
  unsigned ordinal = 0;
  unsigned candidate = 1;
  while (ordinal < 10001) {
    if (IsPrime1(++candidate)) {
      ++ordinal;
    }
  }
  return candidate;
}

bool Problem7::IsPrime1(unsigned number) {
  unsigned max_candidate = sqrt(number);
  unsigned n = 2;
  while (n <= max_candidate) {
    if (number % n == 0) {
      return false;
    }
    ++n;
  }
  return true;
}