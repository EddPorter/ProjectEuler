#include "Problem9.h"

void Problem9::Run() {
  time_method<0>(Method0);
  time_method<1>(Method1);
}

int Problem9::Method0() {
  return 31875000;
}

int Problem9::Method1() {
  for (unsigned short a = 1; a < 1000; ++a) {
    for (unsigned short b = a + 1; b < 1000; ++b) {
      unsigned short c = 1000 - a - b;

      if (a * a + b * b == c * c) {
        return a * b * c;
      }
    }
  }
  return -1;
}