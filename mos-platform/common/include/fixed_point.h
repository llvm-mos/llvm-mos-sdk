

#ifndef _FIXED_POINT_H
#define _FIXED_POINT_H

// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <cstdint>
#include <limits.h>
#include <type_traits>

namespace fixedpoint {

/// Numeric Wrapper for Fixed Point math
///
/// Without dedicated floating point hardware, fixed point math is a good choice
/// for many llvm-mos targets. This class wraps common fixed point idioms
/// to provide a typesafe way to perform math operations that represent fractional
/// values.
///
/// For a quick primer on fixed point math, consider a simple case of a 8.8 fixed
/// point number. The first number represents the number of bits used to hold the
/// Integer portion of the value, and the second 8 bits hold the fractional portion.
/// This has some very useful properties for the 6502 such as when adding two fixed
/// point numbers with the same size, the math is the simply 16 bit math. Another
/// benefit is should you only want to use the integer portion of the value, accessing
/// this comes with no additional cost because its merely the high bytes. This
/// property is not true for all combination of sizes, but in general, it still is
/// reasonably quick to access the higher byte by shifting as needed.
///
/// In a little bit more detail, a fixed point number can be considered a regular
/// 16 bit number that is implicitly divided by the size of the fractional portion.
/// With our 8.8 example, the Fractional portion can represent 256 values total,
/// meaning the value in the fractional part represents a number divided by 256.
/// As a practical example, a 16 bit number `0x5060` , and when divided by `0x100`
/// yields `0x50` with a remainder of `0x60`. This class makes that divider a
/// part of the type of the class, allowing seamless math operations as if its a
/// normal integer, but with the correct shifting when combining with other values.
template<uint8_t ISize, uint8_t FSize, bool Signed = true> class Value;

template<uint8_t ISize, uint8_t FSize, bool Signed>
class Value {
protected:

  // Used to calculate the bitmasks for both the integer part and fractional part
  template <typename R>
  static constexpr R BitMask(unsigned int const onecount) {
    return static_cast<R>(-(onecount != 0))
      & (static_cast<R>(-1) >> ((sizeof(R) * CHAR_BIT) - onecount));
  }

  // Size of the underlying storage for the different views of the data.
  // The total combined storage will be used for representing the actual value.
  using IntType = std::conditional_t<Signed, 
                                     signed _BitInt(((ISize + 7) / 8) * 8),
                                     unsigned _BitInt(((ISize + 7) / 8) * 8)>;
  using FracType = std::conditional_t<Signed,
                                      signed _BitInt(((FSize + 7) / 8) * 8),
                                      unsigned _BitInt(((FSize + 7) / 8) * 8)>;
  using StorageType = std::conditional_t<Signed,
                                         signed _BitInt((((ISize + FSize) + 7) / 8) * 8),
                                         unsigned _BitInt((((ISize + FSize) + 7) / 8) * 8)>;
  StorageType val;
  static constexpr unsigned long INT_MASK = BitMask<unsigned long>(ISize) << FSize;
  static constexpr unsigned long FRAC_MASK = BitMask<unsigned long>(FSize);

public:

  // Constructors

  /// Common constructor for creating a fixed point value from an integer value
  [[clang::always_inline]] constexpr explicit Value(IntType i) {
    SetI(i); 
  }
  
  /// Copy constructor for a fixed point value with different sizes of Int/Frac
  template<uint8_t OI, uint8_t OF, bool S>
  [[clang::always_inline]] constexpr Value(const Value<OI, OF, S>& o) {
    val = Value<ISize, FSize>(o.AsI(), o.AsF()).Get();
  }
  /// Copy constructor for fixed point values with the same size
  [[clang::always_inline]] constexpr Value(const Value& o) : val(o.val) {}
  
  /// Constructor for setting both the integral and fractional part
  [[clang::always_inline]] constexpr explicit Value(IntType i, FracType f) {
    SetI(i);
    SetF(f);
  }
  /// Constructor to convert floating point values into fixed point
  [[clang::always_inline]] constexpr Value(long double f) {
    Set(f * (1 << FSize));
  }

  // Direct value accessor and setter methods

  /// Returns just the integral portion
  [[clang::always_inline]] constexpr IntType AsI() const { return (val & INT_MASK) >> FSize; }
  /// Returns just the fractional portion
  [[clang::always_inline]] constexpr FracType AsF() const { return (val & FRAC_MASK); }
  /// Returns the entire value
  [[clang::always_inline]] constexpr StorageType Get() const { return val; }
  /// Update just the integral portion
  [[clang::always_inline]] constexpr void SetI(IntType v) { 
    val = (val & ~INT_MASK) | static_cast<StorageType>((v) & (INT_MASK >> FSize)) << FSize;
  }
  /// Update just the fractional portion
  [[clang::always_inline]] constexpr void SetF(FracType v) { 
    val = (val & ~FRAC_MASK) | (v & FRAC_MASK);
  }
  /// Update the entire value
  [[clang::always_inline]] constexpr void Set(StorageType v) { val = v; }

  // Operator overloads
  [[clang::always_inline]] constexpr Value& operator=(Value o) {
    val = o.val;
    return *this;
  }

  [[clang::always_inline]] constexpr Value operator +(const Value& o) const {
    Value<ISize, FSize> n = val;
    n += o;
    return n;
  }
  [[clang::always_inline]] constexpr Value& operator +=(const Value& o) {
    val += o.val;
    return *this;
  }

