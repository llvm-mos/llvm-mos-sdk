// Copyright 2023 LLVM-MOS Project Licensed under the Apache License,
// Version 2.0 with LLVM Exceptions. See
// https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#if __cplusplus < 202002L
#error charset support requies C++20
#else
#ifndef _CHARSET_H
#define _CHARSET_H

#include <cstddef>

namespace charset_impl {

template <size_t N> struct UnshiftedString {
  char Str[N]{};

  constexpr UnshiftedString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr UnshiftedString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr UnshiftedString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

    // C0 control codes are uninterpreted.
    case 0x0000 ... 0x001f:
      return C;

      // Name: Map from Commodore VIC-20 (interchange) primary character set to
      // Unicode

      // Date: 2018 April 20

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

      // UNICODE LICENSE V3
      // Copyright © 1991-2023 Unicode, Inc.

    case 0x0020:
      return 0x20; // SPACE
    case 0x0021:
      return 0x21; // EXCLAMATION MARK
    case 0x0022:
      return 0x22; // QUOTATION MARK
    case 0x0023:
      return 0x23; // NUMBER SIGN
    case 0x0024:
      return 0x24; // DOLLAR SIGN
    case 0x0025:
      return 0x25; // PERCENT SIGN
    case 0x0026:
      return 0x26; // AMPERSAND
    case 0x0027:
      return 0x27; // APOSTROPHE
    case 0x0028:
      return 0x28; // LEFT PARENTHESIS
    case 0x0029:
      return 0x29; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x2A; // ASTERISK
    case 0x002B:
      return 0x2B; // PLUS SIGN
    case 0x002C:
      return 0x2C; // COMMA
    case 0x002D:
      return 0x2D; // HYPHEN-MINUS
    case 0x002E:
      return 0x2E; // FULL STOP
    case 0x002F:
      return 0x2F; // SOLIDUS
    case 0x0030:
      return 0x30; // DIGIT ZERO
    case 0x0031:
      return 0x31; // DIGIT ONE
    case 0x0032:
      return 0x32; // DIGIT TWO
    case 0x0033:
      return 0x33; // DIGIT THREE
    case 0x0034:
      return 0x34; // DIGIT FOUR
    case 0x0035:
      return 0x35; // DIGIT FIVE
    case 0x0036:
      return 0x36; // DIGIT SIX
    case 0x0037:
      return 0x37; // DIGIT SEVEN
    case 0x0038:
      return 0x38; // DIGIT EIGHT
    case 0x0039:
      return 0x39; // DIGIT NINE
    case 0x003A:
      return 0x3A; // COLON
    case 0x003B:
      return 0x3B; // SEMICOLON
    case 0x003C:
      return 0x3C; // LESS-THAN SIGN
    case 0x003D:
      return 0x3D; // EQUALS SIGN
    case 0x003E:
      return 0x3E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x3F; // QUESTION MARK
    case 0x0040:
      return 0x40; // COMMERCIAL AT
    case 0x0041:
      return 0x41; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0x42; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0x43; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0x44; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0x45; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0x46; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0x47; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0x48; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0x49; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0x4A; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0x4B; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0x4C; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0x4D; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0x4E; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0x4F; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0x50; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0x51; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0x52; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0x53; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0x54; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0x55; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0x56; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0x57; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0x58; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0x59; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0x5A; // LATIN CAPITAL LETTER Z
    case 0x005B:
      return 0x5B; // LEFT SQUARE BRACKET
    case 0x00A3:
      return 0x5C; // POUND SIGN
    case 0x005D:
      return 0x5D; // RIGHT SQUARE BRACKET
    case 0x2191:
      return 0x5E; // UPWARDS ARROW
    case 0x2190:
      return 0x5F; // LEFTWARDS ARROW
    case 0x2500:
      return 0x60; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x2660:
      return 0x61; // BLACK SPADE SUIT
    case 0x1FB72:
      return 0x62; // VERTICAL ONE EIGHTH BLOCK-4
    case 0x1FB78:
      return 0x63; // HORIZONTAL ONE EIGHTH BLOCK-4
    case 0x1FB77:
      return 0x64; // HORIZONTAL ONE EIGHTH BLOCK-3
    case 0x1FB76:
      return 0x65; // HORIZONTAL ONE EIGHTH BLOCK-2
    case 0x1FB7A:
      return 0x66; // HORIZONTAL ONE EIGHTH BLOCK-6
    case 0x1FB71:
      return 0x67; // VERTICAL ONE EIGHTH BLOCK-3
    case 0x1FB74:
      return 0x68; // VERTICAL ONE EIGHTH BLOCK-6
    case 0x256E:
      return 0x69; // BOX DRAWINGS LIGHT ARC DOWN AND LEFT
    case 0x2570:
      return 0x6A; // BOX DRAWINGS LIGHT ARC UP AND RIGHT
    case 0x256F:
      return 0x6B; // BOX DRAWINGS LIGHT ARC UP AND LEFT
    case 0x1FB7C:
      return 0x6C; // LEFT AND LOWER ONE EIGHTH BLOCK
    case 0x2572:
      return 0x6D; // BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT
    case 0x2571:
      return 0x6E; // BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT
    case 0x1FB7D:
      return 0x6F; // LEFT AND UPPER ONE EIGHTH BLOCK
    case 0x1FB7E:
      return 0x70; // RIGHT AND UPPER ONE EIGHTH BLOCK
    case 0x2022:
      return 0x71; // BULLET (or 0x25CF BLACK CIRCLE)
    case 0x1FB7B:
      return 0x72; // HORIZONTAL ONE EIGHTH BLOCK-7
    case 0x2665:
      return 0x73; // BLACK HEART SUIT
    case 0x1FB70:
      return 0x74; // VERTICAL ONE EIGHTH BLOCK-2
    case 0x256D:
      return 0x75; // BOX DRAWINGS LIGHT ARC DOWN AND RIGHT
    case 0x2573:
      return 0x76; // BOX DRAWINGS LIGHT DIAGONAL CROSS
    case 0x25CB:
      return 0x77; // WHITE CIRCLE (or 0x25E6 WHITE BULLET)
    case 0x2663:
      return 0x78; // BLACK CLUB SUIT
    case 0x1FB75:
      return 0x79; // VERTICAL ONE EIGHTH BLOCK-7
    case 0x2666:
      return 0x7A; // BLACK DIAMOND SUIT
    case 0x253C:
      return 0x7B; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x1FB8C:
      return 0x7C; // LEFT HALF MEDIUM SHADE
    case 0x2502:
      return 0x7D; // BOX DRAWINGS LIGHT VERTICAL
    case 0x03C0:
      return 0x7E; // GREEK SMALL LETTER PI
    case 0x25E5:
      return 0x7F; // BLACK UPPER RIGHT TRIANGLE
    case 0x00A0:
      return 0xA0; // NO-BREAK SPACE
    case 0x258C:
      return 0xA1; // LEFT HALF BLOCK
    case 0x2584:
      return 0xA2; // LOWER HALF BLOCK
    case 0x2594:
      return 0xA3; // UPPER ONE EIGHTH BLOCK
    case 0x2581:
      return 0xA4; // LOWER ONE EIGHTH BLOCK
    case 0x258F:
      return 0xA5; // LEFT ONE EIGHTH BLOCK
    case 0x2592:
      return 0xA6; // MEDIUM SHADE
    case 0x2595:
      return 0xA7; // RIGHT ONE EIGHTH BLOCK
    case 0x1FB8F:
      return 0xA8; // LOWER HALF MEDIUM SHADE
    case 0x25E4:
      return 0xA9; // BLACK UPPER LEFT TRIANGLE
    case 0x1FB87:
      return 0xAA; // RIGHT ONE QUARTER BLOCK
    case 0x251C:
      return 0xAB; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x2597:
      return 0xAC; // QUADRANT LOWER RIGHT
    case 0x2514:
      return 0xAD; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x2510:
      return 0xAE; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2582:
      return 0xAF; // LOWER ONE QUARTER BLOCK
    case 0x250C:
      return 0xB0; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2534:
      return 0xB1; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x252C:
      return 0xB2; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2524:
      return 0xB3; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x258E:
      return 0xB4; // LEFT ONE QUARTER BLOCK
    case 0x258D:
      return 0xB5; // LEFT THREE EIGHTHS BLOCK
    case 0x1FB88:
      return 0xB6; // RIGHT THREE EIGHTHS BLOCK
    case 0x1FB82:
      return 0xB7; // UPPER ONE QUARTER BLOCK
    case 0x1FB83:
      return 0xB8; // UPPER THREE EIGHTHS BLOCK
    case 0x2583:
      return 0xB9; // LOWER THREE EIGHTHS BLOCK
    case 0x1FB7F:
      return 0xBA; // RIGHT AND LOWER ONE EIGHTH BLOCK
    case 0x2596:
      return 0xBB; // QUADRANT LOWER LEFT
    case 0x259D:
      return 0xBC; // QUADRANT UPPER RIGHT
    case 0x2518:
      return 0xBD; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2598:
      return 0xBE; // QUADRANT UPPER LEFT
    case 0x259A:
      return 0xBF; // QUADRANT UPPER LEFT AND LOWER RIGHT
    case 0x2500:
      return 0xC0; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x2660:
      return 0xC1; // BLACK SPADE SUIT
    case 0x1FB72:
      return 0xC2; // VERTICAL ONE EIGHTH BLOCK-4
    case 0x1FB78:
      return 0xC3; // HORIZONTAL ONE EIGHTH BLOCK-4
    case 0x1FB77:
      return 0xC4; // HORIZONTAL ONE EIGHTH BLOCK-3
    case 0x1FB76:
      return 0xC5; // HORIZONTAL ONE EIGHTH BLOCK-2
    case 0x1FB7A:
      return 0xC6; // HORIZONTAL ONE EIGHTH BLOCK-6
    case 0x1FB71:
      return 0xC7; // VERTICAL ONE EIGHTH BLOCK-3
    case 0x1FB74:
      return 0xC8; // VERTICAL ONE EIGHTH BLOCK-6
    case 0x256E:
      return 0xC9; // BOX DRAWINGS LIGHT ARC DOWN AND LEFT
    case 0x2570:
      return 0xCA; // BOX DRAWINGS LIGHT ARC UP AND RIGHT
    case 0x256F:
      return 0xCB; // BOX DRAWINGS LIGHT ARC UP AND LEFT
    case 0x1FB7C:
      return 0xCC; // LEFT AND LOWER ONE EIGHTH BLOCK
    case 0x2572:
      return 0xCD; // BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT
    case 0x2571:
      return 0xCE; // BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT
    case 0x1FB7D:
      return 0xCF; // LEFT AND UPPER ONE EIGHTH BLOCK
    case 0x1FB7E:
      return 0xD0; // RIGHT AND UPPER ONE EIGHTH BLOCK
    case 0x2022:
      return 0xD1; // BULLET (or 0x25CF BLACK CIRCLE)
    case 0x1FB7B:
      return 0xD2; // HORIZONTAL ONE EIGHTH BLOCK-7
    case 0x2665:
      return 0xD3; // BLACK HEART SUIT
    case 0x1FB70:
      return 0xD4; // VERTICAL ONE EIGHTH BLOCK-2
    case 0x256D:
      return 0xD5; // BOX DRAWINGS LIGHT ARC DOWN AND RIGHT
    case 0x2573:
      return 0xD6; // BOX DRAWINGS LIGHT DIAGONAL CROSS
    case 0x25CB:
      return 0xD7; // WHITE CIRCLE (or 0x25E6 WHITE BULLET)
    case 0x2663:
      return 0xD8; // BLACK CLUB SUIT
    case 0x1FB75:
      return 0xD9; // VERTICAL ONE EIGHTH BLOCK-7
    case 0x2666:
      return 0xDA; // BLACK DIAMOND SUIT
    case 0x253C:
      return 0xDB; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x1FB8C:
      return 0xDC; // LEFT HALF MEDIUM SHADE
    case 0x2502:
      return 0xDD; // BOX DRAWINGS LIGHT VERTICAL
    case 0x03C0:
      return 0xDE; // GREEK SMALL LETTER PI
    case 0x25E5:
      return 0xDF; // BLACK UPPER RIGHT TRIANGLE
    case 0x00A0:
      return 0xE0; // NO-BREAK SPACE
    case 0x258C:
      return 0xE1; // LEFT HALF BLOCK
    case 0x2584:
      return 0xE2; // LOWER HALF BLOCK
    case 0x2594:
      return 0xE3; // UPPER ONE EIGHTH BLOCK
    case 0x2581:
      return 0xE4; // LOWER ONE EIGHTH BLOCK
    case 0x258F:
      return 0xE5; // LEFT ONE EIGHTH BLOCK
    case 0x2592:
      return 0xE6; // MEDIUM SHADE
    case 0x2595:
      return 0xE7; // RIGHT ONE EIGHTH BLOCK
    case 0x1FB8F:
      return 0xE8; // LOWER HALF MEDIUM SHADE
    case 0x25E4:
      return 0xE9; // BLACK UPPER LEFT TRIANGLE
    case 0x1FB87:
      return 0xEA; // RIGHT ONE QUARTER BLOCK
    case 0x251C:
      return 0xEB; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x2597:
      return 0xEC; // QUADRANT LOWER RIGHT
    case 0x2514:
      return 0xED; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x2510:
      return 0xEE; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2582:
      return 0xEF; // LOWER ONE QUARTER BLOCK
    case 0x250C:
      return 0xF0; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2534:
      return 0xF1; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x252C:
      return 0xF2; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2524:
      return 0xF3; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x258E:
      return 0xF4; // LEFT ONE QUARTER BLOCK
    case 0x258D:
      return 0xF5; // LEFT THREE EIGHTHS BLOCK
    case 0x1FB88:
      return 0xF6; // RIGHT THREE EIGHTHS BLOCK
    case 0x1FB82:
      return 0xF7; // UPPER ONE QUARTER BLOCK
    case 0x1FB83:
      return 0xF8; // UPPER THREE EIGHTHS BLOCK
    case 0x2583:
      return 0xF9; // LOWER THREE EIGHTHS BLOCK
    case 0x1FB7F:
      return 0xFA; // RIGHT AND LOWER ONE EIGHTH BLOCK
    case 0x2596:
      return 0xFB; // QUADRANT LOWER LEFT
    case 0x259D:
      return 0xFC; // QUADRANT UPPER RIGHT
    case 0x2518:
      return 0xFD; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2598:
      return 0xFE; // QUADRANT UPPER LEFT
    case 0x259A:
      return 0xFF; // QUADRANT UPPER LEFT AND LOWER RIGHT
    }
  }
};

