#if !defined REAL_ENGINE_INCLUDE_VECTOR2_H_
#define REAL_ENGINE_INCLUDE_VECTOR2_H_

#include <concepts>
#include <format>

#include "Object.h"

namespace re::utility {

template<typename T> requires std::is_arithmetic_v<T>
class Vector2 : public Object {
// Friend definitions -------

// Types --------------------
 public:

 protected:

 private:

// Fields -------------------
 public:

// Static members -----------

  static const Vector2 kZero;

  static const Vector2 kUp;

  static const Vector2 kRight;

 protected:

 private:
  T x_{};

  T y_{};

// Methods ------------------
 public:
// Constructors -------------

  Vector2() = default;

  Vector2(const Vector2 &other) = default;

  Vector2(Vector2 &&other) noexcept = default;

  Vector2(T x, T y) : x_(x), y_(y) {}

// Getters ------------------

  [[nodiscard]]
  auto GetX() const -> T {
    return x_;
  }

  [[nodiscard]]
  auto GetY() const -> T {
    return y_;
  }

// Setters ------------------

  auto SetX(const T x) -> void {
    x_ = x;
  }

  auto SetY(const T y) -> void {
    y_ = y;
  }

// Other --------------------

  [[nodiscard]]
  auto ToString() const -> std::string override {
    return std::format("({};{})", x_, y_);
  }

  [[nodiscard]]
  auto GetTypeInfo() const -> const std::type_info & override {
    return typeid(Vector2);
  }

  [[nodiscard]]
  auto IsEqual(const Object *other) const -> bool override {
    auto other_vector2 = dynamic_cast<const Vector2 *>(other);
    return x_ == other_vector2->x_ &&
        y_ == other_vector2->y_;
  }

// Operators ----------------

  auto operator=(const Vector2 &other) -> Vector2 & = default;

  auto operator=(Vector2 &&other) noexcept -> Vector2 & = default;

  auto operator+=(const Vector2 &other) -> Vector2 & {
    x_ += other.x_;
    y_ += other.y_;

    return *this;
  }

  auto operator-=(const Vector2 &other) -> Vector2 & {
    x_ -= other.x_;
    y_ -= other.y_;

    return *this;
  }

  auto operator*=(const T other) -> Vector2 & {
    x_ *= other;
    y_ *= other;

    return *this;
  }

  auto operator/=(const T other) -> Vector2 & {
    x_ /= other;
    y_ /= other;

    return *this;
  }

  auto operator-() -> Vector2 {
    return Vector2(-x_, -y_);
  }

  auto operator+() -> const Vector2 & {
    return *this;
  }

  auto operator+(const Vector2 &other) -> Vector2 {
    return Vector2(*this) += other;
  }

  auto operator-(const Vector2 &other) -> Vector2 {
    return Vector2(*this) -= other;
  }

  auto operator*(const T other) -> Vector2 {
    return Vector2(*this) *= other;
  }

  auto operator/(const T other) -> Vector2 {
    return Vector2(*this) /= other;
  }

  [[nodiscard]]
  auto operator==(const Vector2& other) const -> bool {
    return IsEqual(&other);
  }

  [[nodiscard]]
  auto operator!=(const Vector2& other) const -> bool {
    return !IsEqual(&other);
  }
// Static members -----------



// Friendly functions -------

  friend auto operator*(const T left, const Vector2 &right) -> Vector2 {
    return right * left;
  }

 protected:

 private:
}; // Vector2

template<typename T> requires std::is_arithmetic_v<T>
const Vector2<T> Vector2<T>::kZero{};

template<typename T> requires std::is_arithmetic_v<T>
const Vector2<T> Vector2<T>::kUp{0, 1};

template<typename T> requires std::is_arithmetic_v<T>
const Vector2<T> Vector2<T>::kRight{1, 0};
} // re::utility

#endif // REAL_ENGINE_INCLUDE_VECTOR2_H_
