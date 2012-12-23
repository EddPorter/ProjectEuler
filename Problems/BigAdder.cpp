#include "BigAdder.h"

#include <type_traits>

#define BIGADDERPART_MAX  (999999999ULL)
#define BIGADDER_DIVIDER  (1000000000ULL)

BigAdder::BigAdder()
{
}

BigAdder::BigAdder(unsigned initial)
{
  numberParts.push_back(initial);
}

BigAdder::BigAdder(const char* initial_char)
{
  std::string initial(initial_char);
  unsigned long long adder = 0;
  unsigned long long position = 1;
  for(auto i = initial.crbegin(); i != initial.crend(); ++i) {
    unsigned char next_digit = ((*i) - '0');
    unsigned long long next_value = next_digit * position;
    if (next_value + adder <= BIGADDERPART_MAX) {
      adder += next_value;
      position *= 10;
    } else {
      numberParts.push_back(adder);
      position /= BIGADDER_DIVIDER;
      adder = next_digit * position;
      position *= 10;
    }
  }
  if (adder > 0) {
    numberParts.push_back(adder);
  }
}

// Copy constructor
BigAdder::BigAdder(const BigAdder& other)
  : numberParts(other.numberParts)
{
}

// Move constructor
BigAdder::BigAdder(BigAdder&& other)
  : numberParts(std::move(other.numberParts))
{
}

BigAdder::~BigAdder()
{
}

// copy assignment
BigAdder& BigAdder::operator=(const BigAdder& other)
{
  numberParts = other.numberParts;
  return *this;
}

// move assignment
BigAdder& BigAdder::operator=(BigAdder&& other)
{
  numberParts = std::move(other.numberParts);
  return *this;
}

BigAdder& BigAdder::operator+=(const BigAdder& other)
{
  auto l = numberParts.begin();
  auto r = other.numberParts.cbegin();
  unsigned long long carry = 0ULL;
  for (; l != numberParts.end() && r != other.numberParts.cend(); ++l, ++r) {
    unsigned long long cur = *l;
    unsigned long long ext = *r;
    unsigned long long new_part = cur + ext + carry;
    if (new_part <= BIGADDERPART_MAX) {
      *l = new_part;
      carry = 0ULL;
    } else {
      carry = new_part / BIGADDER_DIVIDER;
      new_part %= BIGADDER_DIVIDER;
      *l = new_part;
    }
  }

  for (; l != numberParts.end(); ++l) {
    unsigned long long cur = *l;
    unsigned long long new_part = cur + carry;
    if (new_part <= BIGADDERPART_MAX) {
      *l = new_part;
      carry = 0ULL;
    } else {
      carry = new_part / BIGADDER_DIVIDER;
      new_part %= BIGADDER_DIVIDER;
      *l = new_part;
    }
  }

  for (; r != other.numberParts.cend(); ++r) {
    unsigned long long cur = *r;
    unsigned long long new_part = cur + carry;
    if (new_part <= BIGADDERPART_MAX) {
      numberParts.push_back(static_cast<unsigned>(new_part));
      carry = 0ULL;
    } else {
      carry = new_part / BIGADDER_DIVIDER;
      new_part %= BIGADDER_DIVIDER;
      numberParts.push_back(static_cast<unsigned>(new_part));
    }
  }

  if (carry) {
    numberParts.push_back(static_cast<unsigned>(carry));
    carry = 0ULL;
  }

  return *this;
}

BigAdder::operator std::string()
{
  std::string ret;
  for (auto i = numberParts.crbegin(); i != numberParts.crend(); ++i) {
    char buf[10];
    _ultoa_s(*i, buf, 10);

    if (i != numberParts.crbegin()) {
      // special case first part
      size_t len = strnlen_s(buf, 9);
      ret.append(9 - len, '0');
    } 
    ret += buf;
  }
  return ret;
}