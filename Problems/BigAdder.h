#pragma once

#include <ostream>
#include <string>
#include <vector>


// Adder of big unsigned numbers.
class BigAdder
{
public:
  BigAdder();
  BigAdder(unsigned initial);
  BigAdder(const char* initial_char);
  BigAdder(const BigAdder& other);  // copy
  BigAdder(BigAdder&& other);       // move

  BigAdder& operator=(const BigAdder& other); // copy assignment
  BigAdder& operator=(BigAdder&& other);      // move assignment

  BigAdder& operator+=(const BigAdder& other);

  ~BigAdder();

  operator std::string();
private:
  std::vector<unsigned> numberParts;
};