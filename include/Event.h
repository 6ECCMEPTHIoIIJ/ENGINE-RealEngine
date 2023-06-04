#if !defined REAL_ENGINE_EVENT_H_
#define REAL_ENGINE_EVENT_H_

#include <unordered_set>
#include <atomic>

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
  std::unordered_set<Handler<Args...>> handlers_;

  std::vector<Request> requests_;

  std::atomic<uint16_t> busy_ = 0;

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
      requests_.push(handler, &Event::AddListener);
    } else {
      handlers_.insert(handler);
    }
  }

  auto RemoveListener(Handler<Args...> *handler) -> void {
    if (busy_ != 0) {
      requests_.push(handler, &Event::RemoveListener);
    } else {
      handlers_.erase(handler);
    }
  }

  auto Invoke(Args... args) -> void {
    ++busy_;
    for (auto &handler : handlers_) {
      handler->Invoke();
    }
    --busy_;

    if (requests_.empty()) {
      return;
    }

    for (auto &request : requests_) {
      request.operation(request.handler);
    }
    requests_.clear();
  }

// Operators ----------------

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Event
} // re

#endif // REAL_ENGINE_EVENT_H_