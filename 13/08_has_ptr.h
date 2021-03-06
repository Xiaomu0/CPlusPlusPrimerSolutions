#ifndef CPS_CP13_EX08_H_
#define CPS_CP13_EX08_H_

#include <string>

class HasPtr {
public:
  HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}

  ~HasPtr() { delete ps; }
  HasPtr(const HasPtr &o) : ps(new std::string(*o.ps)), i(o.i) {}
  HasPtr &operator=(const HasPtr &rhs) {
    if (this != &rhs) { // maybe no need to do this?
      auto newp = new std::string(*rhs.ps);
      delete ps;
      ps = newp;
      i = rhs.i;
    }
    return *this;
  }

private:
  std::string *ps;
  int i;
};

#endif
