#include <iostream>

#include "Vector2.h"
#include "Handler.h"

class A {
 public:
  re::Handler<int> h;
  re::Handler<int> h1;
 public:
  A() {
    h1.Bind(this, &A::Foo);
    h.Bind(this, &A::h1);
  }

  auto Foo(int a) -> int {
    std::cout << a;
    return a;

  }
};

int main() {
  A a;
  a.h(78);
}