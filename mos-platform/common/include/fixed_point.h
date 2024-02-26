// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _FIXED_POINT_H
#define _FIXED_POINT_H

#include <cstdint>
#include <limits.h>
#include <type_traits>
#include <stdio.h>

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
template<uint8_t ISize, uint8_t FSize, bool Signed = true> class FixedPoint;

template<uint8_t ISize, uint8_t FSize, bool Signed>
class FixedPoint {
private:
  template <typename R>
  static constexpr R bitMask(uint64_t onecount) {
    return static_cast<R>(-(onecount != 0))
      & (static_cast<R>(-1) >> ((sizeof(R) * CHAR_BIT) - onecount));
  }

  template<uint8_t LeftISize, uint8_t RightISize>
  static constexpr _BitInt(RightISize) signExtensionMask(_BitInt(LeftISize) in) {
    if constexpr (LeftISize < RightISize) {
      // Need to sign extend since the new size is greater than old size
      return (in & (1 << LeftISize)) != 0 ? bitMask(RightISize - LeftISize) << LeftISize : 0;
    } else {
      // We are truncating or not changing size, so don't do sign extension
      return 0;
    }
  }

  // Size of the underlying storage for the different views of the data.
  // The total combined storage will be used for representing the actual value.
  static constexpr auto roundSizeUp(uint64_t v) {
    return ((v + 7) / 8) * 8;
  }
  using StorageSizeT = _BitInt(roundSizeUp(ISize + FSize));
  using StorageType = std::conditional_t<Signed, StorageSizeT, std::make_unsigned_t<StorageSizeT>>;

  // Underlying storage for the type
  union {
    StorageType val;
    struct {
      StorageType i : ISize;
      StorageType f : FSize;
    };
  };

public:

  // Constructors

  /// Common constructor for creating a fixed point value from an integer value
  [[clang::always_inline]] constexpr FixedPoint(StorageType i) {
    set_i(i); 
  }
  
  /// Copy constructor for a fixed point value with different sizes of Int
  /// If both of the two fixed point values are signed, the new number will be
  /// sign extended from the old value
  template<uint8_t OI, uint8_t OF, bool S,
    typename std::enable_if<OI >= ISize && OF == FSize, bool>::type = true>
  [[clang::always_inline]] constexpr FixedPoint(const FixedPoint<OI, OF, S>& o) {
    // Perform sign extension if both of the two types are signed
    auto intval = o.as_i();
    if constexpr(Signed && S) {
      intval |= signExtensionMask<OI, ISize>(intval);
    }
    auto floatval = o.as_f();
    val = FixedPoint<ISize, FSize, Signed>(intval, floatval).get();
  }
  /// Copy constructor for a fixed point value with different sizes of FracSize
  /// This constructor will rescale the fractional value to the new size by shifting
  /// the fractional value by the difference between the size of the two.
  template<uint8_t OI, uint8_t OF, bool S,
    typename std::enable_if<OI >= ISize && OF != FSize, bool>::type = true>
  [[clang::always_inline]] constexpr explicit FixedPoint(const FixedPoint<OI, OF, S>& o) {
    // Perform sign extension if both of the two types are signed
    auto intval = o.as_i();
    if constexpr(Signed && S) {
      intval |= signExtensionMask<OI, ISize>(intval);
    }
    // Recalculate the fractional value since the bases are different
    constexpr auto shift = FSize > OF ? (FSize - OF) : (OF - FSize);
    auto floatval = FSize > OF ? o.as_f() << shift : o.as_f() >> shift;
    val = FixedPoint<ISize, FSize, Signed>(intval, floatval).get();
  }
  /// Copy constructor for a fixed point value with a smaller sized integer field.
  /// This constructor will TRUNCATE the integer value to fit the new size,
  /// and rescale the fractional value to the new size by shifting the fractional value
  /// by the difference between the size of the two.
  template<uint8_t OI, uint8_t OF, bool S,
    typename std::enable_if<OI < ISize, bool>::type = true>
  [[clang::always_inline]] constexpr explicit FixedPoint(const FixedPoint<OI, OF, S>& o) {
    // Recalculate the decimal value if the bases are different
    auto floatval = o.as_f();
    if constexpr (OF != FSize) {
      constexpr auto shift = FSize > OF ? (FSize - OF) : (OF - FSize);
      floatval = FSize > OF ? floatval << shift : floatval >> shift;
    }
    val = FixedPoint<ISize, FSize, Signed>(o.as_i(), floatval).get();
  }

