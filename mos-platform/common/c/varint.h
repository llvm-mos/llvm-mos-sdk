#ifndef _VARINT_H_
#define _VARINT_H_

#include <new>
#include <type_traits>

namespace __impl {

// An unsigned variable-length integer. Must be implemented by a specific
// instantiation of BigInt.
class VarInt {
  char size;

  char *bytes() { return &size + 1; };
  const char *bytes() const { return &size + 1; };

public:
  VarInt() = delete;
  VarInt(const VarInt &other) = delete;

  template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  VarInt &operator=(T other) {
    *reinterpret_cast<T *>(bytes()) = other;
    return *this;
  }

  VarInt &operator=(const VarInt &other);

  template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  operator T() const {
    return *reinterpret_cast<const T *>(bytes());
  }

  bool operator==(const VarInt &other) const;
  bool operator!=(const VarInt &other) const;

  bool operator<(const VarInt &other) const;
  bool operator<=(const VarInt &other) const;
  bool operator>(const VarInt &other) const;
  bool operator>=(const VarInt &other) const;

  // True if larger than the largest signed value.
  bool too_positive() const;

  // True if larger than the absolute value of the smallest signed value.
  bool too_negative() const;

  VarInt &operator+=(const VarInt &other);
  bool add_overflow(const VarInt &other);

  template <typename T> VarInt &operator+=(T other);
  template <typename T> VarInt &operator*=(T other);

  template <typename T> bool add_overflow(T other);
  template <typename T> bool mul_overflow(T other);
  bool shl_overflow();

  void negate();
  void shl();

  void zero();
  void positive_limit();
  void negative_limit();
  void unsigned_limit();

  void dump() const;

protected:
  VarInt(char size) : size(size) {}
};

// A variable-sized integer with compile-time constant size. Provides a way to
// instantiate a VarInt; otherwise has no specific functionality, in order to
// avoid monomorphization of sizes.
template <char Size> class BigInt : public VarInt {
  char bytes[Size];

public:
  BigInt() : VarInt(Size) {}

  template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  BigInt &operator=(T other) {
    static_assert(sizeof(T) == Size, "incorrect size");
    return static_cast<BigInt &>(VarInt::operator=(other));
  }

  template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
  BigInt(T other) : VarInt(Size) {
    static_assert(sizeof(T) == Size, "incorrect size");
    *this = other;
  }
};

template <typename T> VarInt &VarInt::operator+=(T other) {
  add_overflow(other);
  return *this;
}

template <typename T> VarInt &VarInt::operator*=(T other) {
  mul_overflow(other);
  return *this;
}

template <typename T> bool VarInt::add_overflow(T other) {
  unsigned char carry = 0;
  char i;
  const auto *r_bytes = reinterpret_cast<const char *>(&other);
  for (i = 0; i < sizeof(T); ++i)
    bytes()[i] = __builtin_addcb(bytes()[0], r_bytes[i], carry, &carry);
  for (; i < size; ++i)
    bytes()[i] = __builtin_addcb(bytes()[i], 0, carry, &carry);
  return carry;
}

template <typename T> bool VarInt::mul_overflow(T other) {
  char space[sizeof(VarInt) + size]; // VLA
  auto &p = *new (space) VarInt(size);
  p.zero();
  bool overflow = false;
  while (true) {
    if (other & 1) {
      --other;
      overflow |= p.add_overflow(*this);
    }
    if (!other)
      break;
    other >>= 1;
    overflow |= shl_overflow();
  }
  *this = p;
  return overflow;
}

} // namespace __impl

#endif // not _VARINT_H_
