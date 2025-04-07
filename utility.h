#ifndef UTILITY_H
#define UTILITY_H

#include <functional>

class OnLeavingScope {
  private:
    std::function<void()> toDo;

  public:
    OnLeavingScope(std::function<void()> f) : toDo(f) {}
    ~OnLeavingScope() { toDo(); }
};

#endif