  /// Copy constructor for fixed point values with the same size
  [[clang::always_inline]] constexpr FixedPoint(const FixedPoint& o) : val(o.val) {}
  
  /// Constructor for setting both the integral and fractional part
  [[clang::always_inline]] constexpr FixedPoint(StorageType i, StorageType f) 
    : i(i), f(f) {}
#if __cplusplus >= 202002L
  /// Constructor to convert floating point values into fixed point
  /// Multiplying by a power of two only increases the exponent of the 
  /// floating point number, which is exact so long as overflow does not occur.
  /// Rounding a floating point number to whole is always exact.
  [[clang::always_inline]] consteval explicit FixedPoint(long double f) { set(f * (1 << FSize)); }
  [[clang::always_inline]] consteval explicit FixedPoint(double f) { set(f * (1 << FSize)); }
  [[clang::always_inline]] consteval explicit FixedPoint(float f) { set(f * (1 << FSize)); }
#else
  [[clang::always_inline]] constexpr explicit FixedPoint(long double f) { set(f * (1 << FSize)); }
  [[clang::always_inline]] constexpr explicit FixedPoint(double f) { set(f * (1 << FSize)); }
  [[clang::always_inline]] constexpr explicit FixedPoint(float f) { set(f * (1 << FSize)); }
#endif

  // Direct value accessor and setter methods

  /// Returns just the integral portion
  [[clang::always_inline]] constexpr StorageType as_i() const { return i; }
  /// Returns just the fractional portion
  [[clang::always_inline]] constexpr StorageType as_f() const { return f; }
  /// Returns the entire value
  [[clang::always_inline]] constexpr StorageType get() const { return val; }
  /// Update just the integral portion
  [[clang::always_inline]] constexpr void set_i(StorageType value) { 
    i = value;
  }
  /// Update just the fractional portion
  [[clang::always_inline]] constexpr void set_f(StorageType value) { 
    f = value;
  }
  /// Update the entire value
  [[clang::always_inline]] constexpr void set(StorageType value) { val = value; }

  /// Conversion to another fixed point type can be done losslessly if the new type
  template<uint8_t OI, uint8_t OF, bool S = true>
  [[clang::always_inline]] constexpr FixedPoint<OI, OF, S> as() {
    return FixedPoint<OI, OF, S>(*this);
  }

  // Operator overloads
  [[clang::always_inline]] constexpr FixedPoint& operator=(FixedPoint o) {
    val = o.val;
    return *this;
  }

