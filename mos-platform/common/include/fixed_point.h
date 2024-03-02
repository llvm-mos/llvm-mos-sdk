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
template<intmax_t ISize, intmax_t FSize, bool Signed = true> class FixedPoint;

template<intmax_t ISize, intmax_t FSize, bool Signed>
class FixedPoint {
private:
  // Size of the underlying storage for the different views of the data.
  // The total combined storage will be used for representing the actual value.
  static constexpr auto roundSizeUp(uint64_t v) {
    return ((v + 7) / 8) * 8;
  }
  using StorageSizeT = _BitInt(roundSizeUp(ISize + FSize));
  using IntType = std::conditional_t<Signed, _BitInt(ISize), std::make_unsigned_t<_BitInt(ISize)>>;
  using FracType = std::conditional_t<Signed, _BitInt(FSize), std::make_unsigned_t<_BitInt(FSize)>>;
  using StorageType = std::conditional_t<Signed, StorageSizeT, std::make_unsigned_t<StorageSizeT>>;


  template<template<intmax_t, intmax_t> class Compare, class Op, intmax_t OtherISize, intmax_t OtherFSize, bool OtherSign>
  [[clang::always_inline]] constexpr auto binary_op(const FixedPoint<OtherISize, OtherFSize, OtherSign>& other) const {
    constexpr auto PromotedISize = Compare(ISize, OtherISize);
    constexpr auto PromotedFSize = Compare(FSize, OtherFSize);
    using Promoted = FixedPoint<PromotedISize, PromotedFSize, Signed && OtherSign>;
    Promoted l = *this;
    Promoted r = other;
    Promoted out{0};
    out.set(l.get(), r.get());
    return out;
  }

  // Underlying storage for the type
  union {
    StorageType val;
    struct {
      StorageType f : FSize;
      StorageType i : ISize;
    };
  };

public:

  // Constructors
  template <typename T, std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
  [[clang::always_inline]] constexpr FixedPoint(T i) {
    set_i(i);
  }

  /// Constructor to convert floating point values into fixed point
  /// Multiplying by a power of two only increases the exponent of the 
  /// floating point number, which is exact so long as overflow does not occur.
  /// Rounding a floating point number to whole is always exact.
#if __cplusplus >= 202002L
  template <typename T, std::enable_if_t<std::is_floating_pointr_v<T>, std::nullptr_t> = nullptr>
  [[clang::always_inline]] consteval explicit FixedPoint(T f) { set(f * ((StorageType)1 << FSize)); }
#else
  template <typename T, std::enable_if_t<std::is_floating_pointr_v<T>, std::nullptr_t> = nullptr>
  [[clang::always_inline]] constexpr explicit FixedPoint(T f) { set(f * ((StorageType)1 << FSize)); }
#endif

  // Implicit conversion constructor when there is no loss of data for upsizing the Fixedpoint
  // value. If the integer size is increasing, and the float size remains the same, then the conversion
  // does not lose information, so this conversion is safe.
  template<intmax_t OI, intmax_t OF, bool S,
    typename std::enable_if<(ISize >= OI && FSize == OF), bool>::type = true>
  [[clang::always_inline]] constexpr FixedPoint(const FixedPoint<OI, OF, S>& o) {
    StorageType intval;
    if constexpr(!Signed && S) {
      intval = (std::make_unsigned_t<_BitInt(OI)>) o.as_i();
    } else {
      intval = o.as_i();
    }
    *this = FixedPoint<ISize, FSize, Signed>(intval, o.as_f());
  }
  
  /// Copy constructor for a fixed point value with different sizes of FracSize
  /// or an ISize smaller than the original ISize which leads to truncation.
  /// This constructor will rescale the fractional value to the new size by shifting
  /// the fractional value by the difference between the size of the two and will also
  /// truncate the value of the integer if it doesn't fit the new size.
  template<intmax_t OI, intmax_t OF, bool S,
    typename std::enable_if<(ISize < OI || FSize != OF), bool>::type = true>
  [[clang::always_inline]] constexpr explicit FixedPoint(const FixedPoint<OI, OF, S>& o) {
    // Perform cast to unsigned if the old int is signed and the new one is unsigned
    StorageType intval;
    if constexpr(!Signed && S) {
      intval = (std::make_unsigned_t<_BitInt(OI)>) o.as_i();
    } else {
      intval = o.as_i();
    }
    
    StorageType floatval = o.as_f();
    if constexpr(OF != FSize) {
      // Recalculate the fractional value since the bases are different
      if constexpr(FSize > OF) {
        constexpr auto shift = FSize - OF;
        floatval <<= shift;
      } else {
        constexpr auto shift = OF - FSize;
        floatval >>= shift;
      }
    }
    *this = FixedPoint<ISize, FSize, Signed>(intval, floatval);
  }