  [[clang::always_inline]] constexpr Value operator -(const Value& o) const {
    Value<ISize, FSize> n = val;
    n -= o;
    return n;
  }
  [[clang::always_inline]] constexpr Value& operator -=(const Value& o) {
    val -= o.val;
    return *this;
  }

  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value operator/(T i) {
    Value<ISize, FSize> n{val};
    n /= i;
    return n;
  }
  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value& operator/=(T i) {
    val /= i;
    return *this;
  }

  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value operator*(T i) {
    Value<ISize, FSize> n{val};
    n *= i;
    return n;
  }
  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value& operator*=(T i) {
    val *= i;
    return *this;
  }

  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value operator >>(T v) const {
    Value<ISize, FSize> n = *this;
    n >>= v;
    return n;
  }
  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value& operator >>=(T v) {
    val >>= v;
    return *this;
  }
  
  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value operator <<(T v) const {
    Value<ISize, FSize> n = *this;
    n <<= v;
    return n;
  }
  template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  [[clang::always_inline]] constexpr Value& operator <<=(T v) {
    val <<= v;
    return *this;
  }

  [[clang::always_inline]] Value &operator++() {
    val += 1;
    return *this;
  }
  [[clang::always_inline]] Value operator++(int) {
    Value old = *this;
    ++*this;
    return old;
  }

  // Comparison overloads

  [[clang::always_inline]] constexpr friend bool operator==(const Value& a, const Value& b) noexcept {
    return a.val == b.val;
  }
  [[clang::always_inline]] constexpr friend bool operator< (const Value& a, const Value& b) noexcept {
    return a.val < b.val;
  }
  [[clang::always_inline]] constexpr friend bool operator!=(const Value& a, const Value& b) noexcept {
    return !(a == b);
  }
  [[clang::always_inline]] constexpr friend bool operator> (const Value& a, const Value& b) noexcept {
    return b < a;
  }
  [[clang::always_inline]] constexpr friend bool operator>=(const Value& a, const Value& b) noexcept {
    return !(a < b);
  }
  [[clang::always_inline]] constexpr friend bool operator<=(const Value& a, const Value& b) noexcept {
    return !(b < a);
  }

  [[clang::always_inline]] constexpr friend bool operator==(const Value& a, IntType b) noexcept {
    return a.val == b;
  }
  [[clang::always_inline]] constexpr friend bool operator< (const Value& a, IntType b) noexcept {
    return a.val < b;
  }
  [[clang::always_inline]] constexpr friend bool operator!=(const Value& a, IntType b) noexcept {
    return !(a == b);
  }
  [[clang::always_inline]] constexpr friend bool operator> (const Value& a, IntType b) noexcept {
    return b < a;
  }
  [[clang::always_inline]] constexpr friend bool operator>=(const Value& a, IntType b) noexcept {
    return !(a < b);
  }
  [[clang::always_inline]] constexpr friend bool operator<=(const Value& a, IntType b) noexcept {
    return !(b < a);
  }

  [[clang::always_inline]] constexpr friend bool operator==(IntType a, const Value& b) noexcept {
    return a == b.val;
  }
  [[clang::always_inline]] constexpr friend bool operator< (IntType a, const Value& b) noexcept {
    return a < b.val;
  }
  [[clang::always_inline]] constexpr friend bool operator!=(IntType a, const Value& b) noexcept {
    return !(a == b);
  }
  [[clang::always_inline]] constexpr friend bool operator> (IntType a, const Value& b) noexcept {
    return b < a;
  }
  [[clang::always_inline]] constexpr friend bool operator>=(IntType a, const Value& b) noexcept {
    return !(a < b);
  }
  [[clang::always_inline]] constexpr friend bool operator<=(IntType a, const Value& b) noexcept {
    return !(b < a);
  }
};


/// Helper namespace that contains a few common types and user defined literals
/// for converting from floating point numbers to fixed point numbers at compile time.
/// Usage example:
///
/// using namespace fixedpoint::literals;
/// FP_U8_8 number = 180.44_u8_8; // creates a number at compile-time == 0xb4e1
/// FP_S8_8 value = -60.89_s8_8;  // values can be signed or unsigned
/// auto inferred = 107.3_12_4;   // default is signed just like other int types
namespace literals {

using FP_S8_8 = Value<8, 8, true>;
using FP_S12_4 = Value<12, 4, true>;
using FP_U8_8 = Value<8, 8, false>;
using FP_U12_4 = Value<12, 4, false>;
using FP_8_8 = FP_S8_8;
using FP_12_4 = FP_S12_4;

[[clang::always_inline]] constexpr FP_S8_8 operator ""_s8_8(long double fixed) {
  return {fixed};
}
[[clang::always_inline]] constexpr FP_S12_4 operator ""_s12_4(long double fixed) {
  return {fixed};
}
[[clang::always_inline]] constexpr FP_U8_8 operator ""_u8_8(long double fixed) {
  return {fixed};
}
[[clang::always_inline]] constexpr FP_U12_4 operator ""_u12_4(long double fixed) {
  return {fixed};
}
[[clang::always_inline]] constexpr FP_8_8 operator ""_8_8(long double fixed) {
  return {fixed};
}
[[clang::always_inline]] constexpr FP_12_4 operator ""_12_4(long double fixed) {
  return {fixed};
}
} // namespace literals

} // namespace fixedpoint

#endif // _FIXED_POINT_H

