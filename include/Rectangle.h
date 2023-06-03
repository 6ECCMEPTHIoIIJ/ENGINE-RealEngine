#if !defined REAL_ENGINE_RECTANGLE_H_
#define REAL_ENGINE_RECTANGLE_H_

#include <concepts>

#include "Object.h"

namespace re::utility {

template<typename T> requires std::is_arithmetic_v<T>
class Rectangle : public Object {
// Friend definitions =======

// Types ====================
 public:

 protected:

 private:

// Fields ===================
 public:

// Static members -----------

 protected:

 private:
  T left_;

  T top_;

  T right_;

  T bottom_;

// Methods ==================
 public:
// Constructors -------------
  Rectangle() = default;

  Rectangle(const Rectangle &other) = default;

  Rectangle(Rectangle &&other) noexcept = default;

  Rectangle(T left, T top, T right, T bottom)
      : left_(left), top_(top), right_(right), bottom_(bottom) {}

// Getters ------------------

  [[nodiscard]]
  auto GetLeft() const -> T {
    return left_;
  }

  [[nodiscard]]
  auto GetRight() const -> T {
    return right_;
  }

  [[nodiscard]]
  auto GetTop() const -> T {
    return top_;
  }

  [[nodiscard]]
  auto GetBottom() const -> T {
    return bottom_;
  }

// Setters ------------------

  auto SetTop(const T top) -> void {
    top_ = top;
  }

  auto SetBottom(const T bottom) -> void {
    bottom_ = bottom;
  }

  auto SetLeft(const T left) -> void {
    left_ = left;
  }

  auto SetRight(const T right) -> void {
    right_ = right;
  }



// Other --------------------

// Operators ----------------

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Rectangle
} // re::utility

#endif // REAL_ENGINE_RECTANGLE_H_
