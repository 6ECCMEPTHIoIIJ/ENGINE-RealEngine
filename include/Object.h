#if !defined REAL_ENGINE_OBJECT_H_
#define REAL_ENGINE_OBJECT_H_

#include <string>
#include <typeinfo>
#include <sstream>

namespace re {

/// Base class of all classes contained in
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
  static std::hash<const Object *> hash_;

 private:

// Methods ==================
 public:
// Constructors -------------
  Object() = default;

  Object(const Object &other) = default;

  Object(Object &&other) = default;

// Destructor ---------------

  virtual ~Object() = default;

// Getters ------------------

/// Returns information about object type
  /// \return information about type (equals to invoke typeid(type))
  [[nodiscard]]
  virtual auto GetTypeInfo() const -> const std::type_info & {
    return typeid(Object);
  }

  /// \brief Gets hash code of current object
  /// \return hash code of current object
  [[nodiscard]]
  virtual auto GetHashCode() const -> std::size_t {
    return hash_(this);
  }

// Setters ------------------

// Other --------------------

  /// Coverts object to string
  /// \return string representation of object
  [[nodiscard]]
  virtual auto ToString() const -> std::string {
    std::stringstream ss;
    ss << dynamic_cast<const void *>(this);

    return ss.str();
  }

  ///
  /// \param other
  /// \return
  [[nodiscard]]
  virtual auto IsEqual(const Object *other) const -> bool {
    return this == other;
  }

// Operators ----------------

  auto operator=(const Object &other) -> Object & = default;

  auto operator=(Object &&other) -> Object & = default;

// Static members -----------

// Friendly functions -------

 protected:

 private:
}; // Object

std::hash<const Object *> Object::hash_;
} // re

#endif // REAL_ENGINE_OBJECT_H_