  [[clang::always_inline]] constexpr FixedPoint operator +(FixedPoint o) const {
    FixedPoint n = *this;
    n += o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator +=(FixedPoint o) {
    val += o.val;
    return *this;
  }

  [[clang::always_inline]] constexpr FixedPoint operator -(FixedPoint o) const {
    FixedPoint n = *this;
    n -= o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator -=(FixedPoint o) {
    val -= o.val;
    return *this;
  }

  [[clang::always_inline]] constexpr FixedPoint operator/(StorageType i) {
    FixedPoint n = *this;
    n /= i;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator/=(StorageType i) {
    val /= i;
    return *this;
  }

  [[clang::always_inline]] constexpr FixedPoint operator*(StorageType i) {
    FixedPoint n = *this;
    n *= i;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator*=(StorageType i) {
    val *= i;
    return *this;
  }

  [[clang::always_inline]] constexpr FixedPoint operator >>(StorageType v) const {
    FixedPoint n = *this;
    n >>= v;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator >>=(StorageType v) {
    val >>= v;
    return *this;
  }
  
  [[clang::always_inline]] constexpr FixedPoint operator <<(StorageType v) const {
    FixedPoint n = *this;
    n <<= v;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator <<=(StorageType v) {
    val <<= v;
    return *this;
  }

  [[clang::always_inline]] FixedPoint &operator++() {
    i += 1;
    return *this;
  }
  [[clang::always_inline]] FixedPoint operator++(int) {
    FixedPoint old = *this;
    ++*this;
    return old;
  }

  // Comparison overloads
  [[clang::always_inline]] constexpr friend bool operator==(const FixedPoint& a, const FixedPoint& b) noexcept {
    return a.val == b.val;
  }
  [[clang::always_inline]] constexpr friend bool operator< (const FixedPoint& a, const FixedPoint& b) noexcept {
    return a.val < b.val;
  }
  [[clang::always_inline]] constexpr friend bool operator!=(const FixedPoint& a, const FixedPoint& b) noexcept {
    return !(a == b);
  }
  [[clang::always_inline]] constexpr friend bool operator> (const FixedPoint& a, const FixedPoint& b) noexcept {
    return b < a;
  }
  [[clang::always_inline]] constexpr friend bool operator>=(const FixedPoint& a, const FixedPoint& b) noexcept {
    return !(a < b);
  }
  [[clang::always_inline]] constexpr friend bool operator<=(const FixedPoint& a, const FixedPoint& b) noexcept {
    return !(b < a);
  }

  [[clang::always_inline]] constexpr friend bool operator==(const FixedPoint& a, StorageType b) noexcept {
    return a.i == b && a.f == 0;
  }
  [[clang::always_inline]] constexpr friend bool operator< (const FixedPoint& a, StorageType b) noexcept {
    return a.i < b;
  }
  [[clang::always_inline]] constexpr friend bool operator!=(const FixedPoint& a, StorageType b) noexcept {
    return !(a == b);
  }
  [[clang::always_inline]] constexpr friend bool operator> (const FixedPoint& a, StorageType b) noexcept {
    return b < a;
  }
  [[clang::always_inline]] constexpr friend bool operator>=(const FixedPoint& a, StorageType b) noexcept {
    return !(a < b);
  }
  [[clang::always_inline]] constexpr friend bool operator<=(const FixedPoint& a, StorageType b) noexcept {
    return !(b < a);
  }

  [[clang::always_inline]] constexpr friend bool operator==(StorageType a, const FixedPoint& b) noexcept {
    return a == b.i && b.f == 0;
  }
  [[clang::always_inline]] constexpr friend bool operator< (StorageType a, const FixedPoint& b) noexcept {
    return !(a < b);
  }
  [[clang::always_inline]] constexpr friend bool operator!=(StorageType a, const FixedPoint& b) noexcept {
    return !(a == b);
  }
  [[clang::always_inline]] constexpr friend bool operator> (StorageType a, const FixedPoint& b) noexcept {
    return a.i < b;
  }
  [[clang::always_inline]] constexpr friend bool operator>=(StorageType a, const FixedPoint& b) noexcept {
    return !(a < b);
  }
  [[clang::always_inline]] constexpr friend bool operator<=(StorageType a, const FixedPoint& b) noexcept {
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
namespace fixedpoint_literals {

using FP_S8_8 = FixedPoint<8, 8, true>;
using FP_S12_4 = FixedPoint<12, 4, true>;
using FP_U8_8 = FixedPoint<8, 8, false>;
using FP_U12_4 = FixedPoint<12, 4, false>;
using FP_8_8 = FP_S8_8;
using FP_12_4 = FP_S12_4;

#if __cplusplus >= 202002L
[[clang::always_inline]] consteval FP_S8_8 operator ""_s8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] consteval FP_S12_4 operator ""_s12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] consteval FP_U8_8 operator ""_u8_8(long double fixed) {
  return FixedPoint<8,8,false>{fixed};
}
[[clang::always_inline]] consteval FP_U12_4 operator ""_u12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] consteval FP_8_8 operator ""_8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] consteval FP_12_4 operator ""_12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
#else
[[clang::always_inline]] constexpr FP_S8_8 operator ""_s8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] constexpr FP_S12_4 operator ""_s12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] constexpr FP_U8_8 operator ""_u8_8(long double fixed) {
  return FixedPoint<8,8,false>{fixed};
}
[[clang::always_inline]] constexpr FP_U12_4 operator ""_u12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] constexpr FP_8_8 operator ""_8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] constexpr FP_12_4 operator ""_12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
#endif
} // namespace fixedpoint_literals

#endif // _FIXED_POINT_H
