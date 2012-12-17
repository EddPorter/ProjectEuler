#include "Primes.h"

#include <cmath>    // sqrt

bool IsPrime(unsigned number) {
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