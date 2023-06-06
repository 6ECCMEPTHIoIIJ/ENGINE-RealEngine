#if !defined REAL_ENGINE_HANDLER_H_
#define REAL_ENGINE_HANDLER_H_

#include <functional>
#include <format>
#include <mutex>

#include "Object.h"

namespace re::multithreading {

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

  mutable std::mutex mutex_;

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
  auto Bind(const Functor &functor, C *owner,  BindArgs... bind_args) -> void {
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
    std::lock_guard lock_guard(mutex_);
    function_(args...);
  }

// Operators ----------------

  auto operator=(const Handler &other) -> Handler & = delete;

  auto operator=(Handler &&other) noexcept -> Handler & = delete;

  auto operator()(Args... args) -> void {
    Invoke(args...);
  }

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Handler
} // re::multithreading

#endif // REAL_ENGINE_HANDLER_H_