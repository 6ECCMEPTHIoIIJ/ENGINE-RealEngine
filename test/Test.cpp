#include <iostream>

#include "Vector2.h"
#include "Event.h"

class B {
 public:
  re::Event<int> OnBar;

  B() = default;
};

class A {
 public:
  re::Handler<int> h;

  re::Handler<int> h1;

 public:
  A() {
    h1.Bind(&A::Foo, this, 15);
    h.Bind(&A::h1, this);
  }

  auto Foo(int a, int b) -> int {
    std::cout << a << b;
    return a;
  }
};

int main() {
  B b;
  A a;
  b.OnBar.AddListener(&a.h);
  b.OnBar += &a.h1;
  b.OnBar(5);
  b.OnBar -= &a.h;
  b.OnBar(7);

  re::utility::Vector2<int> v = {0, 1};
}