template <size_t N> struct ShiftedString {
  char Str[N]{};

  constexpr ShiftedString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr ShiftedString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr ShiftedString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

    // C0 control codes are uninterpreted.
    case 0x0000 ... 0x001f:
      return C;

      // Name: Map from Commodore VIC-20 (interchange) alternate character set
      // to Unicode

      // Date: 2018 October 11

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

      // UNICODE LICENSE V3
      // Copyright © 1991-2023 Unicode, Inc.

    case 0x0020:
      return 0x20; // SPACE
    case 0x0021:
      return 0x21; // EXCLAMATION MARK
    case 0x0022:
      return 0x22; // QUOTATION MARK
    case 0x0023:
      return 0x23; // NUMBER SIGN
    case 0x0024:
      return 0x24; // DOLLAR SIGN
    case 0x0025:
      return 0x25; // PERCENT SIGN
    case 0x0026:
      return 0x26; // AMPERSAND
    case 0x0027:
      return 0x27; // APOSTROPHE
    case 0x0028:
      return 0x28; // LEFT PARENTHESIS
    case 0x0029:
      return 0x29; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x2A; // ASTERISK
    case 0x002B:
      return 0x2B; // PLUS SIGN
    case 0x002C:
      return 0x2C; // COMMA
    case 0x002D:
      return 0x2D; // HYPHEN-MINUS
    case 0x002E:
      return 0x2E; // FULL STOP
    case 0x002F:
      return 0x2F; // SOLIDUS
    case 0x0030:
      return 0x30; // DIGIT ZERO
    case 0x0031:
      return 0x31; // DIGIT ONE
    case 0x0032:
      return 0x32; // DIGIT TWO
    case 0x0033:
      return 0x33; // DIGIT THREE
    case 0x0034:
      return 0x34; // DIGIT FOUR
    case 0x0035:
      return 0x35; // DIGIT FIVE
    case 0x0036:
      return 0x36; // DIGIT SIX
    case 0x0037:
      return 0x37; // DIGIT SEVEN
    case 0x0038:
      return 0x38; // DIGIT EIGHT
    case 0x0039:
      return 0x39; // DIGIT NINE
    case 0x003A:
      return 0x3A; // COLON
    case 0x003B:
      return 0x3B; // SEMICOLON
    case 0x003C:
      return 0x3C; // LESS-THAN SIGN
    case 0x003D:
      return 0x3D; // EQUALS SIGN
    case 0x003E:
      return 0x3E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x3F; // QUESTION MARK
    case 0x0040:
      return 0x40; // COMMERCIAL AT
    case 0x0061:
      return 0x41; // LATIN SMALL LETTER A
    case 0x0062:
      return 0x42; // LATIN SMALL LETTER B
    case 0x0063:
      return 0x43; // LATIN SMALL LETTER C
    case 0x0064:
      return 0x44; // LATIN SMALL LETTER D
    case 0x0065:
      return 0x45; // LATIN SMALL LETTER E
    case 0x0066:
      return 0x46; // LATIN SMALL LETTER F
    case 0x0067:
      return 0x47; // LATIN SMALL LETTER G
    case 0x0068:
      return 0x48; // LATIN SMALL LETTER H
    case 0x0069:
      return 0x49; // LATIN SMALL LETTER I
    case 0x006A:
      return 0x4A; // LATIN SMALL LETTER J
    case 0x006B:
      return 0x4B; // LATIN SMALL LETTER K
    case 0x006C:
      return 0x4C; // LATIN SMALL LETTER L
    case 0x006D:
      return 0x4D; // LATIN SMALL LETTER M
    case 0x006E:
      return 0x4E; // LATIN SMALL LETTER N
    case 0x006F:
      return 0x4F; // LATIN SMALL LETTER O
    case 0x0070:
      return 0x50; // LATIN SMALL LETTER P
    case 0x0071:
      return 0x51; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0x52; // LATIN SMALL LETTER R
    case 0x0073:
      return 0x53; // LATIN SMALL LETTER S
    case 0x0074:
      return 0x54; // LATIN SMALL LETTER T
    case 0x0075:
      return 0x55; // LATIN SMALL LETTER U
    case 0x0076:
      return 0x56; // LATIN SMALL LETTER V
    case 0x0077:
      return 0x57; // LATIN SMALL LETTER W
    case 0x0078:
      return 0x58; // LATIN SMALL LETTER X
    case 0x0079:
      return 0x59; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0x5A; // LATIN SMALL LETTER Z
    case 0x005B:
      return 0x5B; // LEFT SQUARE BRACKET
    case 0x00A3:
      return 0x5C; // POUND SIGN
    case 0x005D:
      return 0x5D; // RIGHT SQUARE BRACKET
    case 0x2191:
      return 0x5E; // UPWARDS ARROW
    case 0x2190:
      return 0x5F; // LEFTWARDS ARROW
    case 0x2500:
      return 0x60; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x0041:
      return 0x61; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0x62; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0x63; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0x64; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0x65; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0x66; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0x67; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0x68; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0x69; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0x6A; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0x6B; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0x6C; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0x6D; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0x6E; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0x6F; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0x70; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0x71; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0x72; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0x73; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0x74; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0x75; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0x76; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0x77; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0x78; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0x79; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0x7A; // LATIN CAPITAL LETTER Z
    case 0x253C:
      return 0x7B; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x1FB8C:
      return 0x7C; // LEFT HALF MEDIUM SHADE
    case 0x2502:
      return 0x7D; // BOX DRAWINGS LIGHT VERTICAL
    case 0x1FB95:
      return 0x7E; // CHECKER BOARD FILL
    case 0x1FB98:
      return 0x7F; // UPPER LEFT TO LOWER RIGHT FILL
    case 0x00A0:
      return 0xA0; // NO-BREAK SPACE
    case 0x258C:
      return 0xA1; // LEFT HALF BLOCK
    case 0x2584:
      return 0xA2; // LOWER HALF BLOCK
    case 0x2594:
      return 0xA3; // UPPER ONE EIGHTH BLOCK
    case 0x2581:
      return 0xA4; // LOWER ONE EIGHTH BLOCK
    case 0x258F:
      return 0xA5; // LEFT ONE EIGHTH BLOCK
    case 0x2592:
      return 0xA6; // MEDIUM SHADE
    case 0x2595:
      return 0xA7; // RIGHT ONE EIGHTH BLOCK
    case 0x1FB8F:
      return 0xA8; // LOWER HALF MEDIUM SHADE
    case 0x1FB99:
      return 0xA9; // UPPER RIGHT TO LOWER LEFT FILL
    case 0x1FB87:
      return 0xAA; // RIGHT ONE QUARTER BLOCK
    case 0x251C:
      return 0xAB; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x2597:
      return 0xAC; // QUADRANT LOWER RIGHT
    case 0x2514:
      return 0xAD; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x2510:
      return 0xAE; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2582:
      return 0xAF; // LOWER ONE QUARTER BLOCK
    case 0x250C:
      return 0xB0; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2534:
      return 0xB1; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x252C:
      return 0xB2; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2524:
      return 0xB3; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x258E:
      return 0xB4; // LEFT ONE QUARTER BLOCK
    case 0x258D:
      return 0xB5; // LEFT THREE EIGHTHS BLOCK
    case 0x1FB88:
      return 0xB6; // RIGHT THREE EIGHTHS BLOCK
    case 0x1FB82:
      return 0xB7; // UPPER ONE QUARTER BLOCK
    case 0x1FB83:
      return 0xB8; // UPPER THREE EIGHTHS BLOCK
    case 0x2583:
      return 0xB9; // LOWER THREE EIGHTHS BLOCK
    case 0x2713:
      return 0xBA; // CHECK MARK
    case 0x2596:
      return 0xBB; // QUADRANT LOWER LEFT
    case 0x259D:
      return 0xBC; // QUADRANT UPPER RIGHT
    case 0x2518:
      return 0xBD; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2598:
      return 0xBE; // QUADRANT UPPER LEFT
    case 0x259A:
      return 0xBF; // QUADRANT UPPER LEFT AND LOWER RIGHT
    case 0x2500:
      return 0xC0; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x0041:
      return 0xC1; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0xC2; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0xC3; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0xC4; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0xC5; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0xC6; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0xC7; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0xC8; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0xC9; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0xCA; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0xCB; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0xCC; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0xCD; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0xCE; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0xCF; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0xD0; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0xD1; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0xD2; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0xD3; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0xD4; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0xD5; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0xD6; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0xD7; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0xD8; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0xD9; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0xDA; // LATIN CAPITAL LETTER Z
    case 0x253C:
      return 0xDB; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x1FB8C:
      return 0xDC; // LEFT HALF MEDIUM SHADE
    case 0x2502:
      return 0xDD; // BOX DRAWINGS LIGHT VERTICAL
    case 0x1FB95:
      return 0xDE; // CHECKER BOARD FILL
    case 0x1FB98:
      return 0xDF; // UPPER LEFT TO LOWER RIGHT FILL
    case 0x00A0:
      return 0xE0; // NO-BREAK SPACE
    case 0x258C:
      return 0xE1; // LEFT HALF BLOCK
    case 0x2584:
      return 0xE2; // LOWER HALF BLOCK
    case 0x2594:
      return 0xE3; // UPPER ONE EIGHTH BLOCK
    case 0x2581:
      return 0xE4; // LOWER ONE EIGHTH BLOCK
    case 0x258F:
      return 0xE5; // LEFT ONE EIGHTH BLOCK
    case 0x2592:
      return 0xE6; // MEDIUM SHADE
    case 0x2595:
      return 0xE7; // RIGHT ONE EIGHTH BLOCK
    case 0x1FB8F:
      return 0xE8; // LOWER HALF MEDIUM SHADE
    case 0x1FB99:
      return 0xE9; // UPPER RIGHT TO LOWER LEFT FILL
    case 0x1FB87:
      return 0xEA; // RIGHT ONE QUARTER BLOCK
    case 0x251C:
      return 0xEB; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x2597:
      return 0xEC; // QUADRANT LOWER RIGHT
    case 0x2514:
      return 0xED; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x2510:
      return 0xEE; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2582:
      return 0xEF; // LOWER ONE QUARTER BLOCK
    case 0x250C:
      return 0xF0; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2534:
      return 0xF1; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x252C:
      return 0xF2; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2524:
      return 0xF3; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x258E:
      return 0xF4; // LEFT ONE QUARTER BLOCK
    case 0x258D:
      return 0xF5; // LEFT THREE EIGHTHS BLOCK
    case 0x1FB88:
      return 0xF6; // RIGHT THREE EIGHTHS BLOCK
    case 0x1FB82:
      return 0xF7; // UPPER ONE QUARTER BLOCK
    case 0x1FB83:
      return 0xF8; // UPPER THREE EIGHTHS BLOCK
    case 0x2583:
      return 0xF9; // LOWER THREE EIGHTHS BLOCK
    case 0x2713:
      return 0xFA; // CHECK MARK
    case 0x2596:
      return 0xFB; // QUADRANT LOWER LEFT
    case 0x259D:
      return 0xFC; // QUADRANT UPPER RIGHT
    case 0x2518:
      return 0xFD; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2598:
      return 0xFE; // QUADRANT UPPER LEFT
    case 0x259A:
      return 0xFF; // QUADRANT UPPER LEFT AND LOWER RIGHT
    }
  };
};

