#include "Problem7.h"
#include "Primes.h"   // IsPrime

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
    if (IsPrime(++candidate)) {
      ++ordinal;
    }
  }
  return candidate;
}