#include "Problem3.h"

#include <cmath>

using namespace std;

#define TARGET  600851475143

void Problem3::Run()
{
  time_method<0>(Method0);
  time_method<1>(Method1);
  time_method<2>(Method2);
  time_method<3>(Method3);
}

int Problem3::Method0() {
  return 6857;
}

int Problem3::Method1() {
  auto n = TARGET;
  for (auto i = 2; i <= static_cast<long long>(sqrt(n)); ++i) {
    if (n % i == 0) {
      n /= i;
    }
  }
  return static_cast<int>(n);
}

int Problem3::Method2() {
  auto n = TARGET;
  auto i = 2;
  auto factor = TARGET;
  while (n > 1) {
    if (n % i == 0) {
      n /= i;
      factor = i;
    }
    ++i;
  }
  return static_cast<int>(factor);
}

int Problem3::Method3() {
  auto n = TARGET;
  auto i = 2;
  while (n > 1) {
    if (n % i == 0) {
      n /= i;
    }
    ++i;
  }
  return static_cast<int>(i - 1);
}