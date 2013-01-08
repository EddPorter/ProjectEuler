#pragma once

class ProjectEuler;

typedef unsigned long long (ProjectEuler::*ProjectEulerMemFn)() const;

class ProjectEuler
{
public:
  void RunMenuLoop() const;

private:
  unsigned long long Problem1() const;
  unsigned long long Problem2() const;
  unsigned long long Problem3() const;
  unsigned long long Problem4() const;
  unsigned long long Problem5() const;
  unsigned long long Problem6() const;
  unsigned long long Problem7() const;
  unsigned long long Problem8() const;
  unsigned long long Problem9() const;
  unsigned long long Problem10() const;
  unsigned long long Problem11() const;
  unsigned long long Problem12() const;
  unsigned long long Problem13() const;
  unsigned long long Problem14() const;
  unsigned long long Problem15() const;
  unsigned long long Problem16() const;
  unsigned long long Problem17() const;
  unsigned long long Problem18() const;

  void RunAndTimeMethod(ProjectEulerMemFn problem) const;
};