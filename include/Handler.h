#if !defined REAL_ENGINE_HANDLER_H_
#define REAL_ENGINE_HANDLER_H_

#include <functional>
#include <format>

#include "Object.h"

namespace re {

template<typename ...Args>
class Handler : public Object {
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

  std::function<void(Args...)> function_;

// Methods ==================
 public:
// Constructors -------------

  Handler() = default;

  Handler(const Handler &other) = delete;

  Handler(Handler &&other) = delete;

// Destructor ---------------

  ~Handler() override = default;

// Getters ------------------

  [[nodiscard]]
  auto GetTypeInfo() const -> const std::type_info & override {
    return typeid(Handler);
  }

// Setters ------------------

// Other --------------------

  template<typename C, typename Functor, typename ...BindArgs>
  auto Bind(C *owner, const Functor &functor, BindArgs... bind_args) -> void {
    function_ = [=](Args... args) -> void {
      (owner->*functor)(args..., bind_args...);
    };
  }

  template<typename Functor, typename ...BindArgs>
  auto Bind(const Functor &functor, BindArgs... bind_args) -> void {
    function_ = [=](Args... args) -> void {
      functor(args..., bind_args...);
    };
  }

  auto Invoke(Args... args) -> void {
    function_(args...);
  }

  [[nodiscard]]
  auto ToString() const -> std::string override {
    return function_.target_type().name();
  }

  auto IsEqual(const Object *other) const -> bool override {
    return false;
  }

// Operators ----------------

  auto operator()(Args... args) -> void {
    Invoke(args...);
  }

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Handler
} // re

#endif // REAL_ENGINE_HANDLER_H_