  /// Copy constructor for fixed point values with the same size
  [[clang::always_inline]] constexpr FixedPoint(const FixedPoint& o) : val(o.val) {}
  
  /// Constructor for setting both the integral and fractional part
  [[clang::always_inline]] constexpr FixedPoint(StorageType i, StorageType f) 
    : i(i), f(f) {}

  // Direct value accessor and setter methods

  /// Returns just the integral portion
  [[clang::always_inline]] constexpr IntType as_i() const { return i; }
  /// Returns just the fractional portion
  [[clang::always_inline]] constexpr FracType as_f() const { return f; }
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

  /// Convert the fixed point value to a new fixed point value with a different size.
  /// This is just a convenience function to explicitly convert to a new fixed point type.
  template<intmax_t OI, intmax_t OF, bool S = true>
  [[clang::always_inline]] constexpr FixedPoint<OI, OF, S> as() {
    return FixedPoint<OI, OF, S>(*this);
  }

  [[clang::always_inline]] constexpr bool is_signed() const { return Signed; }
  [[clang::always_inline]] constexpr intmax_t bitcount() const { return ISize + FSize; }
  [[clang::always_inline]] constexpr intmax_t int_bitcount() const { return ISize; }
  [[clang::always_inline]] constexpr intmax_t frac_bitcount() const { return FSize; }

