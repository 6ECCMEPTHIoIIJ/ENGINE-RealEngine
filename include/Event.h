#if !defined REAL_ENGINE_EVENT_H_
#define REAL_ENGINE_EVENT_H_

#include <set>

#include "Object.h"
#include "Handler.h"

namespace re {

class Event : public Object {
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

// Operators ----------------

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Event
} // re

#endif // REAL_ENGINE_EVENT_H_