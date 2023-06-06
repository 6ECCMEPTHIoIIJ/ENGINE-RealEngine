#if !defined REAL_ENGINE_SINGLE_BLOCKER_H_
#define REAL_ENGINE_SINGLE_BLOCKER_H_

#include <atomic>
#include <mutex>

#include "Object.h"

namespace re::multithreading {

class SingleBlocker : public Object {
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

  std::atomic<bool> locked_;

  mutable std::mutex mutex_;

// Methods ==================
 public:
// Constructors -------------

  SingleBlocker() = default;

  SingleBlocker(const SingleBlocker &other) = delete;

  SingleBlocker(SingleBlocker &&other) = delete;

// Destructor ---------------

  ~SingleBlocker() override = default;

// Getters ------------------

  [[nodiscard]]
  auto IsLocked() const -> bool {
    return locked_;
  }

// Setters ------------------

// Other --------------------

  auto Lock() -> void {
    locked_ = true;
  }

  auto Unlock() -> void {
    locked_ = false;
  }

  auto TryLock() -> bool {
    std::lock_guard lock_guard(mutex_);
    if (IsLocked()) {
      return false;
    }

    Lock();
    return true;
  }

  auto TryUnlock() -> bool {
    std::lock_guard lock_guard(mutex_);
    if (!IsLocked()) {
      return false;
    }

    Unlock();
    return true;
  }

// Operators ----------------

  explicit operator bool() const {
    return IsLocked();
  }

  auto operator=(const SingleBlocker &other) -> SingleBlocker & = delete;

  auto operator=(SingleBlocker &&other) -> SingleBlocker & = delete;

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // SingleBlocker
} // re::multithreading

#endif // REAL_ENGINE_SINGLE_BLOCKER_H_