template <size_t N> struct UnshiftedVideoString {
  char Str[N]{};

  constexpr UnshiftedVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr UnshiftedVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr UnshiftedVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

      // Name: Map from Commodore VIC-20 (video) primary character set to
      // Unicode

      // Date: 2018 April 20

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0040:
      return 0x00; // COMMERCIAL AT
    case 0x0041:
      return 0x01; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0x02; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0x03; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0x04; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0x05; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0x06; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0x07; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0x08; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0x09; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0x0A; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0x0B; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0x0C; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0x0D; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0x0E; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0x0F; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0x10; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0x11; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0x12; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0x13; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0x14; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0x15; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0x16; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0x17; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0x18; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0x19; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0x1A; // LATIN CAPITAL LETTER Z
    case 0x005B:
      return 0x1B; // LEFT SQUARE BRACKET
    case 0x00A3:
      return 0x1C; // POUND SIGN
    case 0x005D:
      return 0x1D; // RIGHT SQUARE BRACKET
    case 0x2191:
      return 0x1E; // UPWARDS ARROW
    case 0x2190:
      return 0x1F; // LEFTWARDS ARROW
    case 0x0020:
      return 0x20; // SPACE
    case 0x0021:
      return 0x21; // EXCLAMATION MARK
    case 0x0022:
      return 0x22; // QUOTATION MARK
    case 0x0023:
      return 0x23; // NUMBER SIGN
    case 0x0024:
      return 0x24; // DOLLAR SIGN
    case 0x0025:
      return 0x25; // PERCENT SIGN
    case 0x0026:
      return 0x26; // AMPERSAND
    case 0x0027:
      return 0x27; // APOSTROPHE
    case 0x0028:
      return 0x28; // LEFT PARENTHESIS
    case 0x0029:
      return 0x29; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x2A; // ASTERISK
    case 0x002B:
      return 0x2B; // PLUS SIGN
    case 0x002C:
      return 0x2C; // COMMA
    case 0x002D:
      return 0x2D; // HYPHEN-MINUS
    case 0x002E:
      return 0x2E; // FULL STOP
    case 0x002F:
      return 0x2F; // SOLIDUS
    case 0x0030:
      return 0x30; // DIGIT ZERO
    case 0x0031:
      return 0x31; // DIGIT ONE
    case 0x0032:
      return 0x32; // DIGIT TWO
    case 0x0033:
      return 0x33; // DIGIT THREE
    case 0x0034:
      return 0x34; // DIGIT FOUR
    case 0x0035:
      return 0x35; // DIGIT FIVE
    case 0x0036:
      return 0x36; // DIGIT SIX
    case 0x0037:
      return 0x37; // DIGIT SEVEN
    case 0x0038:
      return 0x38; // DIGIT EIGHT
    case 0x0039:
      return 0x39; // DIGIT NINE
    case 0x003A:
      return 0x3A; // COLON
    case 0x003B:
      return 0x3B; // SEMICOLON
    case 0x003C:
      return 0x3C; // LESS-THAN SIGN
    case 0x003D:
      return 0x3D; // EQUALS SIGN
    case 0x003E:
      return 0x3E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x3F; // QUESTION MARK
    case 0x2500:
      return 0x40; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x2660:
      return 0x41; // BLACK SPADE SUIT
    case 0x1FB72:
      return 0x42; // VERTICAL ONE EIGHTH BLOCK-4
    case 0x1FB78:
      return 0x43; // HORIZONTAL ONE EIGHTH BLOCK-4
    case 0x1FB77:
      return 0x44; // HORIZONTAL ONE EIGHTH BLOCK-3
    case 0x1FB76:
      return 0x45; // HORIZONTAL ONE EIGHTH BLOCK-2
    case 0x1FB7A:
      return 0x46; // HORIZONTAL ONE EIGHTH BLOCK-6
    case 0x1FB71:
      return 0x47; // VERTICAL ONE EIGHTH BLOCK-3
    case 0x1FB74:
      return 0x48; // VERTICAL ONE EIGHTH BLOCK-6
    case 0x256E:
      return 0x49; // BOX DRAWINGS LIGHT ARC DOWN AND LEFT
    case 0x2570:
      return 0x4A; // BOX DRAWINGS LIGHT ARC UP AND RIGHT
    case 0x256F:
      return 0x4B; // BOX DRAWINGS LIGHT ARC UP AND LEFT
    case 0x1FB7C:
      return 0x4C; // LEFT AND LOWER ONE EIGHTH BLOCK
    case 0x2572:
      return 0x4D; // BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT
    case 0x2571:
      return 0x4E; // BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT
    case 0x1FB7D:
      return 0x4F; // LEFT AND UPPER ONE EIGHTH BLOCK
    case 0x1FB7E:
      return 0x50; // RIGHT AND UPPER ONE EIGHTH BLOCK
    case 0x2022:
      return 0x51; // BULLET (or 0x25CF BLACK CIRCLE)
    case 0x1FB7B:
      return 0x52; // HORIZONTAL ONE EIGHTH BLOCK-7
    case 0x2665:
      return 0x53; // BLACK HEART SUIT
    case 0x1FB70:
      return 0x54; // VERTICAL ONE EIGHTH BLOCK-2
    case 0x256D:
      return 0x55; // BOX DRAWINGS LIGHT ARC DOWN AND RIGHT
    case 0x2573:
      return 0x56; // BOX DRAWINGS LIGHT DIAGONAL CROSS
    case 0x25CB:
      return 0x57; // WHITE CIRCLE (or 0x25E6 WHITE BULLET)
    case 0x2663:
      return 0x58; // BLACK CLUB SUIT
    case 0x1FB75:
      return 0x59; // VERTICAL ONE EIGHTH BLOCK-7
    case 0x2666:
      return 0x5A; // BLACK DIAMOND SUIT
    case 0x253C:
      return 0x5B; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x1FB8C:
      return 0x5C; // LEFT HALF MEDIUM SHADE
    case 0x2502:
      return 0x5D; // BOX DRAWINGS LIGHT VERTICAL
    case 0x03C0:
      return 0x5E; // GREEK SMALL LETTER PI
    case 0x25E5:
      return 0x5F; // BLACK UPPER RIGHT TRIANGLE
    case 0x00A0:
      return 0x60; // NO-BREAK SPACE
    case 0x258C:
      return 0x61; // LEFT HALF BLOCK
    case 0x2584:
      return 0x62; // LOWER HALF BLOCK
    case 0x2594:
      return 0x63; // UPPER ONE EIGHTH BLOCK
    case 0x2581:
      return 0x64; // LOWER ONE EIGHTH BLOCK
    case 0x258F:
      return 0x65; // LEFT ONE EIGHTH BLOCK
    case 0x2592:
      return 0x66; // MEDIUM SHADE
    case 0x2595:
      return 0x67; // RIGHT ONE EIGHTH BLOCK
    case 0x1FB8F:
      return 0x68; // LOWER HALF MEDIUM SHADE
    case 0x25E4:
      return 0x69; // BLACK UPPER LEFT TRIANGLE
    case 0x1FB87:
      return 0x6A; // RIGHT ONE QUARTER BLOCK
    case 0x251C:
      return 0x6B; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x2597:
      return 0x6C; // QUADRANT LOWER RIGHT
    case 0x2514:
      return 0x6D; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x2510:
      return 0x6E; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2582:
      return 0x6F; // LOWER ONE QUARTER BLOCK
    case 0x250C:
      return 0x70; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2534:
      return 0x71; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x252C:
      return 0x72; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2524:
      return 0x73; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x258E:
      return 0x74; // LEFT ONE QUARTER BLOCK
    case 0x258D:
      return 0x75; // LEFT THREE EIGHTHS BLOCK
    case 0x1FB88:
      return 0x76; // RIGHT THREE EIGHTHS BLOCK
    case 0x1FB82:
      return 0x77; // UPPER ONE QUARTER BLOCK
    case 0x1FB83:
      return 0x78; // UPPER THREE EIGHTHS BLOCK
    case 0x2583:
      return 0x79; // LOWER THREE EIGHTHS BLOCK
    case 0x1FB7F:
      return 0x7A; // RIGHT AND LOWER ONE EIGHTH BLOCK
    case 0x2596:
      return 0x7B; // QUADRANT LOWER LEFT
    case 0x259D:
      return 0x7C; // QUADRANT UPPER RIGHT
    case 0x2518:
      return 0x7D; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2598:
      return 0x7E; // QUADRANT UPPER LEFT
    case 0x259A:
      return 0x7F; // QUADRANT UPPER LEFT AND LOWER RIGHT
    case 0x25D8:
      return 0xD1; // INVERSE BULLET
    case 0x25D9:
      return 0xD7; // INVERSE WHITE CIRCLE
    case 0x1FB94:
      return 0xDC; // LEFT HALF INVERSE MEDIUM SHADE AND RIGHT HALF BLOCK
    case 0x25E3:
      return 0xDF; // BLACK LOWER LEFT TRIANGLE
    case 0x2588:
      return 0xE0; // FULL BLOCK
    case 0x2590:
      return 0xE1; // RIGHT HALF BLOCK
    case 0x2580:
      return 0xE2; // UPPER HALF BLOCK
    case 0x2587:
      return 0xE3; // LOWER SEVEN EIGHTHS BLOCK
    case 0x1FB86:
      return 0xE4; // UPPER SEVEN EIGHTHS BLOCK
    case 0x1FB8B:
      return 0xE5; // RIGHT SEVEN EIGHTHS BLOCK
    case 0x1FB90:
      return 0xE6; // INVERSE MEDIUM SHADE
    case 0x2589:
      return 0xE7; // LEFT SEVEN EIGHTHS BLOCK
    case 0x1FB91:
      return 0xE8; // UPPER HALF BLOCK AND LOWER HALF INVERSE MEDIUM SHADE
    case 0x25E2:
      return 0xE9; // BLACK LOWER RIGHT TRIANGLE
    case 0x258A:
      return 0xEA; // LEFT THREE QUARTERS BLOCK
    case 0x259B:
      return 0xEC; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER LEFT
    case 0x1FB85:
      return 0xEF; // UPPER THREE QUARTERS BLOCK
    case 0x1FB8A:
      return 0xF4; // RIGHT THREE QUARTERS BLOCK
    case 0x1FB89:
      return 0xF5; // RIGHT FIVE EIGHTHS BLOCK
    case 0x258B:
      return 0xF6; // LEFT FIVE EIGHTHS BLOCK
    case 0x2586:
      return 0xF7; // LOWER THREE QUARTERS BLOCK
    case 0x2585:
      return 0xF8; // LOWER FIVE EIGHTHS BLOCK
    case 0x1FB84:
      return 0xF9; // UPPER FIVE EIGHTHS BLOCK
    case 0x259C:
      return 0xFB; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER RIGHT
    case 0x2599:
      return 0xFC; // QUADRANT UPPER LEFT AND LOWER LEFT AND LOWER RIGHT
    case 0x259F:
      return 0xFE; // QUADRANT UPPER RIGHT AND LOWER LEFT AND LOWER RIGHT
    case 0x259E:
      return 0xFF; // QUADRANT UPPER RIGHT AND LOWER LEFT
    }
  }
};

