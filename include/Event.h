#if !defined REAL_ENGINE_EVENT_H_
#define REAL_ENGINE_EVENT_H_

#include <unordered_set>
#include <atomic>
#include <mutex>
#include <sstream>
#include <condition_variable>

#include "Object.h"
#include "SingleBlocker.h"
#include "MultiBlocker.h"
#include "Handler.h"

namespace re {

template<typename ...Args>
class Event : public Object {
// Friend definitions =======

// Types ====================
 public:

 protected:

 private:

  struct Request {
    Handler<Args...> *handler;

    void (Event::*operation)(Handler<Args...> *);
  };

// Fields ===================
 public:

// Static members -----------

 protected:

 private:
  std::unordered_set<Handler<Args...> *> handlers_;

  std::vector<Request> requests_;

  MultiBlocker invoke_locker_;

  MultiBlocker request_locker_;

  SingleBlocker process_locker_;

  std::atomic<bool> process_busy_;

  std::atomic<bool> invoke_busy_;

// Methods ==================
 public:
// Constructors -------------

  Event() = default;

  Event(const Event &other) = delete;

  Event(Event &&other) noexcept = delete;

// Destructor ---------------

  ~Event() override = default;

// Getters ------------------

// Setters ------------------

// Other --------------------

  auto AddListener(Handler<Args...> *handler) -> void {
    if (invoke_locker_) {
      requests_.emplace_back(handler, &Event::AddListener);
    } else {
      handlers_.insert(handler);
    }
  }

  auto RemoveListener(Handler<Args...> *handler) -> void {
    if (invoke_locker_) {
      requests_.emplace_back(handler, &Event::RemoveListener);
    } else {
      handlers_.erase(handler);
    }
  }

  auto Invoke(Args... args) -> void {
    process_busy_.wait(true);
    InvokeHandlers(args...);
    UnlockProcessingRequests();

    if (!process_locker_.TryLock()) {
      return;
    }

    invoke_busy_.wait(true);
    ProcessRequests(args...);
    UnlockInvokingHandlers();
  }

  auto GetTypeInfo() const -> const std::type_info & override {
    return typeid(Event);
  }

// Operators ----------------

  auto operator=(const Event &other) -> Event & = delete;

  auto operator=(Event &&other) noexcept -> Event & = delete;

  auto operator+=(Handler<Args...> *handler) -> void {
    AddListener(handler);
  }

  auto operator-=(Handler<Args...> *handler) -> void {
    RemoveListener(handler);
  }

  auto operator()(Args... args) -> void {
    Invoke(args...);
  }

// Static members -----------

// Friendly functions -------

 protected:

 private:
  auto InvokeHandlers(Args... args) -> void {
    invoke_locker_.AddLock();
    for (auto &handler : handlers_) {
      handler->Invoke(args...);
    }

    invoke_locker_.RemoveLock();
  }

  auto UnlockProcessingRequests() -> void {
    if (!invoke_locker_.IsLocked()) {
      invoke_busy_ = false;
      invoke_busy_.notify_one();
    }
  }

  auto ProcessRequests(Args... args) -> void {
    if (requests_.empty()) {
      return;
    }

    for (const auto &request : requests_) {
      (this->*request.operation)(request.handler);
    }
    requests_.clear();
  }

  auto UnlockInvokingHandlers() -> void {
    if (!process_locker_.IsLocked()) {
      process_busy_ = false;
      process_busy_.notify_one();
    }
  }
}; // Event
} // re

#endif // REAL_ENGINE_EVENT_H_