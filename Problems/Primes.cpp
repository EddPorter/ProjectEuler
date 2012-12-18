#include "Primes.h"

#include <cmath>    // ceil, sqrt

bool IsPrime(unsigned number) {
  unsigned max_candidate = static_cast<unsigned>(ceil(sqrt(number)));
  unsigned n = 2;
  while (n <= max_candidate) {
    if (number % n == 0) {
      return false;
    }
    ++n;
  }
  return true;
}