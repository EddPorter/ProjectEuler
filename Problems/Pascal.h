#pragma once

#include <map>        // map
#include <utility>    // make_pair, pair

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

unsigned long long CalculatePascal(unsigned n, unsigned k) {
  static std::map<std::pair<unsigned, unsigned>, unsigned long long> cache;
  if (n == k || k == 0) {
    return 1ULL;
  }
  auto i = cache.find(std::make_pair(n, k));
  if (i != cache.end()) {
    return (*i).second;
  }
  auto result = CalculatePascal(n - 1, k - 1) + CalculatePascal(n - 1, k);
  cache[std::make_pair(n, k)] = result;
  cache[std::make_pair(n, n - k)] = result;
  return result;
}

template<unsigned Mod>
unsigned long long CalculatePascal(unsigned n, unsigned k) {
  static std::map<std::pair<unsigned, unsigned>, unsigned long long> cache;
  if (n == k || k == 0) {
    return 1ULL;
  }
  auto i = cache.find(std::make_pair(n, k));
  if (i != cache.end()) {
    return (*i).second;
  }
  auto result = (CalculatePascal(n - 1, k - 1) + CalculatePascal(n - 1, k)) % Mod;
  cache[std::make_pair(n, k)] = result;
  cache[std::make_pair(n, n - k)] = result;
  return result;
}