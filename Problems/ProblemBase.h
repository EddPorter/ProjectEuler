#pragma once
#define WIN32_LEAN_AND_MEAN

#include <iostream>     // std::cout
#include <numeric>      // accumulate
#include <ostream>      // std::endl
#include <vector>       // vector
#include <Windows.h>    // LARGE_INTEGER, QueryPerformanceCounter,
                        // QueryPerformanceFrequency

#define DISCARDS 5
#define TRIALS  5

class ProblemBase {
public:
  virtual void Run() = 0;

protected:
  template <unsigned N>
  void time_method(int (*method)(void)) const;
};

static long long query_counter() {
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return li.QuadPart;
}

static long long query_frequency() {
  LARGE_INTEGER li;
  QueryPerformanceFrequency(&li);
  return li.QuadPart;
}

template <unsigned N>
void ProblemBase::time_method(int (*method)(void)) const {
  static const auto frequency = query_frequency();
  std::vector<double> times(TRIALS);
  for (auto i = 0; i < TRIALS + DISCARDS; ++i) {
    const auto start = query_counter();
    auto result = method();
    const auto finish = query_counter();
    if (i == 0) {
      std::cout << "Method " << N << ": " << result << std::endl;
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