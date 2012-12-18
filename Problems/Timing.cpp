#include "Timing.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>    // LARGE_INTEGER, QueryPerformanceCounter,
                        // QueryPerformanceFrequency


long long QueryCounter() {
  LARGE_INTEGER li;
  QueryPerformanceCounter(&li);
  return li.QuadPart;
}

long long QueryFrequency() {
  LARGE_INTEGER li;
  QueryPerformanceFrequency(&li);
  return li.QuadPart;
}