  // Operator overloads
  // Unary operators
  [[clang::always_inline]] constexpr FixedPoint& operator=(FixedPoint o) {
    val = o.val;
    return *this;
  }
  [[clang::always_inline]] constexpr FixedPoint operator -() const {
    FixedPoint<ISize, FSize, Signed> n = *this;
    n.set(-n.get());
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint operator ~() const {
    FixedPoint<ISize, FSize, Signed> n = *this;
    n.set(~n.get());
    return n;
  }
  // Bitwise operators
  [[clang::always_inline]] constexpr FixedPoint operator %(FixedPoint o) const {
    FixedPoint n = *this;
    n %= o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator %=(FixedPoint o) {
    val %= o.val;
    return *this;
  }
  [[clang::always_inline]] constexpr FixedPoint operator &(FixedPoint o) const {
    FixedPoint n = *this;
    n &= o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator &=(FixedPoint o) {
    val &= o.val;
    return *this;
  }
  [[clang::always_inline]] constexpr FixedPoint operator |(FixedPoint o) const {
    FixedPoint n = *this;
    n |= o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator |=(FixedPoint o) {
    val |= o.val;
    return *this;
  }
  [[clang::always_inline]] constexpr FixedPoint operator ^(FixedPoint o) const {
    FixedPoint n = *this;
    n ^= o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator ^=(FixedPoint o) {
    val ^= o.val;
    return *this;
  }

  // Arithimetic operators for same sized types
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

  [[clang::always_inline]] constexpr FixedPoint operator/(FixedPoint o) const {
    FixedPoint n = *this;
    n /= o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator/=(FixedPoint o) {
    val /= o.get();
    return *this;
  }

  [[clang::always_inline]] constexpr FixedPoint operator*(FixedPoint o) const {
    FixedPoint n = *this;
    n *= o;
    return n;
  }
  [[clang::always_inline]] constexpr FixedPoint& operator*=(FixedPoint o) {
    // Fixed point mult is (n * m / FSize)
    // Expand the immediate value before multiplying
    FixedPoint<ISize * 2, FSize, Signed> temp{*this};
    FixedPoint<ISize * 2, FSize, Signed> other{o};
    // Truncate the final result to fit inside our value
    val = (temp.get() * other.get()) >> FSize;
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
  
  // Operators that promote to the larger size
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator +(FixedPoint<OI, OF, S> o) const {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = o;
    l += r;
    return l;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator -(FixedPoint<OI, OF, S> o) const {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = o;
    l -= r;
    return l;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator %(FixedPoint<OI, OF, S> o) const {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = o;
    l %= r;
    return l;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator ^(FixedPoint<OI, OF, S> o) const {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = o;
    l ^= r;
    return l;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator &(FixedPoint<OI, OF, S> o) const {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = o;
    l &= r;
    return l;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator |(FixedPoint<OI, OF, S> o) const {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = o;
    l |= r;
    return l;
  }

  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator *(FixedPoint<OI, OF, S> o) const {
    // Extend both sides to the same size
    auto l = FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S>{*this};
    auto r = FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S>{o};
    // Then do a regular multiply and truncate the result to our size
    auto f = (l * r);
    FixedPoint out{0};
    out.set(f.get());
    return out;
  }

  // Comparison overloads
  [[clang::always_inline]] constexpr bool operator==(const FixedPoint& b) const noexcept {
    return val == b.val;
  }
  [[clang::always_inline]] constexpr bool operator< (const FixedPoint& b) const noexcept {
    return val < b.val;
  }
  [[clang::always_inline]] constexpr bool operator!=(const FixedPoint& b) const noexcept {
    return !(*this == b);
  }
  [[clang::always_inline]] constexpr bool operator> (const FixedPoint& b) const noexcept {
    return b < *this;
  }
  [[clang::always_inline]] constexpr bool operator>=(const FixedPoint& b) const noexcept {
    return !(*this < b);
  }
  [[clang::always_inline]] constexpr bool operator<=(const FixedPoint& b) const noexcept {
    return !(b < *this);
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator==(FixedPoint<OI, OF, S> b) const noexcept {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = b;
    return l == r;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator< (FixedPoint<OI, OF, S> b) const noexcept {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = b;
    return l < r;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator!=(FixedPoint<OI, OF, S> b) const noexcept {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = b;
    return !(l == r);
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator> (FixedPoint<OI, OF, S> b) const noexcept {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = b;
    return r < l;
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator>=(FixedPoint<OI, OF, S> b) const noexcept {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = b;
    return !(l < r);
  }
  template<intmax_t OI, intmax_t OF, bool S>
  [[clang::always_inline]] constexpr auto operator<=(FixedPoint<OI, OF, S> b) const noexcept {
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> l = *this;
    FixedPoint<(ISize > OI ? ISize : OI), (FSize > OF ? FSize : OF), Signed && S> r = b;
    return !(r < l);
  }
};


/// Helper namespace that contains a few common types and user defined literals
/// for converting from floating point numbers to fixed point numbers at compile time.
/// Usage example:
///
/// using namespace fixedpoint::literals;
/// fu8_8 number = 180.44_u8_8; // creates a number at compile-time == 0xb4e1
/// f8_8 value = -60.89_s8_8;  // values can be signed or unsigned
/// auto inferred = 107.3_12_4;   // default is signed just like other int types
namespace fixedpoint_literals {

using fs8_8 = FixedPoint<8, 8, true>;
using fs12_4 = FixedPoint<12, 4, true>;
using fs16_8 = FixedPoint<16, 8, true>;
using fs8_16 = FixedPoint<8, 16, true>;
using fs12_12 = FixedPoint<12, 12, true>;
using fs16_16 = FixedPoint<16, 16, true>;
using fs24_8 = FixedPoint<24, 8, true>;

using fu8_8 = FixedPoint<8, 8, false>;
using fu12_4 = FixedPoint<12, 4, false>;
using fu16_8 = FixedPoint<16, 8, false>;
using fu8_16 = FixedPoint<8, 16, false>;
using fu12_12 = FixedPoint<12, 12, false>;
using fu16_16 = FixedPoint<16, 16, false>;
using fu24_8 = FixedPoint<24, 8, false>;

using f8_8 = fs8_8;
using f12_4 = fs12_4;
using f16_8 = fs16_8;
using f8_16 = fs8_16;
using f12_12 = fs12_12;
using f16_16 = fs16_16;
using f24_8 = fs24_8;

#if __cplusplus >= 202002L
[[clang::always_inline]] consteval fs8_8 operator ""_s8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] consteval fs12_4 operator ""_s12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] consteval fs16_8 operator ""_s16_8(long double fixed) {
  return FixedPoint<16,8,true>{fixed};
}
[[clang::always_inline]] consteval fs8_16 operator ""_s8_16(long double fixed) {
  return FixedPoint<8,16,true>{fixed};
}
[[clang::always_inline]] consteval fs12_12 operator ""_s12_12(long double fixed) {
  return FixedPoint<12,12,true>{fixed};
}
[[clang::always_inline]] consteval fs16_16 operator ""_s16_16(long double fixed) {
  return FixedPoint<16,16,true>{fixed};
}
[[clang::always_inline]] consteval fs24_8 operator ""_s24_8(long double fixed) {
  return FixedPoint<24,8,true>{fixed};
}

[[clang::always_inline]] consteval fu8_8 operator ""_u8_8(long double fixed) {
  return FixedPoint<8,8,false>{fixed};
}
[[clang::always_inline]] consteval fu12_4 operator ""_u12_4(long double fixed) {
  return FixedPoint<12,4,false>{fixed};
}
[[clang::always_inline]] consteval fu16_8 operator ""_u16_8(long double fixed) {
  return FixedPoint<16,8,false>{fixed};
}
[[clang::always_inline]] consteval fu8_16 operator ""_u8_16(long double fixed) {
  return FixedPoint<8,16,false>{fixed};
}
[[clang::always_inline]] consteval fu12_12 operator ""_u12_12(long double fixed) {
  return FixedPoint<12,12,false>{fixed};
}
[[clang::always_inline]] consteval fu16_16 operator ""_u16_16(long double fixed) {
  return FixedPoint<16,16,false>{fixed};
}
[[clang::always_inline]] consteval fu24_8 operator ""_u24_8(long double fixed) {
  return FixedPoint<24,8,false>{fixed};
}

[[clang::always_inline]] consteval fs8_8 operator ""_8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] consteval fs12_4 operator ""_12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] consteval fs16_8 operator ""_16_8(long double fixed) {
  return FixedPoint<16,8,true>{fixed};
}
[[clang::always_inline]] consteval fs8_16 operator ""_8_16(long double fixed) {
  return FixedPoint<8,16,true>{fixed};
}
[[clang::always_inline]] consteval fs12_12 operator ""_12_12(long double fixed) {
  return FixedPoint<12,12,true>{fixed};
}
[[clang::always_inline]] consteval fs16_16 operator ""_16_16(long double fixed) {
  return FixedPoint<16,16,true>{fixed};
}
[[clang::always_inline]] consteval fs24_8 operator ""_24_8(long double fixed) {
  return FixedPoint<24,8,true>{fixed};
}
#else
[[clang::always_inline]] constexpr fs8_8 operator ""_s8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] constexpr fs12_4 operator ""_s12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] constexpr fs16_8 operator ""_s16_8(long double fixed) {
  return FixedPoint<16,8,true>{fixed};
}
[[clang::always_inline]] constexpr fs8_16 operator ""_s8_16(long double fixed) {
  return FixedPoint<8,16,true>{fixed};
}
[[clang::always_inline]] constexpr fs12_12 operator ""_s12_12(long double fixed) {
  return FixedPoint<12,12,true>{fixed};
}
[[clang::always_inline]] constexpr fs16_16 operator ""_s16_16(long double fixed) {
  return FixedPoint<16,16,true>{fixed};
}
[[clang::always_inline]] constexpr fs24_8 operator ""_s24_8(long double fixed) {
  return FixedPoint<24,8,true>{fixed};
}

[[clang::always_inline]] constexpr fu8_8 operator ""_u8_8(long double fixed) {
  return FixedPoint<8,8,false>{fixed};
}
[[clang::always_inline]] constexpr fu12_4 operator ""_u12_4(long double fixed) {
  return FixedPoint<12,4,false>{fixed};
}
[[clang::always_inline]] constexpr fu16_8 operator ""_u16_8(long double fixed) {
  return FixedPoint<16,8,false>{fixed};
}
[[clang::always_inline]] constexpr fu8_16 operator ""_u8_16(long double fixed) {
  return FixedPoint<8,16,false>{fixed};
}
[[clang::always_inline]] constexpr fu12_12 operator ""_u12_12(long double fixed) {
  return FixedPoint<12,12,false>{fixed};
}
[[clang::always_inline]] constexpr fu16_16 operator ""_u16_16(long double fixed) {
  return FixedPoint<16,16,false>{fixed};
}
[[clang::always_inline]] constexpr fu24_8 operator ""_u24_8(long double fixed) {
  return FixedPoint<24,8,false>{fixed};
}

[[clang::always_inline]] constexpr f8_8 operator ""_8_8(long double fixed) {
  return FixedPoint<8,8,true>{fixed};
}
[[clang::always_inline]] constexpr f12_4 operator ""_12_4(long double fixed) {
  return FixedPoint<12,4,true>{fixed};
}
[[clang::always_inline]] constexpr f16_8 operator ""_16_8(long double fixed) {
  return FixedPoint<16,8,true>{fixed};
}
[[clang::always_inline]] constexpr f8_16 operator ""_8_16(long double fixed) {
  return FixedPoint<8,16,true>{fixed};
}
[[clang::always_inline]] constexpr f12_12 operator ""_12_12(long double fixed) {
  return FixedPoint<12,12,true>{fixed};
}
[[clang::always_inline]] constexpr f16_16 operator ""_16_16(long double fixed) {
  return FixedPoint<16,16,true>{fixed};
}
[[clang::always_inline]] constexpr f24_8 operator ""_24_8(long double fixed) {
  return FixedPoint<24,8,true>{fixed};
}
#endif
} // namespace fixedpoint_literals

#endif // _FIXED_POINT_H
