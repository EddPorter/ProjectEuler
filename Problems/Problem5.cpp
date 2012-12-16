#include "Problem5.h"


void Problem5::Run() {
  time_method<0>(Method0);
  time_method<1>(Method1);
}

int Problem5::Method0() {
  return 232792560;
}

int Problem5::Method1() {
  const unsigned short MIN_DIVISOR = 1;
  const unsigned short MAX_DIVISOR = 20;

  for (unsigned n = 1; ; ++n) {
    bool success = true;
    for (unsigned short d = MIN_DIVISOR; d <= MAX_DIVISOR; ++d) {
      if (n % d) {
        success = false;
        break;
      }
    }
    if (success) {
      return n;
    }
  }
}
