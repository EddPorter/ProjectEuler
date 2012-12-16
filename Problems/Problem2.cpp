#include "Problem2.h"

#include <vector>     // vector

using namespace std;

void Problem2::Run() {
  time_method<0>(Method0);
  time_method<1>(Method1);
  time_method<2>(Method2);
}

int Problem2::Method0() {
  return 4613732;
}

int Problem2::Method1() {
  int last2 = 1, last1 = 2;
  vector<int> v;
  v.push_back(last2);
  v.push_back(last1);
  int i;
  while ((i = last1 + last2) < 4000000) {
    v.push_back(i);
    last2 = last1;
    last1 = i;
  }
  return accumulate(v.begin(), v.end(), 0, [](const int &acc, const int &value) {
    return acc + (value % 2 == 0 ? value : 0);
  });
}

int Problem2::Method2() {
  int acc = 2;
  int last2 = 1, last1 = 2;
  int next ;
  while ((next = last2 + last1) < 4000000) {
    if (next % 2 == 0) {
      acc += next;
    }
    last2 = last1;
    last1 = next;
  }
  return acc;
}