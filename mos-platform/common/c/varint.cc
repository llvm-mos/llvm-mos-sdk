#include "varint.h"

#include <stdio.h>
#include <string.h>

using namespace __impl;

VarInt &VarInt::operator=(const VarInt &other) {
  memcpy(bytes(), other.bytes(), size);
  return *this;
}

bool VarInt::operator!=(const VarInt &other) const {
  for (char i = 0; i < size; ++i)
    if (bytes()[i] != other.bytes()[i])
      return true;
  return false;
}

bool VarInt::operator==(const VarInt &other) const { return !(*this != other); }

bool VarInt::operator<(const VarInt &other) const {
  for (char i = size - 1; i; --i) {
    if (bytes()[i] < other.bytes()[i])
      return true;
    if (bytes()[i] > other.bytes()[i])
      return false;
  }
  return bytes()[0] < other.bytes()[0];
}

bool VarInt::operator<=(const VarInt &other) const { return !(other < *this); }
bool VarInt::operator>(const VarInt &other) const { return other < *this; }
bool VarInt::operator>=(const VarInt &other) const { return !(*this < other); }

bool VarInt::too_positive() const { return bytes()[size - 1] >= 0x80; }

bool VarInt::too_negative() const {
  if (bytes()[size - 1] < 0x80)
    return false;
  if (bytes()[size - 1] > 0x80)
    return true;
  for (char i = 0; i < size - 1; i++)
    if (bytes()[i] != 0)
      return true;
  return false;
}

VarInt &VarInt::operator+=(const VarInt &other) {
  add_overflow(other);
  return *this;
}

bool VarInt::add_overflow(const VarInt &other) {
  unsigned char carry = 0;
  for (char i = 0; i < size; ++i)
    bytes()[i] = __builtin_addcb(bytes()[i], other.bytes()[i], carry, &carry);
  return carry;
}

bool VarInt::shl_overflow() {
  char carry = 0;
  for (char i = 0; i < size; ++i) {
    char new_carry = bytes()[i] & 0x80 ? 1 : 0;
    bytes()[i] <<= 1;
    bytes()[i] |= carry;
    carry = new_carry;
  }
  return carry;
}

void VarInt::negate() {
  unsigned char carry = 0;
  for (char i = 0; i < size; ++i)
    bytes()[i] = __builtin_subcb(0, bytes()[i], carry, &carry);
}

void VarInt::shl() { shl_overflow(); }

void VarInt::zero() {
  for (char i = 0; i < size; ++i)
    bytes()[i] = 0;
}

void VarInt::positive_limit() {
  for (char i = 0; i < size - 1; ++i)
    bytes()[i] = 0xff;
  bytes()[size - 1] = 0x7f;
}

void VarInt::negative_limit() {
  for (char i = 0; i < size - 1; ++i)
    bytes()[i] = 0;
  bytes()[size - 1] = 0x80;
}

void VarInt::unsigned_limit() {
  for (char i = 0; i < size; ++i)
    bytes()[i] = 0xff;
}

void VarInt::dump() const {
  for (char i = 0; i < size; ++i)
    printf("%02x", bytes()[i]);
  putchar('\n');
}