template <size_t N> struct UnshiftedReverseVideoString {
  char Str[N]{};

  constexpr UnshiftedReverseVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr UnshiftedReverseVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr UnshiftedReverseVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

      // Name: Map from Commodore VIC-20 (video) primary character set to
      // Unicode

      // Date: 2018 April 20

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0040:
      return 0x80; // COMMERCIAL AT, reverse video
    case 0x0041:
      return 0x81; // LATIN CAPITAL LETTER A, reverse video
    case 0x0042:
      return 0x82; // LATIN CAPITAL LETTER B, reverse video
    case 0x0043:
      return 0x83; // LATIN CAPITAL LETTER C, reverse video
    case 0x0044:
      return 0x84; // LATIN CAPITAL LETTER D, reverse video
    case 0x0045:
      return 0x85; // LATIN CAPITAL LETTER E, reverse video
    case 0x0046:
      return 0x86; // LATIN CAPITAL LETTER F, reverse video
    case 0x0047:
      return 0x87; // LATIN CAPITAL LETTER G, reverse video
    case 0x0048:
      return 0x88; // LATIN CAPITAL LETTER H, reverse video
    case 0x0049:
      return 0x89; // LATIN CAPITAL LETTER I, reverse video
    case 0x004A:
      return 0x8A; // LATIN CAPITAL LETTER J, reverse video
    case 0x004B:
      return 0x8B; // LATIN CAPITAL LETTER K, reverse video
    case 0x004C:
      return 0x8C; // LATIN CAPITAL LETTER L, reverse video
    case 0x004D:
      return 0x8D; // LATIN CAPITAL LETTER M, reverse video
    case 0x004E:
      return 0x8E; // LATIN CAPITAL LETTER N, reverse video
    case 0x004F:
      return 0x8F; // LATIN CAPITAL LETTER O, reverse video
    case 0x0050:
      return 0x90; // LATIN CAPITAL LETTER P, reverse video
    case 0x0051:
      return 0x91; // LATIN CAPITAL LETTER Q, reverse video
    case 0x0052:
      return 0x92; // LATIN CAPITAL LETTER R, reverse video
    case 0x0053:
      return 0x93; // LATIN CAPITAL LETTER S, reverse video
    case 0x0054:
      return 0x94; // LATIN CAPITAL LETTER T, reverse video
    case 0x0055:
      return 0x95; // LATIN CAPITAL LETTER U, reverse video
    case 0x0056:
      return 0x96; // LATIN CAPITAL LETTER V, reverse video
    case 0x0057:
      return 0x97; // LATIN CAPITAL LETTER W, reverse video
    case 0x0058:
      return 0x98; // LATIN CAPITAL LETTER X, reverse video
    case 0x0059:
      return 0x99; // LATIN CAPITAL LETTER Y, reverse video
    case 0x005A:
      return 0x9A; // LATIN CAPITAL LETTER Z, reverse video
    case 0x005B:
      return 0x9B; // LEFT SQUARE BRACKET, reverse video
    case 0x00A3:
      return 0x9C; // POUND SIGN, reverse video
    case 0x005D:
      return 0x9D; // RIGHT SQUARE BRACKET, reverse video
    case 0x2191:
      return 0x9E; // UPWARDS ARROW, reverse video
    case 0x2190:
      return 0x9F; // LEFTWARDS ARROW, reverse video
    case 0x0020:
      return 0xA0; // SPACE, reverse video
    case 0x0021:
      return 0xA1; // EXCLAMATION MARK, reverse video
    case 0x0022:
      return 0xA2; // QUOTATION MARK, reverse video
    case 0x0023:
      return 0xA3; // NUMBER SIGN, reverse video
    case 0x0024:
      return 0xA4; // DOLLAR SIGN, reverse video
    case 0x0025:
      return 0xA5; // PERCENT SIGN, reverse video
    case 0x0026:
      return 0xA6; // AMPERSAND, reverse video
    case 0x0027:
      return 0xA7; // APOSTROPHE, reverse video
    case 0x0028:
      return 0xA8; // LEFT PARENTHESIS, reverse video
    case 0x0029:
      return 0xA9; // RIGHT PARENTHESIS, reverse video
    case 0x002A:
      return 0xAA; // ASTERISK, reverse video
    case 0x002B:
      return 0xAB; // PLUS SIGN, reverse video
    case 0x002C:
      return 0xAC; // COMMA, reverse video
    case 0x002D:
      return 0xAD; // HYPHEN-MINUS, reverse video
    case 0x002E:
      return 0xAE; // FULL STOP, reverse video
    case 0x002F:
      return 0xAF; // SOLIDUS, reverse video
    case 0x0030:
      return 0xB0; // DIGIT ZERO, reverse video
    case 0x0031:
      return 0xB1; // DIGIT ONE, reverse video
    case 0x0032:
      return 0xB2; // DIGIT TWO, reverse video
    case 0x0033:
      return 0xB3; // DIGIT THREE, reverse video
    case 0x0034:
      return 0xB4; // DIGIT FOUR, reverse video
    case 0x0035:
      return 0xB5; // DIGIT FIVE, reverse video
    case 0x0036:
      return 0xB6; // DIGIT SIX, reverse video
    case 0x0037:
      return 0xB7; // DIGIT SEVEN, reverse video
    case 0x0038:
      return 0xB8; // DIGIT EIGHT, reverse video
    case 0x0039:
      return 0xB9; // DIGIT NINE, reverse video
    case 0x003A:
      return 0xBA; // COLON, reverse video
    case 0x003B:
      return 0xBB; // SEMICOLON, reverse video
    case 0x003C:
      return 0xBC; // LESS-THAN SIGN, reverse video
    case 0x003D:
      return 0xBD; // EQUALS SIGN, reverse video
    case 0x003E:
      return 0xBE; // GREATER-THAN SIGN, reverse video
    case 0x003F:
      return 0xBF; // QUESTION MARK, reverse video
    case 0x2500:
      return 0xC0; // BOX DRAWINGS LIGHT HORIZONTAL, reverse video
    case 0x2660:
      return 0xC1; // BLACK SPADE SUIT, reverse video
    case 0x1FB72:
      return 0xC2; // VERTICAL ONE EIGHTH BLOCK-4, reverse video
    case 0x1FB78:
      return 0xC3; // HORIZONTAL ONE EIGHTH BLOCK-4, reverse video
    case 0x1FB77:
      return 0xC4; // HORIZONTAL ONE EIGHTH BLOCK-3, reverse video
    case 0x1FB76:
      return 0xC5; // HORIZONTAL ONE EIGHTH BLOCK-2, reverse video
    case 0x1FB7A:
      return 0xC6; // HORIZONTAL ONE EIGHTH BLOCK-6, reverse video
    case 0x1FB71:
      return 0xC7; // VERTICAL ONE EIGHTH BLOCK-3, reverse video
    case 0x1FB74:
      return 0xC8; // VERTICAL ONE EIGHTH BLOCK-6, reverse video
    case 0x256E:
      return 0xC9; // BOX DRAWINGS LIGHT ARC DOWN AND LEFT, reverse video
    case 0x2570:
      return 0xCA; // BOX DRAWINGS LIGHT ARC UP AND RIGHT, reverse video
    case 0x256F:
      return 0xCB; // BOX DRAWINGS LIGHT ARC UP AND LEFT, reverse video
    case 0x1FB7C:
      return 0xCC; // LEFT AND LOWER ONE EIGHTH BLOCK, reverse video
    case 0x2572:
      return 0xCD; // BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT, reverse video
    case 0x2571:
      return 0xCE; // BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT, reverse video
    case 0x1FB7D:
      return 0xCF; // LEFT AND UPPER ONE EIGHTH BLOCK, reverse video
    case 0x1FB7E:
      return 0xD0; // RIGHT AND UPPER ONE EIGHTH BLOCK, reverse video
    case 0x1FB7B:
      return 0xD2; // HORIZONTAL ONE EIGHTH BLOCK-7, reverse video
    case 0x2665:
      return 0xD3; // BLACK HEART SUIT, reverse video
    case 0x1FB70:
      return 0xD4; // VERTICAL ONE EIGHTH BLOCK-2, reverse video
    case 0x256D:
      return 0xD5; // BOX DRAWINGS LIGHT ARC DOWN AND RIGHT, reverse video
    case 0x2573:
      return 0xD6; // BOX DRAWINGS LIGHT DIAGONAL CROSS, reverse video
    case 0x2663:
      return 0xD8; // BLACK CLUB SUIT, reverse video
    case 0x1FB75:
      return 0xD9; // VERTICAL ONE EIGHTH BLOCK-7, reverse video
    case 0x2666:
      return 0xDA; // BLACK DIAMOND SUIT, reverse video
    case 0x253C:
      return 0xDB; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL, reverse video
    case 0x2502:
      return 0xDD; // BOX DRAWINGS LIGHT VERTICAL, reverse video
    case 0x03C0:
      return 0xDE; // GREEK SMALL LETTER PI, reverse video
    case 0x251C:
      return 0xEB; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT, reverse video
    case 0x2514:
      return 0xED; // BOX DRAWINGS LIGHT UP AND RIGHT, reverse video
    case 0x2510:
      return 0xEE; // BOX DRAWINGS LIGHT DOWN AND LEFT, reverse video
    case 0x250C:
      return 0xF0; // BOX DRAWINGS LIGHT DOWN AND RIGHT, reverse video
    case 0x2534:
      return 0xF1; // BOX DRAWINGS LIGHT UP AND HORIZONTAL, reverse video
    case 0x252C:
      return 0xF2; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL, reverse video
    case 0x2524:
      return 0xF3; // BOX DRAWINGS LIGHT VERTICAL AND LEFT, reverse video
    case 0x1FB7F:
      return 0xFA; // RIGHT AND LOWER ONE EIGHTH BLOCK, reverse video
    case 0x2518:
      return 0xFD; // BOX DRAWINGS LIGHT UP AND LEFT, reverse video
    }
  }
};

