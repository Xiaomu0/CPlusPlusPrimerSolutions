#ifndef CPS_CP13_EX05_H_
#define CPS_CP13_EX05_H_

#include <string>

class HasPtr {
public:
  HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}

  ~HasPtr() { delete ps; }
  HasPtr(const HasPtr &o) : ps(new std::string(*o.ps)), i(o.i) {}

private:
  std::string *ps;
  int i;
};

#endif
