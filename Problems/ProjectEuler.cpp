#include "ProjectEuler.h"
#include "Problem1.h"
#include "Problem2.h"
#include "Problem3.h"
#include "Problem4.h"
#include "Problem5.h"
#include "Problem6.h"
#include "Problem7.h"
#include "Problem8.h"

#include <iostream>   // cin, cout
#include <ostream>    // endl
using namespace std;

#define LARGEST_PROBLEM   8

void ProjectEuler::RunMenuLoop() {
  while(true) {
    cout << "Enter the number of the problem to exectute:" << endl;
    cout << "  1. Sum of natural numbers that are multiples of 3 and 5." << endl;
    cout << "  2. Sum of even-valued Fibonacci terms." << endl;
    cout << "  3. Largest prime factor." << endl;
    cout << "  4. Find largest palindrome product." << endl;
    cout << "  5. Find smallest number with consecutive divisors." << endl;
    cout << "  6. Difference between sum of squares and square sum." << endl;
    cout << "  7. Find nth prime number." << endl;
    cout << "  8. Largest product of consecutive digits." << endl;
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
      {
        Problem1 problem;
        problem.Run();}
      break;
    case 2:
      {
        Problem2 problem;
        problem.Run();
      }
      break;
    case 3:
      {
        Problem3 problem;
        problem.Run();
      }
      break;
    case 4:
      {
        Problem4 problem;
        problem.Run();
      }
      break;
    case 5:
      {
        Problem5 problem;
        problem.Run();
      }
      break;
    case 6:
      {
        Problem6 problem;
        problem.Run();
      }
      break;
    case 7:
      {
        Problem7 problem;
        problem.Run();
      }
      break;
    case 8:
      {
        Problem8 problem;
        problem.Run();
      }
      break;
    }
  }
}