template <size_t N> struct ShiftedVideoString {
  char Str[N]{};

  constexpr ShiftedVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr ShiftedVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr ShiftedVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

      // Name: Map from Commodore VIC-20 (video) alternate character set to
      // Unicode

      // Date: 2018 October 11

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0040:
      return 0x00; // COMMERCIAL AT
    case 0x0061:
      return 0x01; // LATIN SMALL LETTER A
    case 0x0062:
      return 0x02; // LATIN SMALL LETTER B
    case 0x0063:
      return 0x03; // LATIN SMALL LETTER C
    case 0x0064:
      return 0x04; // LATIN SMALL LETTER D
    case 0x0065:
      return 0x05; // LATIN SMALL LETTER E
    case 0x0066:
      return 0x06; // LATIN SMALL LETTER F
    case 0x0067:
      return 0x07; // LATIN SMALL LETTER G
    case 0x0068:
      return 0x08; // LATIN SMALL LETTER H
    case 0x0069:
      return 0x09; // LATIN SMALL LETTER I
    case 0x006A:
      return 0x0A; // LATIN SMALL LETTER J
    case 0x006B:
      return 0x0B; // LATIN SMALL LETTER K
    case 0x006C:
      return 0x0C; // LATIN SMALL LETTER L
    case 0x006D:
      return 0x0D; // LATIN SMALL LETTER M
    case 0x006E:
      return 0x0E; // LATIN SMALL LETTER N
    case 0x006F:
      return 0x0F; // LATIN SMALL LETTER O
    case 0x0070:
      return 0x10; // LATIN SMALL LETTER P
    case 0x0071:
      return 0x11; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0x12; // LATIN SMALL LETTER R
    case 0x0073:
      return 0x13; // LATIN SMALL LETTER S
    case 0x0074:
      return 0x14; // LATIN SMALL LETTER T
    case 0x0075:
      return 0x15; // LATIN SMALL LETTER U
    case 0x0076:
      return 0x16; // LATIN SMALL LETTER V
    case 0x0077:
      return 0x17; // LATIN SMALL LETTER W
    case 0x0078:
      return 0x18; // LATIN SMALL LETTER X
    case 0x0079:
      return 0x19; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0x1A; // LATIN SMALL LETTER Z
    case 0x005B:
      return 0x1B; // LEFT SQUARE BRACKET
    case 0x00A3:
      return 0x1C; // POUND SIGN
    case 0x005D:
      return 0x1D; // RIGHT SQUARE BRACKET
    case 0x2191:
      return 0x1E; // UPWARDS ARROW
    case 0x2190:
      return 0x1F; // LEFTWARDS ARROW
    case 0x0020:
      return 0x20; // SPACE
    case 0x0021:
      return 0x21; // EXCLAMATION MARK
    case 0x0022:
      return 0x22; // QUOTATION MARK
    case 0x0023:
      return 0x23; // NUMBER SIGN
    case 0x0024:
      return 0x24; // DOLLAR SIGN
    case 0x0025:
      return 0x25; // PERCENT SIGN
    case 0x0026:
      return 0x26; // AMPERSAND
    case 0x0027:
      return 0x27; // APOSTROPHE
    case 0x0028:
      return 0x28; // LEFT PARENTHESIS
    case 0x0029:
      return 0x29; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x2A; // ASTERISK
    case 0x002B:
      return 0x2B; // PLUS SIGN
    case 0x002C:
      return 0x2C; // COMMA
    case 0x002D:
      return 0x2D; // HYPHEN-MINUS
    case 0x002E:
      return 0x2E; // FULL STOP
    case 0x002F:
      return 0x2F; // SOLIDUS
    case 0x0030:
      return 0x30; // DIGIT ZERO
    case 0x0031:
      return 0x31; // DIGIT ONE
    case 0x0032:
      return 0x32; // DIGIT TWO
    case 0x0033:
      return 0x33; // DIGIT THREE
    case 0x0034:
      return 0x34; // DIGIT FOUR
    case 0x0035:
      return 0x35; // DIGIT FIVE
    case 0x0036:
      return 0x36; // DIGIT SIX
    case 0x0037:
      return 0x37; // DIGIT SEVEN
    case 0x0038:
      return 0x38; // DIGIT EIGHT
    case 0x0039:
      return 0x39; // DIGIT NINE
    case 0x003A:
      return 0x3A; // COLON
    case 0x003B:
      return 0x3B; // SEMICOLON
    case 0x003C:
      return 0x3C; // LESS-THAN SIGN
    case 0x003D:
      return 0x3D; // EQUALS SIGN
    case 0x003E:
      return 0x3E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x3F; // QUESTION MARK
    case 0x2500:
      return 0x40; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x0041:
      return 0x41; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0x42; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0x43; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0x44; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0x45; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0x46; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0x47; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0x48; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0x49; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0x4A; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0x4B; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0x4C; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0x4D; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0x4E; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0x4F; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0x50; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0x51; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0x52; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0x53; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0x54; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0x55; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0x56; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0x57; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0x58; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0x59; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0x5A; // LATIN CAPITAL LETTER Z
    case 0x253C:
      return 0x5B; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x1FB8C:
      return 0x5C; // LEFT HALF MEDIUM SHADE
    case 0x2502:
      return 0x5D; // BOX DRAWINGS LIGHT VERTICAL
    case 0x1FB95:
      return 0x5E; // CHECKER BOARD FILL
    case 0x1FB98:
      return 0x5F; // UPPER LEFT TO LOWER RIGHT FILL
    case 0x00A0:
      return 0x60; // NO-BREAK SPACE
    case 0x258C:
      return 0x61; // LEFT HALF BLOCK
    case 0x2584:
      return 0x62; // LOWER HALF BLOCK
    case 0x2594:
      return 0x63; // UPPER ONE EIGHTH BLOCK
    case 0x2581:
      return 0x64; // LOWER ONE EIGHTH BLOCK
    case 0x258F:
      return 0x65; // LEFT ONE EIGHTH BLOCK
    case 0x2592:
      return 0x66; // MEDIUM SHADE
    case 0x2595:
      return 0x67; // RIGHT ONE EIGHTH BLOCK
    case 0x1FB8F:
      return 0x68; // LOWER HALF MEDIUM SHADE
    case 0x1FB99:
      return 0x69; // UPPER RIGHT TO LOWER LEFT FILL
    case 0x1FB87:
      return 0x6A; // RIGHT ONE QUARTER BLOCK
    case 0x251C:
      return 0x6B; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x2597:
      return 0x6C; // QUADRANT LOWER RIGHT
    case 0x2514:
      return 0x6D; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x2510:
      return 0x6E; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2582:
      return 0x6F; // LOWER ONE QUARTER BLOCK
    case 0x250C:
      return 0x70; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2534:
      return 0x71; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x252C:
      return 0x72; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2524:
      return 0x73; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x258E:
      return 0x74; // LEFT ONE QUARTER BLOCK
    case 0x258D:
      return 0x75; // LEFT THREE EIGHTHS BLOCK
    case 0x1FB88:
      return 0x76; // RIGHT THREE EIGHTHS BLOCK
    case 0x1FB82:
      return 0x77; // UPPER ONE QUARTER BLOCK
    case 0x1FB83:
      return 0x78; // UPPER THREE EIGHTHS BLOCK
    case 0x2583:
      return 0x79; // LOWER THREE EIGHTHS BLOCK
    case 0x2713:
      return 0x7A; // CHECK MARK
    case 0x2596:
      return 0x7B; // QUADRANT LOWER LEFT
    case 0x259D:
      return 0x7C; // QUADRANT UPPER RIGHT
    case 0x2518:
      return 0x7D; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2598:
      return 0x7E; // QUADRANT UPPER LEFT
    case 0x259A:
      return 0x7F; // QUADRANT UPPER LEFT AND LOWER RIGHT
    case 0x1FB94:
      return 0xDC; // LEFT HALF INVERSE MEDIUM SHADE AND RIGHT HALF BLOCK
    case 0x1FB96:
      return 0xDE; // INVERSE CHECKER BOARD FILL
    case 0x2588:
      return 0xE0; // FULL BLOCK
    case 0x2590:
      return 0xE1; // RIGHT HALF BLOCK
    case 0x2580:
      return 0xE2; // UPPER HALF BLOCK
    case 0x2587:
      return 0xE3; // LOWER SEVEN EIGHTHS BLOCK
    case 0x1FB86:
      return 0xE4; // UPPER SEVEN EIGHTHS BLOCK
    case 0x1FB8B:
      return 0xE5; // RIGHT SEVEN EIGHTHS BLOCK
    case 0x1FB90:
      return 0xE6; // INVERSE MEDIUM SHADE
    case 0x2589:
      return 0xE7; // LEFT SEVEN EIGHTHS BLOCK
    case 0x1FB91:
      return 0xE8; // UPPER HALF BLOCK AND LOWER HALF INVERSE MEDIUM SHADE
    case 0x258A:
      return 0xEA; // LEFT THREE QUARTERS BLOCK
    case 0x259B:
      return 0xEC; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER LEFT
    case 0x1FB85:
      return 0xEF; // UPPER THREE QUARTERS BLOCK
    case 0x1FB8A:
      return 0xF4; // RIGHT THREE QUARTERS BLOCK
    case 0x1FB89:
      return 0xF5; // RIGHT FIVE EIGHTHS BLOCK
    case 0x258B:
      return 0xF6; // LEFT FIVE EIGHTHS BLOCK
    case 0x2586:
      return 0xF7; // LOWER THREE QUARTERS BLOCK
    case 0x2585:
      return 0xF8; // LOWER FIVE EIGHTHS BLOCK
    case 0x1FB84:
      return 0xF9; // UPPER FIVE EIGHTHS BLOCK
    case 0x1FBB1:
      return 0xFA; // INVERSE CHECK MARK
    case 0x259C:
      return 0xFB; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER RIGHT
    case 0x2599:
      return 0xFC; // QUADRANT UPPER LEFT AND LOWER LEFT AND LOWER RIGHT
    case 0x259F:
      return 0xFE; // QUADRANT UPPER RIGHT AND LOWER LEFT AND LOWER RIGHT
    case 0x259E:
      return 0xFF; // QUADRANT UPPER RIGHT AND LOWER LEFT
    }
  }
};

