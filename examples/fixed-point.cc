#undef NDEBUG
#include <assert.h>
#include <fixed_point.h>

// This file is an example of how to use the high level fixed point
// library in fixed_point.h. The fixedpoint::Value class provides a
// typesafe wrapper for fixed point mathematical operations and
// convenience methods for accessing the integral and decimal parts.

int main() {
  // Creates a signed fixed point number with 100 as the integral part
  // The full representation of the number is 0x6400 where 0x64 is the
  // integer part and 0x00 is the fractional part.
  FixedPoint<8, 8> basic_number{100};

  // Math operators work out of the box
  // This will add 19 to the integral part
  basic_number += 19;

  // Integer and fractional parts can be accessed individually
  assert( basic_number.as_i() == 119 );

  // Now for the fun part, here's a second number but with a fractional part
  // This number in hexadecimal is 0x0110
  FixedPoint<8, 8> second_number{1, 16};
  
  // Subtraction works as well.
  basic_number -= second_number;
  // The new basic_number integral part is now 117 (since we subtracted a fraction part)
  assert( basic_number.as_i() == 117 );
  // The fractional part is 
  assert( basic_number.as_f() == 0xe0 );

  // Now that the basics are out of the way, let's start using the helper methods
  // in the literals namespace
  using namespace fixedpoint_literals;

  // For the common 8.8 and 12.4 fixed point numbers, user defined literals are
  // provided for converting from floating point numbers at compile time.
  // This converts 9.87 into an 8.8 number (0x09de)
  auto third_number = 9.87_12_4;

  // Comparisons work between fixed point numbers or integer numbers
  // Additionally fixed point numbers will be converted to other fixed point
  // numbers automatically when performing math operations.
  if (third_number + second_number > first_number) {
    assert( false );
  } else if (first_number < 119) {
    assert( true );
  }

  // fixed point numbers can be signed or unsigned as well with the optional
  // third parameter. They are signed by default like other integer types
  // There is also a matching literal type for unsigned numbers `_u8_8`
  // as well as an explicit signed version `_s8_8`
  fu8_8 unsigned_number = 40.4_u8_8;
  // The type is not required of course, the following also works.
  auto unsigned_number2 = 40.4_u8_8;

  unsigned_number += 200;
  // Since its unsigned, it will be treated as a positive value instead
  assert ( unsigned_number > 200 );

  return 0;
}