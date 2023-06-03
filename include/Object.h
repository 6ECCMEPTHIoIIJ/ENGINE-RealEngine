#if !defined REAL_ENGINE_OBJECT_H_
#define REAL_ENGINE_OBJECT_H_

#include <string>
#include <typeinfo>

namespace re {

class Object {
// Friend definitions =======

// Types ====================
 public:

 protected:

 private:

// Fields ===================
 public:

// Static members -----------

 protected:
  std::hash<const Object *> hash_;

 private:

// Methods ==================
 public:
// Constructors -------------


// Getters ------------------

// Setters ------------------

// Other --------------------

  [[nodiscard]]
  virtual auto ToString() const -> std::string = 0;

  [[nodiscard]]
  virtual auto GetTypeInfo() const -> const std::type_info & = 0;

  [[nodiscard]]
  virtual auto GetHashCode() const -> std::size_t {
    return hash_(this);
  }

  [[nodiscard]]
  virtual auto IsEqual(const Object *other) const -> bool = 0;

// Operators ----------------

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Object
} // re

#endif // REAL_ENGINE_OBJECT_H_