template <size_t N> struct ShiftedReverseVideoString {
  char Str[N]{};

  constexpr ShiftedReverseVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr ShiftedReverseVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr ShiftedReverseVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

      // Name: Map from Commodore VIC-20 (video) alternate character set to
      // Unicode

      // Date: 2018 October 11

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0040:
      return 0x80; // COMMERCIAL AT, reverse video
    case 0x0061:
      return 0x81; // LATIN SMALL LETTER A, reverse video
    case 0x0062:
      return 0x82; // LATIN SMALL LETTER B, reverse video
    case 0x0063:
      return 0x83; // LATIN SMALL LETTER C, reverse video
    case 0x0064:
      return 0x84; // LATIN SMALL LETTER D, reverse video
    case 0x0065:
      return 0x85; // LATIN SMALL LETTER E, reverse video
    case 0x0066:
      return 0x86; // LATIN SMALL LETTER F, reverse video
    case 0x0067:
      return 0x87; // LATIN SMALL LETTER G, reverse video
    case 0x0068:
      return 0x88; // LATIN SMALL LETTER H, reverse video
    case 0x0069:
      return 0x89; // LATIN SMALL LETTER I, reverse video
    case 0x006A:
      return 0x8A; // LATIN SMALL LETTER J, reverse video
    case 0x006B:
      return 0x8B; // LATIN SMALL LETTER K, reverse video
    case 0x006C:
      return 0x8C; // LATIN SMALL LETTER L, reverse video
    case 0x006D:
      return 0x8D; // LATIN SMALL LETTER M, reverse video
    case 0x006E:
      return 0x8E; // LATIN SMALL LETTER N, reverse video
    case 0x006F:
      return 0x8F; // LATIN SMALL LETTER O, reverse video
    case 0x0070:
      return 0x90; // LATIN SMALL LETTER P, reverse video
    case 0x0071:
      return 0x91; // LATIN SMALL LETTER Q, reverse video
    case 0x0072:
      return 0x92; // LATIN SMALL LETTER R, reverse video
    case 0x0073:
      return 0x93; // LATIN SMALL LETTER S, reverse video
    case 0x0074:
      return 0x94; // LATIN SMALL LETTER T, reverse video
    case 0x0075:
      return 0x95; // LATIN SMALL LETTER U, reverse video
    case 0x0076:
      return 0x96; // LATIN SMALL LETTER V, reverse video
    case 0x0077:
      return 0x97; // LATIN SMALL LETTER W, reverse video
    case 0x0078:
      return 0x98; // LATIN SMALL LETTER X, reverse video
    case 0x0079:
      return 0x99; // LATIN SMALL LETTER Y, reverse video
    case 0x007A:
      return 0x9A; // LATIN SMALL LETTER Z, reverse video
    case 0x005B:
      return 0x9B; // LEFT SQUARE BRACKET, reverse video
    case 0x00A3:
      return 0x9C; // POUND SIGN, reverse video
    case 0x005D:
      return 0x9D; // RIGHT SQUARE BRACKET, reverse video
    case 0x2191:
      return 0x9E; // UPWARDS ARROW, reverse video
    case 0x2190:
      return 0x9F; // LEFTWARDS ARROW, reverse video
    case 0x0020:
      return 0xA0; // SPACE, reverse video
    case 0x0021:
      return 0xA1; // EXCLAMATION MARK, reverse video
    case 0x0022:
      return 0xA2; // QUOTATION MARK, reverse video
    case 0x0023:
      return 0xA3; // NUMBER SIGN, reverse video
    case 0x0024:
      return 0xA4; // DOLLAR SIGN, reverse video
    case 0x0025:
      return 0xA5; // PERCENT SIGN, reverse video
    case 0x0026:
      return 0xA6; // AMPERSAND, reverse video
    case 0x0027:
      return 0xA7; // APOSTROPHE, reverse video
    case 0x0028:
      return 0xA8; // LEFT PARENTHESIS, reverse video
    case 0x0029:
      return 0xA9; // RIGHT PARENTHESIS, reverse video
    case 0x002A:
      return 0xAA; // ASTERISK, reverse video
    case 0x002B:
      return 0xAB; // PLUS SIGN, reverse video
    case 0x002C:
      return 0xAC; // COMMA, reverse video
    case 0x002D:
      return 0xAD; // HYPHEN-MINUS, reverse video
    case 0x002E:
      return 0xAE; // FULL STOP, reverse video
    case 0x002F:
      return 0xAF; // SOLIDUS, reverse video
    case 0x0030:
      return 0xB0; // DIGIT ZERO, reverse video
    case 0x0031:
      return 0xB1; // DIGIT ONE, reverse video
    case 0x0032:
      return 0xB2; // DIGIT TWO, reverse video
    case 0x0033:
      return 0xB3; // DIGIT THREE, reverse video
    case 0x0034:
      return 0xB4; // DIGIT FOUR, reverse video
    case 0x0035:
      return 0xB5; // DIGIT FIVE, reverse video
    case 0x0036:
      return 0xB6; // DIGIT SIX, reverse video
    case 0x0037:
      return 0xB7; // DIGIT SEVEN, reverse video
    case 0x0038:
      return 0xB8; // DIGIT EIGHT, reverse video
    case 0x0039:
      return 0xB9; // DIGIT NINE, reverse video
    case 0x003A:
      return 0xBA; // COLON, reverse video
    case 0x003B:
      return 0xBB; // SEMICOLON, reverse video
    case 0x003C:
      return 0xBC; // LESS-THAN SIGN, reverse video
    case 0x003D:
      return 0xBD; // EQUALS SIGN, reverse video
    case 0x003E:
      return 0xBE; // GREATER-THAN SIGN, reverse video
    case 0x003F:
      return 0xBF; // QUESTION MARK, reverse video
    case 0x2500:
      return 0xC0; // BOX DRAWINGS LIGHT HORIZONTAL, reverse video
    case 0x0041:
      return 0xC1; // LATIN CAPITAL LETTER A, reverse video
    case 0x0042:
      return 0xC2; // LATIN CAPITAL LETTER B, reverse video
    case 0x0043:
      return 0xC3; // LATIN CAPITAL LETTER C, reverse video
    case 0x0044:
      return 0xC4; // LATIN CAPITAL LETTER D, reverse video
    case 0x0045:
      return 0xC5; // LATIN CAPITAL LETTER E, reverse video
    case 0x0046:
      return 0xC6; // LATIN CAPITAL LETTER F, reverse video
    case 0x0047:
      return 0xC7; // LATIN CAPITAL LETTER G, reverse video
    case 0x0048:
      return 0xC8; // LATIN CAPITAL LETTER H, reverse video
    case 0x0049:
      return 0xC9; // LATIN CAPITAL LETTER I, reverse video
    case 0x004A:
      return 0xCA; // LATIN CAPITAL LETTER J, reverse video
    case 0x004B:
      return 0xCB; // LATIN CAPITAL LETTER K, reverse video
    case 0x004C:
      return 0xCC; // LATIN CAPITAL LETTER L, reverse video
    case 0x004D:
      return 0xCD; // LATIN CAPITAL LETTER M, reverse video
    case 0x004E:
      return 0xCE; // LATIN CAPITAL LETTER N, reverse video
    case 0x004F:
      return 0xCF; // LATIN CAPITAL LETTER O, reverse video
    case 0x0050:
      return 0xD0; // LATIN CAPITAL LETTER P, reverse video
    case 0x0051:
      return 0xD1; // LATIN CAPITAL LETTER Q, reverse video
    case 0x0052:
      return 0xD2; // LATIN CAPITAL LETTER R, reverse video
    case 0x0053:
      return 0xD3; // LATIN CAPITAL LETTER S, reverse video
    case 0x0054:
      return 0xD4; // LATIN CAPITAL LETTER T, reverse video
    case 0x0055:
      return 0xD5; // LATIN CAPITAL LETTER U, reverse video
    case 0x0056:
      return 0xD6; // LATIN CAPITAL LETTER V, reverse video
    case 0x0057:
      return 0xD7; // LATIN CAPITAL LETTER W, reverse video
    case 0x0058:
      return 0xD8; // LATIN CAPITAL LETTER X, reverse video
    case 0x0059:
      return 0xD9; // LATIN CAPITAL LETTER Y, reverse video
    case 0x005A:
      return 0xDA; // LATIN CAPITAL LETTER Z, reverse video
    case 0x253C:
      return 0xDB; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL, reverse video
    case 0x2502:
      return 0xDD; // BOX DRAWINGS LIGHT VERTICAL, reverse video
    case 0x1FB98:
      return 0xDF; // UPPER LEFT TO LOWER RIGHT FILL, reverse video
    case 0x1FB99:
      return 0xE9; // UPPER RIGHT TO LOWER LEFT FILL, reverse video
    case 0x251C:
      return 0xEB; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT, reverse video
    case 0x2514:
      return 0xED; // BOX DRAWINGS LIGHT UP AND RIGHT, reverse video
    case 0x2510:
      return 0xEE; // BOX DRAWINGS LIGHT DOWN AND LEFT, reverse video
    case 0x250C:
      return 0xF0; // BOX DRAWINGS LIGHT DOWN AND RIGHT, reverse video
    case 0x2534:
      return 0xF1; // BOX DRAWINGS LIGHT UP AND HORIZONTAL, reverse video
    case 0x252C:
      return 0xF2; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL, reverse video
    case 0x2524:
      return 0xF3; // BOX DRAWINGS LIGHT VERTICAL AND LEFT, reverse video
    case 0x2518:
      return 0xFD; // BOX DRAWINGS LIGHT UP AND LEFT, reverse video
    }
  }
};

} // namespace charset_impl

template <charset_impl::UnshiftedString S> constexpr auto operator""_u() {
  return S.Str;
}
template <charset_impl::ShiftedString S> constexpr auto operator""_s() {
  return S.Str;
}

template <charset_impl::UnshiftedVideoString S> constexpr auto operator""_uv() {
  return S.Str;
}

template <charset_impl::UnshiftedReverseVideoString S>
constexpr auto operator""_urv() {
  return S.Str;
}

template <charset_impl::ShiftedVideoString S> constexpr auto operator""_sv() {
  return S.Str;
}

template <charset_impl::ShiftedReverseVideoString S>
constexpr auto operator""_srv() {
  return S.Str;
}

#endif // not _CHARSET_H
#endif // __cplusplus >= 202002L
