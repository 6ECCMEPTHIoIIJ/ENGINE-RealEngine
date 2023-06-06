#if !defined REAL_ENGINE_BLOCKER_H_
#define REAL_ENGINE_BLOCKER_H_

#include <cstdint>
#include <stdexcept>
#include <atomic>
#include <mutex>

#include "Object.h"

namespace re::multithreading {

class MultiBlocker : public Object {
// Friend definitions =======

// Types ====================
 public:

 protected:

 private:

// Fields ===================
 public:

// Static members -----------

 protected:

  std::atomic<uint32_t> count_ = 0;

  mutable std::mutex mutex_;

 private:

// Methods ==================
 public:
// Constructors -------------

  MultiBlocker() = default;

  MultiBlocker(const MultiBlocker &other) = delete;

  MultiBlocker(MultiBlocker &&other) = delete;

// Destructor ---------------

  ~MultiBlocker() override = default;

// Getters ------------------

  [[nodiscard]]
  auto IsLocked() const -> bool {
    return count_ != 0;
  }

  [[nodiscard]]
  auto GetTypeInfo() const -> const std::type_info & override {
    return typeid(MultiBlocker);
  }

// Setters ------------------

// Other --------------------

  auto AddLock() -> void {
    ++count_;
  }

  auto RemoveLock() -> void {
    std::lock_guard lock_guard(mutex_);
    if (!IsLocked()) {
      throw std::logic_error("Nothing to unlock");
    }

    --count_;
  }

// Operators ----------------

  auto operator=(const MultiBlocker &other) -> MultiBlocker & = delete;

  auto operator=(MultiBlocker &&other) -> MultiBlocker & = delete;

  explicit operator bool() const {
    return IsLocked();
  }

  auto operator++() -> void {
    AddLock();
  }

  auto operator--() -> void {
    RemoveLock();
  }

  auto operator++(int) -> void {
    AddLock();
  }

  auto operator--(int) -> void {
    RemoveLock();
  }

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // MultiBlocker
} // re::multithreading

#endif // REAL_ENGINE_BLOCKER_H_
