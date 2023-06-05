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

    A() {
      h.Bind(&A::Foo, this, 10);
    }
 private:
    int Foo(const int a, const int b) {
      std::cout << std::format("{} {}\n", a, b);
      return a;
    }
};

int main() {
  B b;
  A a;
  b.OnBar.AddListener(&a.h);
  b.OnBar += &a.h;
  b.OnBar(5);
  b.OnBar -= &a.h;
  b.OnBar(7);

  re::utility::Vector2<int> v = {0, 1};
}