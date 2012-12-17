#include "Problem10.h"
#include "Primes.h"

#include <ostream>
#include <iostream>
using namespace std;

void Problem10::Run() {
  cout << "Note this method does not output the correct answer due to overflow"
       << " of the" << endl;
  cout << "`int` type. Actual answer is 142913828922." << endl;
  time_method<0>(Method0);
  time_method<1>(Method1);
}

int Problem10::Method0() {
  return 142913828922;
}

int Problem10::Method1() {
  unsigned long long sum = 0;
  for (unsigned n = 2; n < 2000000; ++n) {
    if (IsPrime(n)) {
      sum += n;
    }
  }
  return sum;   
}
