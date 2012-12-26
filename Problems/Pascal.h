#pragma once

template<unsigned n, unsigned k>
class Pascal
{
public:
  enum Result : unsigned long long { Result = Pascal<n - 1, k - 1>::Result + Pascal<n - 1, k>::Result };
};

template<unsigned n>
class Pascal<n, 0>
{
public:
  enum Result : unsigned long long { Result = 1ULL };
};

template<unsigned n>
class Pascal<n, n>
{
public:
  enum Result : unsigned long long { Result = 1ULL };
};
