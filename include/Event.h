#if !defined REAL_ENGINE_EVENT_H_
#define REAL_ENGINE_EVENT_H_

#include <unordered_set>
#include <atomic>
#include <mutex>
#include <sstream>

#include "Object.h"
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

  std::atomic<uint16_t> busy_ = 0;

  mutable std::mutex mutex_;

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
    if (busy_ != 0) {
      requests_.emplace_back(handler, &Event::AddListener);
    } else {
      handlers_.insert(handler);
    }
  }

  auto RemoveListener(Handler<Args...> *handler) -> void {
    if (busy_ != 0) {
      requests_.emplace_back(handler, &Event::RemoveListener);
    } else {
      handlers_.erase(handler);
    }
  }

  auto Invoke(Args... args) -> void {
    ++busy_;
    for (auto &handler : handlers_) {
      handler->Invoke(args...);
    }
    --busy_;

    std::lock_guard lock_guard(mutex_);
    if (requests_.empty()) {
      return;
    }

    for (const auto &request : requests_) {
      (this->*request.operation)(request.handler);
    }
    requests_.clear();
  }

  auto GetTypeInfo() const -> const std::type_info & override {
    return typeid(Event);
  }

  auto ToString() const -> std::string override {
    std::stringstream ss;
    ss << "[ ";
    for (const auto &handler : handlers_) {
      ss << handler->ToString() << " ";
    }
    ss << "]";

    return ss.str();
  }

  auto IsEqual(const Object *other) const -> bool override {
    return this == other;
  }

// Operators ----------------

  auto operator=(const Event &other) -> Event & = delete;

  auto operator=(Event &&other) noexcept -> Event & = delete;

  auto operator+=(Handler<Args...> *handler) -> Event & {
    AddListener(handler);
    return *this;
  }

  auto operator-=(Handler<Args...> *handler) -> Event & {
    RemoveListener(handler);
    return *this;
  }

  auto operator()(Args... args) -> void {
    Invoke(args...);
  }

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Event
} // re

#endif // REAL_ENGINE_EVENT_H_