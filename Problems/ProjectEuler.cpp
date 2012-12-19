#include "ProjectEuler.h"

#include "Primes.h"   // IsPrime
#include "Text.h"     // IsPalindrome
#include "Timing.h"   // QueryCounter, QueryFrequency

#include <climits>    // INT_MAX
#include <iostream>   // cin, cout
#include <numeric>    // accumulate
#include <ostream>    // endl
#include <regex>      // regex, smatch, sregex_iterator
#include <string>     // string
#include <vector>     // vector
using namespace std;

#define DISCARDS          5
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
    cout << " 11. Largest product in a grid." << endl;
    cout << "> ";

    unsigned short problem;
    cin >> problem;
    cout << endl;

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
    case 11:
      RunAndTimeMethod(&ProjectEuler::Problem11);
      break;
    default:
      cout << "Please enter a valid problem number from the menu." << endl;
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

// Largest product in a grid
// Problem 11
// 22 February 2002
//
// In the 20x20 grid below, four numbers along a diagonal line have been marked
// in red.
//  08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
//  49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
//  81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
//  52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
//  22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
//  24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
//  32 98 81 28 64 23 67 10*26 38 40 67 59 54 70 66 18 38 64 70
//  67 26 20 68 02 62 12 20 95*63 94 39 63 08 40 91 66 49 94 21
//  24 55 58 05 66 73 99 26 97 17*78 78 96 83 14 88 34 89 63 72
//  21 36 23 09 75 00 76 44 20 45 35*14 00 61 33 97 34 31 33 95
//  78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
//  16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
//  86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
//  19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
//  04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
//  88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
//  04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
//  20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
//  20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
//  01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
// The product of these numbers is 26 * 63 * 78 * 14 = 1788696.
//
// What is the greatest product of four adjacent numbers in any
// direction (up, down, left, right, or diagonally) in the 20x20 grid?
unsigned long long ProjectEuler::Problem11() const {
  const string data(
    "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08\n"
    "49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00\n"
    "81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65\n"
    "52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91\n"
    "22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80\n"
    "24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50\n"
    "32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70\n"
    "67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21\n"
    "24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72\n"
    "21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95\n"
    "78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92\n"
    "16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57\n"
    "86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58\n"
    "19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40\n"
    "04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66\n"
    "88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69\n"
    "04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36\n"
    "20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16\n"
    "20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54\n"
    "01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48\n");

  vector<vector<unsigned char>> grid;

  {
    vector<unsigned char> row;

    const regex r("(\\d{2})|(\\n)|( )");
    for (sregex_iterator i(data.begin(), data.end(), r), end; i != end; ++i) {
      const smatch &m = *i;
      if (m[1].matched) {
        row.push_back(stoi(m[1]));
      } else if (m[2].matched) {
        grid.push_back(row);
        row.clear();
      } else if (m[3].matched) {
        // do nothing
      } else {
        throw new runtime_error("RUNTIME ERROR: grid must contain only digits, "
          "newlines, and spaces.");
      }
    }

    _ASSERT(grid.size() == 20);
    _ASSERT(grid[0].size() == 20);
  }

  unsigned long long max_product = 0;
  // Check right
  for (unsigned char row = 0; row < 16; ++row) {
    for (unsigned char col = 0; col < 20; ++col) {
      unsigned long long product =
        grid[col][row]     * grid[col][row + 1] *
        grid[col][row + 2] * grid[col][row + 3];
      if (product > max_product) {
        max_product = product;
      }
    }
  }
  // Check down
  for (unsigned char row = 0; row < 20; ++row) {
    for (unsigned char col = 0; col < 16; ++col) {
      unsigned long long product =
        grid[col][row]     * grid[col + 1][row] *
        grid[col + 2][row] * grid[col + 3][row];
      if (product > max_product) {
        max_product = product;
      }
    }
  }
  // Check diagonal (-ve)
  for (unsigned char row = 0; row < 16; ++row) {
    for (unsigned char col = 0; col < 16; ++col) {
      unsigned long long product =
        grid[col][row]         * grid[col + 1][row + 1] *
        grid[col + 2][row + 2] * grid[col + 3][row + 3];
      if (product > max_product) {
        max_product = product;
      }
    }
  }
  // Check diagonal (+ve)
  for (unsigned char row = 4; row < 20; ++row) {
    for (unsigned char col = 0; col < 16; ++col) {
      unsigned long long product =
        grid[col][row]         * grid[col + 1][row - 1] *
        grid[col + 2][row - 2] * grid[col + 3][row - 3];
      if (product > max_product) {
        max_product = product;
      }
    }
  }

  return max_product; // 70600674
}