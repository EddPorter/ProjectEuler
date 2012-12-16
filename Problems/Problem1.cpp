#include "Problem1.h"


void Problem1::Run() {
  time_method<0>(Method0);
  time_method<1>(Method1);
}

int Problem1::Method0() {
  return 233168;
}

int Problem1::Method1() {
  auto result = 0;
  for (auto i = 1; i < 1000; ++i) {
    if (i % 3 == 0 || i % 5 == 0) {
      result += i;
    }
  }
  return result;
}