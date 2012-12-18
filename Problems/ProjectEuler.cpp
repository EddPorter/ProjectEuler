#include "ProjectEuler.h"

#include "Primes.h"   // IsPrime
#include "Text.h"     // IsPalindrome
#include "Timing.h"   // QueryCounter, QueryFrequency

#include <climits>    // INT_MAX
#include <iostream>   // cin, cout
#include <numeric>    // accumulate
#include <ostream>    // endl
#include <string>     // string
#include <vector>     // vector
using namespace std;

#define DISCARDS          5
#define LARGEST_PROBLEM   10
#define TRIALS            5

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))

void ProjectEuler::RunMenuLoop() const {
  while(true) {
    cout << "Enter the number of the problem to execute:" << endl;
    cout << "  1. Sum of natural numbers that are multiples of 3 and 5." << endl;
    cout << "  2. Sum of even-valued Fibonacci terms." << endl;
    cout << "  3. Largest prime factor." << endl;
    cout << "  4. Find largest palindrome product." << endl;
    cout << "  5. Find smallest number with consecutive divisors." << endl;
    cout << "  6. Difference between sum of squares and square sum." << endl;
    cout << "  7. Find nth prime number." << endl;
    cout << "  8. Largest product of consecutive digits." << endl;
    cout << "  9. Special Pythagorean triplet." << endl;
    cout << " 10. Summation of primes." << endl;
    cout << "> ";

    unsigned short problem;
    cin >> problem;
    cout << endl;

    if (problem == 0 || problem > LARGEST_PROBLEM) {
      cout << "Please enter a valid problem number from the menu." << endl;
      continue;
    }

    switch (problem) {
    case 1:
      RunAndTimeMethod(&ProjectEuler::Problem1);
      break;
    case 2:
      RunAndTimeMethod(&ProjectEuler::Problem2);
      break;
    case 3:
      RunAndTimeMethod(&ProjectEuler::Problem3);
      break;
    case 4:
      RunAndTimeMethod(&ProjectEuler::Problem4);
      break;
    case 5:
      RunAndTimeMethod(&ProjectEuler::Problem5);
      break;
    case 6:
      RunAndTimeMethod(&ProjectEuler::Problem6);
      break;
    case 7:
      RunAndTimeMethod(&ProjectEuler::Problem7);
      break;
    case 8:
      RunAndTimeMethod(&ProjectEuler::Problem8);
      break;
    case 9:
      RunAndTimeMethod(&ProjectEuler::Problem9);
      break;
    case 10:
      RunAndTimeMethod(&ProjectEuler::Problem10);
      break;
    }
  }
}

void ProjectEuler::RunAndTimeMethod(ProjectEulerMemFn problem) const {
  static const auto frequency = QueryFrequency();
  std::vector<double> times(TRIALS);
  for (auto i = 0; i < TRIALS + DISCARDS; ++i) {
    const auto start = QueryCounter();
    unsigned long long result = CALL_MEMBER_FN(*this, problem)();
    const auto finish = QueryCounter();
    if (i == 0) {
      std::cout << "Result: " << result << std::endl;
    }
    if (i >= DISCARDS) {
      auto time_taken = (finish - start) * 1000.0 / frequency;
      times.push_back(time_taken);
      std::cout << "\t@ " << time_taken << std::endl;
    }
  }
  auto total_time = std::accumulate(times.begin(), times.end(), 0.0);
  std::cout << "Average time taken: " << total_time / TRIALS << "ms" << std::endl;
  std::cout << std::endl;
}

unsigned long long ProjectEuler::Problem1() const {
  auto result = 0;
  for (auto i = 1; i < 1000; ++i) {
    if (i % 3 == 0 || i % 5 == 0) {
      result += i;
    }
  }
  return result;  // 233168
}

unsigned long long ProjectEuler::Problem2() const {
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
  return acc;   // 4613732
}

unsigned long long ProjectEuler::Problem3() const {
  auto n = 600851475143;
  auto i = 2;
  while (n > 1) {
    if (n % i == 0) {
      n /= i;
    }
    ++i;
  }
  return i - 1; // 6857
}

unsigned long long ProjectEuler::Problem4() const {
  unsigned largest_palindrome = 0;

  for (unsigned first = 999; first >= 100; --first) {
    for(unsigned second = 999; second >= 100; --second) {
      unsigned product = first * second;
      if (IsPalindrome(product) && product > largest_palindrome) {
        largest_palindrome = product;
      }
    }
  }

  return largest_palindrome;  // 906609
}

unsigned long long ProjectEuler::Problem5() const {
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
      return n; // 232792560
    }
  }
}

unsigned long long ProjectEuler::Problem6() const {
  // use well-known formula for calculating triangular numbers
  unsigned sum = (100 * 101) / 2;
  int squared_sum = sum * sum;

  unsigned sum_squares = 0;
  for (unsigned short n = 1; n <= 100; ++n) {
    sum_squares += n * n;
  }

  return squared_sum - sum_squares; // 25164150
}

unsigned long long ProjectEuler::Problem7() const {
  unsigned ordinal = 0;
  unsigned candidate = 1;
  while (ordinal < 10001) {
    if (IsPrime(++candidate)) {
      ++ordinal;
    }
  }
  return candidate; // 104743
}

unsigned long long ProjectEuler::Problem8() const {
  const string digits(
    "73167176531330624919225119674426574742355349194934"
    "96983520312774506326239578318016984801869478851843"
    "85861560789112949495459501737958331952853208805511"
    "12540698747158523863050715693290963295227443043557"
    "66896648950445244523161731856403098711121722383113"
    "62229893423380308135336276614282806444486645238749"
    "30358907296290491560440772390713810515859307960866"
    "70172427121883998797908792274921901699720888093776"
    "65727333001053367881220235421809751254540594752243"
    "52584907711670556013604839586446706324415722155397"
    "53697817977846174064955149290862569321978468622482"
    "83972241375657056057490261407972968652414535100474"
    "82166370484403199890008895243450658541227588666881"
    "16427171479924442928230863465674813919123162824586"
    "17866458359124566529476545682848912883142607690042"
    "24219022671055626321111109370544217506941658960408"
    "07198403850962455444362981230987879927244284909188"
    "84580156166097919133875499200524063689912560717606"
    "05886116467109405077541002256983155200055935729725"
    "71636269561882670428252483600823257530420752963450");
  unsigned max_product = 0;

  for (auto b = digits.begin(), e = b + 5; e != digits.end(); ++b, ++e) {
    unsigned product = std::accumulate(b, e, 1, [](unsigned acc, char next) {
      return acc * (next - '0');
    });
    if (product > max_product) {
      max_product = product;
    }
  }

  return max_product; // 40824
}

unsigned long long ProjectEuler::Problem9() const {
  for (unsigned short a = 1; a < 1000; ++a) {
    for (unsigned short b = a + 1; b < 1000; ++b) {
      unsigned short c = 1000 - a - b;

      if (a * a + b * b == c * c) {
        return a * b * c; // 31875000
      }
    }
  }
  return -1;
}

unsigned long long ProjectEuler::Problem10() const {
  unsigned long long sum = 0;
  for (unsigned n = 2; n < 2000000; ++n) {
    if (IsPrime(n)) {
      sum += n;
    }
  }
  return sum; // 142913828922
}