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

namespace re::multithreading {

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

  std::atomic<bool> request_busy_;

  mutable std::mutex handler_modify_mutex_;

  mutable std::mutex request_modify_mutex_;

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
    if (invoke_locker_.IsLocked()) {
      std::lock_guard lock_guard(request_modify_mutex_);
      requests_.emplace_back(handler, &Event::AddListener);
    } else {
      LockModifyingRequests();
      InsertHandler(handler);
      UnlockModifyingRequests();
    }
  }

  auto RemoveListener(Handler<Args...> *handler) -> void {
    if (invoke_locker_.IsLocked()) {
      std::lock_guard lock_guard(request_modify_mutex_);
      requests_.emplace_back(handler, &Event::RemoveListener);
    } else {
      LockModifyingRequests();
      EraseHandler(handler);
      UnlockModifyingRequests();
    }
  }

  auto Invoke(Args... args) -> void {
    process_busy_.wait(true);
    LockProcessingRequests();
    InvokeHandlers(args...);
    UnlockProcessingRequests();

    if (!process_locker_.TryLock()) {
      return;
    }

    LockInvokingHandlers();
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

  auto LockProcessingRequests() -> void {
    invoke_busy_ = true;
  }

  auto UnlockProcessingRequests() -> void {
    if (!invoke_locker_.IsLocked()) {
      invoke_busy_ = false;
      invoke_busy_.notify_all();
    }
  }

  auto ProcessRequests(Args... args) -> void {
    if (requests_.empty()) {
      return;
    }

    for (const auto &request : requests_) {
      request_busy_.wait(true);
      ProcessRequest(request);
    }
    requests_.clear();
  }

  auto LockInvokingHandlers() -> void {
    process_busy_ = true;
  }

  auto UnlockInvokingHandlers() -> void {
    process_locker_.Unlock();
    process_busy_ = false;
    process_busy_.notify_all();
  }

  auto LockModifyingRequests() -> void {
    request_busy_ = true;
  }

  auto UnlockModifyingRequests() -> void {
    if (!request_locker_.IsLocked()) {
      request_busy_ = false;
      request_busy_.notify_all();
    }
  }

  auto InsertHandler(Handler<Args...> *handler) -> void {
    request_locker_.AddLock();
    handler_modify_mutex_.lock();
    handlers_.insert(handler);
    handler_modify_mutex_.unlock();
    request_locker_.RemoveLock();
  }

  auto EraseHandler(Handler<Args...> *handler) -> void {
    request_locker_.AddLock();
    handler_modify_mutex_.lock();
    handlers_.erase(handler);
    handler_modify_mutex_.unlock();
    request_locker_.RemoveLock();
  }

  auto ProcessRequest(const Request &request) -> void {
    std::lock_guard lock_guard(handler_modify_mutex_);
    (this->*request.operation)(request.handler);
  }
}; // Event
} // re::multithreading



#endif // REAL_ENGINE_EVENT_H_