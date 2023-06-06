#include <iostream>

#include "Vector2.h"
#include "Event.h"

class B {
 public:
  re::multithreading::Event<int> OnBar;

  B() = default;
};

class A {
 public:
  re::multithreading::Handler<int> h;

  A(int a) {
    h.Bind(&A::Foo, this, a);
  }

 private:
  int Foo(const int a, const int b) {
    std::cout << std::format("{} {}\n", a, b);
    return a;
  }
};

int main() {
  B b;
  A a(10);
  A a1(123);
  A a2(42);
  A a3(0);
  A a4(123213);
  b.OnBar.AddListener(&a.h);
  std::thread([&] { while (true) { b.OnBar(5); }}).detach();
  b.OnBar.AddListener(&a1.h);
  std::thread([&] { while (true) { b.OnBar(12); }}).detach();
  std::thread([&] { while (true) { b.OnBar(-3125); }}).detach();
  b.OnBar.AddListener(&a2.h);
  std::thread([&] { while (true) { b.OnBar(124); }}).detach();
  std::thread([&] { while (true) { b.OnBar(432); }}).detach();
  std::thread([&] { while (true) { b.OnBar(87); }}).detach();
  std::thread([&] { while (true) { b.OnBar(32); }}).detach();
  b.OnBar.AddListener(&a3.h);
  std::thread([&] { while (true) { b.OnBar(82342); }}).detach();
  std::thread([&] { while (true) { b.OnBar(3523); }}).detach();
  std::thread([&] { while (true) { b.OnBar(234534); }}).detach();
  std::thread([&] { while (true) { b.OnBar(74367); }}).detach();
  b.OnBar.AddListener(&a4.h);
  std::thread([&] { while (true) { b.OnBar(357543); }}).detach();
  std::thread([&] { while (true) { b.OnBar(35654); }}).detach();
  std::thread([&] { while (true) { b.OnBar(871234); }}).detach();
  std::thread([&] { while (true) { b.OnBar(0); }}).detach();
  std::thread([&] { while (true) { b.OnBar(7); }}).join();

  re::utility::Vector2<int> v = {0, 1};
}