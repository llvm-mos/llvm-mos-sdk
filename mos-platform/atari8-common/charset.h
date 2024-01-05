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

template <size_t N> struct AtasciiString {
  char Str[N]{};

  constexpr AtasciiString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr AtasciiString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr AtasciiString(char32_t const (&Src)[N]) {
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

      // Name: Map from Atari 8-bit series (interchange) graphics character
      // set to Unicode

      // Date: 2018 April 20

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

      // UNICODE LICENSE V3
      // Copyright © 1991-2023 Unicode, Inc.

    case 0x2665:
      return 0x00; // BLACK HEART SUIT
    case 0x251C:
      return 0x01; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x23B9:
      return 0x02; // RIGHT VERTICAL BOX LINE
    case 0x2518:
      return 0x03; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2524:
      return 0x04; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x2510:
      return 0x05; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2571:
      return 0x06; // BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT
    case 0x2572:
      return 0x07; // BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT
    case 0x25E2:
      return 0x08; // BLACK LOWER RIGHT TRIANGLE
    case 0x2597:
      return 0x09; // QUADRANT LOWER RIGHT
    case 0x25E3:
      return 0x0A; // BLACK LOWER LEFT TRIANGLE
    case 0x259D:
      return 0x0B; // QUADRANT UPPER RIGHT
    case 0x2598:
      return 0x0C; // QUADRANT UPPER LEFT
    case 0x23BA:
      return 0x0D; // HORIZONTAL SCAN LINE-1
    case 0x23BD:
      return 0x0E; // HORIZONTAL SCAN LINE-9
    case 0x2596:
      return 0x0F; // QUADRANT LOWER LEFT
    case 0x2663:
      return 0x10; // BLACK CLUB SUIT
    case 0x250C:
      return 0x11; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2500:
      return 0x12; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x253C:
      return 0x13; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x2022:
      return 0x14; // BULLET
    case 0x2584:
      return 0x15; // LOWER HALF BLOCK
    case 0x23B8:
      return 0x16; // LEFT VERTICAL BOX LINE
    case 0x252C:
      return 0x17; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2534:
      return 0x18; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x258C:
      return 0x19; // LEFT HALF BLOCK
    case 0x2514:
      return 0x1A; // BOX DRAWINGS LIGHT UP AND RIGHT
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
    case 0x005C:
      return 0x5C; // REVERSE SOLIDUS
    case 0x005D:
      return 0x5D; // RIGHT SQUARE BRACKET
    case 0x005E:
      return 0x5E; // CIRCUMFLEX ACCENT
    case 0x005F:
      return 0x5F; // LOW LINE
    case 0x2666:
      return 0x60; // BLACK DIAMOND SUIT
    case 0x0061:
      return 0x61; // LATIN SMALL LETTER A
    case 0x0062:
      return 0x62; // LATIN SMALL LETTER B
    case 0x0063:
      return 0x63; // LATIN SMALL LETTER C
    case 0x0064:
      return 0x64; // LATIN SMALL LETTER D
    case 0x0065:
      return 0x65; // LATIN SMALL LETTER E
    case 0x0066:
      return 0x66; // LATIN SMALL LETTER F
    case 0x0067:
      return 0x67; // LATIN SMALL LETTER G
    case 0x0068:
      return 0x68; // LATIN SMALL LETTER H
    case 0x0069:
      return 0x69; // LATIN SMALL LETTER I
    case 0x006A:
      return 0x6A; // LATIN SMALL LETTER J
    case 0x006B:
      return 0x6B; // LATIN SMALL LETTER K
    case 0x006C:
      return 0x6C; // LATIN SMALL LETTER L
    case 0x006D:
      return 0x6D; // LATIN SMALL LETTER M
    case 0x006E:
      return 0x6E; // LATIN SMALL LETTER N
    case 0x006F:
      return 0x6F; // LATIN SMALL LETTER O
    case 0x0070:
      return 0x70; // LATIN SMALL LETTER P
    case 0x0071:
      return 0x71; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0x72; // LATIN SMALL LETTER R
    case 0x0073:
      return 0x73; // LATIN SMALL LETTER S
    case 0x0074:
      return 0x74; // LATIN SMALL LETTER T
    case 0x0075:
      return 0x75; // LATIN SMALL LETTER U
    case 0x0076:
      return 0x76; // LATIN SMALL LETTER V
    case 0x0077:
      return 0x77; // LATIN SMALL LETTER W
    case 0x0078:
      return 0x78; // LATIN SMALL LETTER X
    case 0x0079:
      return 0x79; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0x7A; // LATIN SMALL LETTER Z
    case 0x2660:
      return 0x7B; // BLACK SPADE SUIT
    case 0x007C:
      return 0x7C; // VERTICAL LINE
    case 0x25E4:
      return 0x88; // BLACK UPPER LEFT TRIANGLE
    case 0x259B:
      return 0x89; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER LEFT
    case 0x25E5:
      return 0x8A; // BLACK UPPER RIGHT TRIANGLE
    case 0x2599:
      return 0x8B; // QUADRANT UPPER LEFT AND LOWER LEFT AND LOWER RIGHT
    case 0x259F:
      return 0x8C; // QUADRANT UPPER RIGHT AND LOWER LEFT AND LOWER RIGHT
    case 0x259C:
      return 0x8F; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER RIGHT
    case 0x25D8:
      return 0x94; // INVERSE BULLET
    case 0x2580:
      return 0x95; // UPPER HALF BLOCK
    case 0x2590:
      return 0x99; // RIGHT HALF BLOCK
    }
  }
};

template <size_t N> struct AtasciiInternationalString {
  char Str[N]{};

  constexpr AtasciiInternationalString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr AtasciiInternationalString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr AtasciiInternationalString(char32_t const (&Src)[N]) {
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

      // Name: Map from Atari 8-bit series (interchange) international
      // character set to Unicode

      // Date: 2018 April 20

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

      // UNICODE LICENSE V3
      // Copyright © 1991-2023 Unicode, Inc.

    case 0x00E1:
      return 0x00; // LATIN SMALL LETTER A WITH ACUTE
    case 0x00F9:
      return 0x01; // LATIN SMALL LETTER U WITH GRAVE
    case 0x00D1:
      return 0x02; // LATIN CAPITAL LETTER N WITH TILDE
    case 0x00C9:
      return 0x03; // LATIN CAPITAL LETTER E WITH ACUTE
    case 0x00E7:
      return 0x04; // LATIN SMALL LETTER C WITH CEDILLA
    case 0x00F4:
      return 0x05; // LATIN SMALL LETTER O WITH CIRCUMFLEX
    case 0x00F2:
      return 0x06; // LATIN SMALL LETTER O WITH GRAVE
    case 0x00EC:
      return 0x07; // LATIN SMALL LETTER I WITH GRAVE
    case 0x00A3:
      return 0x08; // POUND SIGN
    case 0x00EF:
      return 0x09; // LATIN SMALL LETTER I WITH DIAERESIS
    case 0x00FC:
      return 0x0A; // LATIN SMALL LETTER U WITH DIAERESIS
    case 0x00E4:
      return 0x0B; // LATIN SMALL LETTER A WITH DIAERESIS
    case 0x00D6:
      return 0x0C; // LATIN CAPITAL LETTER O WITH DIAERESIS
    case 0x00FA:
      return 0x0D; // LATIN SMALL LETTER U WITH ACUTE
    case 0x00F3:
      return 0x0E; // LATIN SMALL LETTER O WITH ACUTE
    case 0x00F6:
      return 0x0F; // LATIN SMALL LETTER O WITH DIAERESIS
    case 0x00DC:
      return 0x10; // LATIN CAPITAL LETTER U WITH DIAERESIS
    case 0x00E2:
      return 0x11; // LATIN SMALL LETTER A WITH CIRCUMFLEX
    case 0x00FB:
      return 0x12; // LATIN SMALL LETTER U WITH CIRCUMFLEX
    case 0x00EE:
      return 0x13; // LATIN SMALL LETTER I WITH CIRCUMFLEX
    case 0x00E9:
      return 0x14; // LATIN SMALL LETTER E WITH ACUTE
    case 0x00E8:
      return 0x15; // LATIN SMALL LETTER E WITH GRAVE
    case 0x00F1:
      return 0x16; // LATIN SMALL LETTER N WITH TILDE
    case 0x00EA:
      return 0x17; // LATIN SMALL LETTER E WITH CIRCUMFLEX
    case 0x00E5:
      return 0x18; // LATIN SMALL LETTER A WITH RING ABOVE
    case 0x00E0:
      return 0x19; // LATIN SMALL LETTER A WITH GRAVE
    case 0x00C5:
      return 0x1A; // LATIN CAPITAL LETTER A WITH RING ABOVE
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
    case 0x005C:
      return 0x5C; // REVERSE SOLIDUS
    case 0x005D:
      return 0x5D; // RIGHT SQUARE BRACKET
    case 0x005E:
      return 0x5E; // CIRCUMFLEX ACCENT
    case 0x005F:
      return 0x5F; // LOW LINE
    case 0x00A1:
      return 0x60; // INVERTED EXCLAMATION MARK
    case 0x0061:
      return 0x61; // LATIN SMALL LETTER A
    case 0x0062:
      return 0x62; // LATIN SMALL LETTER B
    case 0x0063:
      return 0x63; // LATIN SMALL LETTER C
    case 0x0064:
      return 0x64; // LATIN SMALL LETTER D
    case 0x0065:
      return 0x65; // LATIN SMALL LETTER E
    case 0x0066:
      return 0x66; // LATIN SMALL LETTER F
    case 0x0067:
      return 0x67; // LATIN SMALL LETTER G
    case 0x0068:
      return 0x68; // LATIN SMALL LETTER H
    case 0x0069:
      return 0x69; // LATIN SMALL LETTER I
    case 0x006A:
      return 0x6A; // LATIN SMALL LETTER J
    case 0x006B:
      return 0x6B; // LATIN SMALL LETTER K
    case 0x006C:
      return 0x6C; // LATIN SMALL LETTER L
    case 0x006D:
      return 0x6D; // LATIN SMALL LETTER M
    case 0x006E:
      return 0x6E; // LATIN SMALL LETTER N
    case 0x006F:
      return 0x6F; // LATIN SMALL LETTER O
    case 0x0070:
      return 0x70; // LATIN SMALL LETTER P
    case 0x0071:
      return 0x71; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0x72; // LATIN SMALL LETTER R
    case 0x0073:
      return 0x73; // LATIN SMALL LETTER S
    case 0x0074:
      return 0x74; // LATIN SMALL LETTER T
    case 0x0075:
      return 0x75; // LATIN SMALL LETTER U
    case 0x0076:
      return 0x76; // LATIN SMALL LETTER V
    case 0x0077:
      return 0x77; // LATIN SMALL LETTER W
    case 0x0078:
      return 0x78; // LATIN SMALL LETTER X
    case 0x0079:
      return 0x79; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0x7A; // LATIN SMALL LETTER Z
    case 0x00C4:
      return 0x7B; // LATIN CAPITAL LETTER A WITH DIAERESIS
    case 0x007C:
      return 0x7C; // VERTICAL LINE
    }
  };
};

template <size_t N> struct AtasciiVideoString {
  char Str[N]{};

  constexpr AtasciiVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr AtasciiVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr AtasciiVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

    // Preserve NUL
    case 0x0000:
      return 0x00;

      // Name: Map from Atari 8-bit series (video) graphics character set to
      // Unicode

      // Date: 2018 August 16

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0020:
      return 0x00; // SPACE
    case 0x0021:
      return 0x01; // EXCLAMATION MARK
    case 0x0022:
      return 0x02; // QUOTATION MARK
    case 0x0023:
      return 0x03; // NUMBER SIGN
    case 0x0024:
      return 0x04; // DOLLAR SIGN
    case 0x0025:
      return 0x05; // PERCENT SIGN
    case 0x0026:
      return 0x06; // AMPERSAND
    case 0x0027:
      return 0x07; // APOSTROPHE
    case 0x0028:
      return 0x08; // LEFT PARENTHESIS
    case 0x0029:
      return 0x09; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x0A; // ASTERISK
    case 0x002B:
      return 0x0B; // PLUS SIGN
    case 0x002C:
      return 0x0C; // COMMA
    case 0x002D:
      return 0x0D; // HYPHEN-MINUS
    case 0x002E:
      return 0x0E; // FULL STOP
    case 0x002F:
      return 0x0F; // SOLIDUS
    case 0x0030:
      return 0x10; // DIGIT ZERO
    case 0x0031:
      return 0x11; // DIGIT ONE
    case 0x0032:
      return 0x12; // DIGIT TWO
    case 0x0033:
      return 0x13; // DIGIT THREE
    case 0x0034:
      return 0x14; // DIGIT FOUR
    case 0x0035:
      return 0x15; // DIGIT FIVE
    case 0x0036:
      return 0x16; // DIGIT SIX
    case 0x0037:
      return 0x17; // DIGIT SEVEN
    case 0x0038:
      return 0x18; // DIGIT EIGHT
    case 0x0039:
      return 0x19; // DIGIT NINE
    case 0x003A:
      return 0x1A; // COLON
    case 0x003B:
      return 0x1B; // SEMICOLON
    case 0x003C:
      return 0x1C; // LESS-THAN SIGN
    case 0x003D:
      return 0x1D; // EQUALS SIGN
    case 0x003E:
      return 0x1E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x1F; // QUESTION MARK
    case 0x0040:
      return 0x20; // COMMERCIAL AT
    case 0x0041:
      return 0x21; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0x22; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0x23; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0x24; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0x25; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0x26; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0x27; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0x28; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0x29; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0x2A; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0x2B; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0x2C; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0x2D; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0x2E; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0x2F; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0x30; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0x31; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0x32; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0x33; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0x34; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0x35; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0x36; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0x37; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0x38; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0x39; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0x3A; // LATIN CAPITAL LETTER Z
    case 0x005B:
      return 0x3B; // LEFT SQUARE BRACKET
    case 0x005C:
      return 0x3C; // REVERSE SOLIDUS
    case 0x005D:
      return 0x3D; // RIGHT SQUARE BRACKET
    case 0x005E:
      return 0x3E; // CIRCUMFLEX ACCENT
    case 0x005F:
      return 0x3F; // LOW LINE
    case 0x2665:
      return 0x40; // BLACK HEART SUIT
    case 0x251C:
      return 0x41; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x23B9:
      return 0x42; // RIGHT VERTICAL BOX LINE
    case 0x2518:
      return 0x43; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2524:
      return 0x44; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x2510:
      return 0x45; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2571:
      return 0x46; // BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT
    case 0x2572:
      return 0x47; // BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT
    case 0x25E2:
      return 0x48; // BLACK LOWER RIGHT TRIANGLE
    case 0x2597:
      return 0x49; // QUADRANT LOWER RIGHT
    case 0x25E3:
      return 0x4A; // BLACK LOWER LEFT TRIANGLE
    case 0x259D:
      return 0x4B; // QUADRANT UPPER RIGHT
    case 0x2598:
      return 0x4C; // QUADRANT UPPER LEFT
    case 0x23BA:
      return 0x4D; // HORIZONTAL SCAN LINE-1
    case 0x23BD:
      return 0x4E; // HORIZONTAL SCAN LINE-9
    case 0x2596:
      return 0x4F; // QUADRANT LOWER LEFT
    case 0x2663:
      return 0x50; // BLACK CLUB SUIT
    case 0x250C:
      return 0x51; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2500:
      return 0x52; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x253C:
      return 0x53; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x2022:
      return 0x54; // BULLET
    case 0x2584:
      return 0x55; // LOWER HALF BLOCK
    case 0x23B8:
      return 0x56; // LEFT VERTICAL BOX LINE
    case 0x252C:
      return 0x57; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2534:
      return 0x58; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x258C:
      return 0x59; // LEFT HALF BLOCK
    case 0x2514:
      return 0x5A; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x241B:
      return 0x5B; // SYMBOL FOR ESCAPE
    case 0x2191:
      return 0x5C; // UPWARDS ARROW
    case 0x2193:
      return 0x5D; // DOWNWARDS ARROW
    case 0x2190:
      return 0x5E; // LEFTWARDS ARROW
    case 0x2192:
      return 0x5F; // RIGHTWARDS ARROW
    case 0x2666:
      return 0x60; // BLACK DIAMOND SUIT
    case 0x0061:
      return 0x61; // LATIN SMALL LETTER A
    case 0x0062:
      return 0x62; // LATIN SMALL LETTER B
    case 0x0063:
      return 0x63; // LATIN SMALL LETTER C
    case 0x0064:
      return 0x64; // LATIN SMALL LETTER D
    case 0x0065:
      return 0x65; // LATIN SMALL LETTER E
    case 0x0066:
      return 0x66; // LATIN SMALL LETTER F
    case 0x0067:
      return 0x67; // LATIN SMALL LETTER G
    case 0x0068:
      return 0x68; // LATIN SMALL LETTER H
    case 0x0069:
      return 0x69; // LATIN SMALL LETTER I
    case 0x006A:
      return 0x6A; // LATIN SMALL LETTER J
    case 0x006B:
      return 0x6B; // LATIN SMALL LETTER K
    case 0x006C:
      return 0x6C; // LATIN SMALL LETTER L
    case 0x006D:
      return 0x6D; // LATIN SMALL LETTER M
    case 0x006E:
      return 0x6E; // LATIN SMALL LETTER N
    case 0x006F:
      return 0x6F; // LATIN SMALL LETTER O
    case 0x0070:
      return 0x70; // LATIN SMALL LETTER P
    case 0x0071:
      return 0x71; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0x72; // LATIN SMALL LETTER R
    case 0x0073:
      return 0x73; // LATIN SMALL LETTER S
    case 0x0074:
      return 0x74; // LATIN SMALL LETTER T
    case 0x0075:
      return 0x75; // LATIN SMALL LETTER U
    case 0x0076:
      return 0x76; // LATIN SMALL LETTER V
    case 0x0077:
      return 0x77; // LATIN SMALL LETTER W
    case 0x0078:
      return 0x78; // LATIN SMALL LETTER X
    case 0x0079:
      return 0x79; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0x7A; // LATIN SMALL LETTER Z
    case 0x2660:
      return 0x7B; // BLACK SPADE SUIT
    case 0x007C:
      return 0x7C; // VERTICAL LINE
    case 0x1F8B0:
      return 0x7D; // ARROW POINTING UPWARDS THEN NORTH WEST
    case 0x25C0:
      return 0x7E; // BLACK LEFT-POINTING TRIANGLE
    case 0x25B6:
      return 0x7F; // BLACK RIGHT-POINTING TRIANGLE
    case 0x25E4:
      return 0xC8; // BLACK UPPER LEFT TRIANGLE
    case 0x259B:
      return 0xC9; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER LEFT
    case 0x25E5:
      return 0xCA; // BLACK UPPER RIGHT TRIANGLE
    case 0x2599:
      return 0xCB; // QUADRANT UPPER LEFT AND LOWER LEFT AND LOWER RIGHT
    case 0x259F:
      return 0xCC; // QUADRANT UPPER RIGHT AND LOWER LEFT AND LOWER RIGHT
    case 0x259C:
      return 0xCF; // QUADRANT UPPER LEFT AND UPPER RIGHT AND LOWER RIGHT
    case 0x25D8:
      return 0xD4; // INVERSE BULLET
    case 0x2580:
      return 0xD5; // UPPER HALF BLOCK
    case 0x2590:
      return 0xD9; // RIGHT HALF BLOCK
    }
  }
};

template <size_t N> struct AtasciiReverseVideoString {
  char Str[N]{};

  constexpr AtasciiReverseVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr AtasciiReverseVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr AtasciiReverseVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

    // Preserve NUL
    case 0x0000:
      return 0x00;

      // Name: Map from Atari 8-bit series (video) graphics character set to
      // Unicode

      // Date: 2018 August 16

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0020:
      return 0x80; // SPACE
    case 0x0021:
      return 0x81; // EXCLAMATION MARK
    case 0x0022:
      return 0x82; // QUOTATION MARK
    case 0x0023:
      return 0x83; // NUMBER SIGN
    case 0x0024:
      return 0x84; // DOLLAR SIGN
    case 0x0025:
      return 0x85; // PERCENT SIGN
    case 0x0026:
      return 0x86; // AMPERSAND
    case 0x0027:
      return 0x87; // APOSTROPHE
    case 0x0028:
      return 0x88; // LEFT PARENTHESIS
    case 0x0029:
      return 0x89; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x8A; // ASTERISK
    case 0x002B:
      return 0x8B; // PLUS SIGN
    case 0x002C:
      return 0x8C; // COMMA
    case 0x002D:
      return 0x8D; // HYPHEN-MINUS
    case 0x002E:
      return 0x8E; // FULL STOP
    case 0x002F:
      return 0x8F; // SOLIDUS
    case 0x0030:
      return 0x90; // DIGIT ZERO
    case 0x0031:
      return 0x91; // DIGIT ONE
    case 0x0032:
      return 0x92; // DIGIT TWO
    case 0x0033:
      return 0x93; // DIGIT THREE
    case 0x0034:
      return 0x94; // DIGIT FOUR
    case 0x0035:
      return 0x95; // DIGIT FIVE
    case 0x0036:
      return 0x96; // DIGIT SIX
    case 0x0037:
      return 0x97; // DIGIT SEVEN
    case 0x0038:
      return 0x98; // DIGIT EIGHT
    case 0x0039:
      return 0x99; // DIGIT NINE
    case 0x003A:
      return 0x9A; // COLON
    case 0x003B:
      return 0x9B; // SEMICOLON
    case 0x003C:
      return 0x9C; // LESS-THAN SIGN
    case 0x003D:
      return 0x9D; // EQUALS SIGN
    case 0x003E:
      return 0x9E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x9F; // QUESTION MARK
    case 0x0040:
      return 0xA0; // COMMERCIAL AT
    case 0x0041:
      return 0xA1; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0xA2; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0xA3; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0xA4; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0xA5; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0xA6; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0xA7; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0xA8; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0xA9; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0xAA; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0xAB; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0xAC; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0xAD; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0xAE; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0xAF; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0xB0; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0xB1; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0xB2; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0xB3; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0xB4; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0xB5; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0xB6; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0xB7; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0xB8; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0xB9; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0xBA; // LATIN CAPITAL LETTER Z
    case 0x005B:
      return 0xBB; // LEFT SQUARE BRACKET
    case 0x005C:
      return 0xBC; // REVERSE SOLIDUS
    case 0x005D:
      return 0xBD; // RIGHT SQUARE BRACKET
    case 0x005E:
      return 0xBE; // CIRCUMFLEX ACCENT
    case 0x005F:
      return 0xBF; // LOW LINE
    case 0x2665:
      return 0xC0; // BLACK HEART SUIT
    case 0x251C:
      return 0xC1; // BOX DRAWINGS LIGHT VERTICAL AND RIGHT
    case 0x23B9:
      return 0xC2; // RIGHT VERTICAL BOX LINE
    case 0x2518:
      return 0xC3; // BOX DRAWINGS LIGHT UP AND LEFT
    case 0x2524:
      return 0xC4; // BOX DRAWINGS LIGHT VERTICAL AND LEFT
    case 0x2510:
      return 0xC5; // BOX DRAWINGS LIGHT DOWN AND LEFT
    case 0x2571:
      return 0xC6; // BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT
    case 0x2572:
      return 0xC7; // BOX DRAWINGS LIGHT DIAGONAL UPPER LEFT TO LOWER RIGHT
    case 0x23BA:
      return 0xCD; // HORIZONTAL SCAN LINE-1
    case 0x23BD:
      return 0xCE; // HORIZONTAL SCAN LINE-9
    case 0x2663:
      return 0xD0; // BLACK CLUB SUIT
    case 0x250C:
      return 0xD1; // BOX DRAWINGS LIGHT DOWN AND RIGHT
    case 0x2500:
      return 0xD2; // BOX DRAWINGS LIGHT HORIZONTAL
    case 0x253C:
      return 0xD3; // BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
    case 0x23B8:
      return 0xD6; // LEFT VERTICAL BOX LINE
    case 0x252C:
      return 0xD7; // BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
    case 0x2534:
      return 0xD8; // BOX DRAWINGS LIGHT UP AND HORIZONTAL
    case 0x2514:
      return 0xDA; // BOX DRAWINGS LIGHT UP AND RIGHT
    case 0x241B:
      return 0xDB; // SYMBOL FOR ESCAPE
    case 0x2191:
      return 0xDC; // UPWARDS ARROW
    case 0x2193:
      return 0xDD; // DOWNWARDS ARROW
    case 0x2190:
      return 0xDE; // LEFTWARDS ARROW
    case 0x2192:
      return 0xDF; // RIGHTWARDS ARROW
    case 0x2666:
      return 0xE0; // BLACK DIAMOND SUIT
    case 0x0061:
      return 0xE1; // LATIN SMALL LETTER A
    case 0x0062:
      return 0xE2; // LATIN SMALL LETTER B
    case 0x0063:
      return 0xE3; // LATIN SMALL LETTER C
    case 0x0064:
      return 0xE4; // LATIN SMALL LETTER D
    case 0x0065:
      return 0xE5; // LATIN SMALL LETTER E
    case 0x0066:
      return 0xE6; // LATIN SMALL LETTER F
    case 0x0067:
      return 0xE7; // LATIN SMALL LETTER G
    case 0x0068:
      return 0xE8; // LATIN SMALL LETTER H
    case 0x0069:
      return 0xE9; // LATIN SMALL LETTER I
    case 0x006A:
      return 0xEA; // LATIN SMALL LETTER J
    case 0x006B:
      return 0xEB; // LATIN SMALL LETTER K
    case 0x006C:
      return 0xEC; // LATIN SMALL LETTER L
    case 0x006D:
      return 0xED; // LATIN SMALL LETTER M
    case 0x006E:
      return 0xEE; // LATIN SMALL LETTER N
    case 0x006F:
      return 0xEF; // LATIN SMALL LETTER O
    case 0x0070:
      return 0xF0; // LATIN SMALL LETTER P
    case 0x0071:
      return 0xF1; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0xF2; // LATIN SMALL LETTER R
    case 0x0073:
      return 0xF3; // LATIN SMALL LETTER S
    case 0x0074:
      return 0xF4; // LATIN SMALL LETTER T
    case 0x0075:
      return 0xF5; // LATIN SMALL LETTER U
    case 0x0076:
      return 0xF6; // LATIN SMALL LETTER V
    case 0x0077:
      return 0xF7; // LATIN SMALL LETTER W
    case 0x0078:
      return 0xF8; // LATIN SMALL LETTER X
    case 0x0079:
      return 0xF9; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0xFA; // LATIN SMALL LETTER Z
    case 0x2660:
      return 0xFB; // BLACK SPADE SUIT
    case 0x007C:
      return 0xFC; // VERTICAL LINE
    case 0x1F8B0:
      return 0xFD; // ARROW POINTING UPWARDS THEN NORTH WEST
    case 0x25C0:
      return 0xFE; // BLACK LEFT-POINTING TRIANGLE
    case 0x25B6:
      return 0xFF; // BLACK RIGHT-POINTING TRIANGLE
    }
  }
};

template <size_t N> struct AtasciiInternationalVideoString {
  char Str[N]{};

  constexpr AtasciiInternationalVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr AtasciiInternationalVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr AtasciiInternationalVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

    // Preserve NUL
    case 0x0000:
      return 0x00;

      // Name: Map from Atari 8-bit series (video) international character set
      // to Unicode

      // Date: 2018 August 16

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0020:
      return 0x00; // SPACE
    case 0x0021:
      return 0x01; // EXCLAMATION MARK
    case 0x0022:
      return 0x02; // QUOTATION MARK
    case 0x0023:
      return 0x03; // NUMBER SIGN
    case 0x0024:
      return 0x04; // DOLLAR SIGN
    case 0x0025:
      return 0x05; // PERCENT SIGN
    case 0x0026:
      return 0x06; // AMPERSAND
    case 0x0027:
      return 0x07; // APOSTROPHE
    case 0x0028:
      return 0x08; // LEFT PARENTHESIS
    case 0x0029:
      return 0x09; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x0A; // ASTERISK
    case 0x002B:
      return 0x0B; // PLUS SIGN
    case 0x002C:
      return 0x0C; // COMMA
    case 0x002D:
      return 0x0D; // HYPHEN-MINUS
    case 0x002E:
      return 0x0E; // FULL STOP
    case 0x002F:
      return 0x0F; // SOLIDUS
    case 0x0030:
      return 0x10; // DIGIT ZERO
    case 0x0031:
      return 0x11; // DIGIT ONE
    case 0x0032:
      return 0x12; // DIGIT TWO
    case 0x0033:
      return 0x13; // DIGIT THREE
    case 0x0034:
      return 0x14; // DIGIT FOUR
    case 0x0035:
      return 0x15; // DIGIT FIVE
    case 0x0036:
      return 0x16; // DIGIT SIX
    case 0x0037:
      return 0x17; // DIGIT SEVEN
    case 0x0038:
      return 0x18; // DIGIT EIGHT
    case 0x0039:
      return 0x19; // DIGIT NINE
    case 0x003A:
      return 0x1A; // COLON
    case 0x003B:
      return 0x1B; // SEMICOLON
    case 0x003C:
      return 0x1C; // LESS-THAN SIGN
    case 0x003D:
      return 0x1D; // EQUALS SIGN
    case 0x003E:
      return 0x1E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x1F; // QUESTION MARK
    case 0x0040:
      return 0x20; // COMMERCIAL AT
    case 0x0041:
      return 0x21; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0x22; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0x23; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0x24; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0x25; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0x26; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0x27; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0x28; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0x29; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0x2A; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0x2B; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0x2C; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0x2D; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0x2E; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0x2F; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0x30; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0x31; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0x32; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0x33; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0x34; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0x35; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0x36; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0x37; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0x38; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0x39; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0x3A; // LATIN CAPITAL LETTER Z
    case 0x005B:
      return 0x3B; // LEFT SQUARE BRACKET
    case 0x005C:
      return 0x3C; // REVERSE SOLIDUS
    case 0x005D:
      return 0x3D; // RIGHT SQUARE BRACKET
    case 0x005E:
      return 0x3E; // CIRCUMFLEX ACCENT
    case 0x005F:
      return 0x3F; // LOW LINE
    case 0x00E1:
      return 0x40; // LATIN SMALL LETTER A WITH ACUTE
    case 0x00F9:
      return 0x41; // LATIN SMALL LETTER U WITH GRAVE
    case 0x00D1:
      return 0x42; // LATIN CAPITAL LETTER N WITH TILDE
    case 0x00C9:
      return 0x43; // LATIN CAPITAL LETTER E WITH ACUTE
    case 0x00E7:
      return 0x44; // LATIN SMALL LETTER C WITH CEDILLA
    case 0x00F4:
      return 0x45; // LATIN SMALL LETTER O WITH CIRCUMFLEX
    case 0x00F2:
      return 0x46; // LATIN SMALL LETTER O WITH GRAVE
    case 0x00EC:
      return 0x47; // LATIN SMALL LETTER I WITH GRAVE
    case 0x00A3:
      return 0x48; // POUND SIGN
    case 0x00EF:
      return 0x49; // LATIN SMALL LETTER I WITH DIAERESIS
    case 0x00FC:
      return 0x4A; // LATIN SMALL LETTER U WITH DIAERESIS
    case 0x00E4:
      return 0x4B; // LATIN SMALL LETTER A WITH DIAERESIS
    case 0x00D6:
      return 0x4C; // LATIN CAPITAL LETTER O WITH DIAERESIS
    case 0x00FA:
      return 0x4D; // LATIN SMALL LETTER U WITH ACUTE
    case 0x00F3:
      return 0x4E; // LATIN SMALL LETTER O WITH ACUTE
    case 0x00F6:
      return 0x4F; // LATIN SMALL LETTER O WITH DIAERESIS
    case 0x00DC:
      return 0x50; // LATIN CAPITAL LETTER U WITH DIAERESIS
    case 0x00E2:
      return 0x51; // LATIN SMALL LETTER A WITH CIRCUMFLEX
    case 0x00FB:
      return 0x52; // LATIN SMALL LETTER U WITH CIRCUMFLEX
    case 0x00EE:
      return 0x53; // LATIN SMALL LETTER I WITH CIRCUMFLEX
    case 0x00E9:
      return 0x54; // LATIN SMALL LETTER E WITH ACUTE
    case 0x00E8:
      return 0x55; // LATIN SMALL LETTER E WITH GRAVE
    case 0x00F1:
      return 0x56; // LATIN SMALL LETTER N WITH TILDE
    case 0x00EA:
      return 0x57; // LATIN SMALL LETTER E WITH CIRCUMFLEX
    case 0x00E5:
      return 0x58; // LATIN SMALL LETTER A WITH RING ABOVE
    case 0x00E0:
      return 0x59; // LATIN SMALL LETTER A WITH GRAVE
    case 0x00C5:
      return 0x5A; // LATIN CAPITAL LETTER A WITH RING ABOVE
    case 0x241B:
      return 0x5B; // SYMBOL FOR ESCAPE
    case 0x2191:
      return 0x5C; // UPWARDS ARROW
    case 0x2193:
      return 0x5D; // DOWNWARDS ARROW
    case 0x2190:
      return 0x5E; // LEFTWARDS ARROW
    case 0x2192:
      return 0x5F; // RIGHTWARDS ARROW
    case 0x00A1:
      return 0x60; // INVERTED EXCLAMATION MARK
    case 0x0061:
      return 0x61; // LATIN SMALL LETTER A
    case 0x0062:
      return 0x62; // LATIN SMALL LETTER B
    case 0x0063:
      return 0x63; // LATIN SMALL LETTER C
    case 0x0064:
      return 0x64; // LATIN SMALL LETTER D
    case 0x0065:
      return 0x65; // LATIN SMALL LETTER E
    case 0x0066:
      return 0x66; // LATIN SMALL LETTER F
    case 0x0067:
      return 0x67; // LATIN SMALL LETTER G
    case 0x0068:
      return 0x68; // LATIN SMALL LETTER H
    case 0x0069:
      return 0x69; // LATIN SMALL LETTER I
    case 0x006A:
      return 0x6A; // LATIN SMALL LETTER J
    case 0x006B:
      return 0x6B; // LATIN SMALL LETTER K
    case 0x006C:
      return 0x6C; // LATIN SMALL LETTER L
    case 0x006D:
      return 0x6D; // LATIN SMALL LETTER M
    case 0x006E:
      return 0x6E; // LATIN SMALL LETTER N
    case 0x006F:
      return 0x6F; // LATIN SMALL LETTER O
    case 0x0070:
      return 0x70; // LATIN SMALL LETTER P
    case 0x0071:
      return 0x71; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0x72; // LATIN SMALL LETTER R
    case 0x0073:
      return 0x73; // LATIN SMALL LETTER S
    case 0x0074:
      return 0x74; // LATIN SMALL LETTER T
    case 0x0075:
      return 0x75; // LATIN SMALL LETTER U
    case 0x0076:
      return 0x76; // LATIN SMALL LETTER V
    case 0x0077:
      return 0x77; // LATIN SMALL LETTER W
    case 0x0078:
      return 0x78; // LATIN SMALL LETTER X
    case 0x0079:
      return 0x79; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0x7A; // LATIN SMALL LETTER Z
    case 0x00C4:
      return 0x7B; // LATIN CAPITAL LETTER A WITH DIAERESIS
    case 0x007C:
      return 0x7C; // VERTICAL LINE
    case 0x1F8B0:
      return 0x7D; // ARROW POINTING UPWARDS THEN NORTH WEST
    case 0x25C0:
      return 0x7E; // BLACK LEFT-POINTING TRIANGLE
    case 0x25B6:
      return 0x7F; // BLACK RIGHT-POINTING TRIANGLE
    }
  }
};

template <size_t N> struct AtasciiInternationalReverseVideoString {
  char Str[N]{};

  constexpr AtasciiInternationalReverseVideoString(char const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0x80)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }

  constexpr AtasciiInternationalReverseVideoString(char16_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I) {
      if (Src[I] >= 0xD800 && Src[I] <= 0xDFFF)
        throw "use U prefix for unicode string literals";
      Str[I] = TranslateUnicode(Src[I]);
    }
  }
  
  constexpr AtasciiInternationalReverseVideoString(char32_t const (&Src)[N]) {
    for (size_t I = 0; I < N; ++I)
      Str[I] = TranslateUnicode(Src[I]);
  }

  constexpr char TranslateUnicode(char32_t C) {
    switch (C) {
    default:
      throw "Unsupported";

    // Preserve NUL
    case 0x0000:
      return 0x00;

      // Name: Map from Atari 8-bit series (video) international character set
      // to Unicode

      // Date: 2018 August 16

      // Author: Rebecca Bettencourt <support@kreativekorp.com>

    case 0x0020:
      return 0x80; // SPACE
    case 0x0021:
      return 0x81; // EXCLAMATION MARK
    case 0x0022:
      return 0x82; // QUOTATION MARK
    case 0x0023:
      return 0x83; // NUMBER SIGN
    case 0x0024:
      return 0x84; // DOLLAR SIGN
    case 0x0025:
      return 0x85; // PERCENT SIGN
    case 0x0026:
      return 0x86; // AMPERSAND
    case 0x0027:
      return 0x87; // APOSTROPHE
    case 0x0028:
      return 0x88; // LEFT PARENTHESIS
    case 0x0029:
      return 0x89; // RIGHT PARENTHESIS
    case 0x002A:
      return 0x8A; // ASTERISK
    case 0x002B:
      return 0x8B; // PLUS SIGN
    case 0x002C:
      return 0x8C; // COMMA
    case 0x002D:
      return 0x8D; // HYPHEN-MINUS
    case 0x002E:
      return 0x8E; // FULL STOP
    case 0x002F:
      return 0x8F; // SOLIDUS
    case 0x0030:
      return 0x90; // DIGIT ZERO
    case 0x0031:
      return 0x91; // DIGIT ONE
    case 0x0032:
      return 0x92; // DIGIT TWO
    case 0x0033:
      return 0x93; // DIGIT THREE
    case 0x0034:
      return 0x94; // DIGIT FOUR
    case 0x0035:
      return 0x95; // DIGIT FIVE
    case 0x0036:
      return 0x96; // DIGIT SIX
    case 0x0037:
      return 0x97; // DIGIT SEVEN
    case 0x0038:
      return 0x98; // DIGIT EIGHT
    case 0x0039:
      return 0x99; // DIGIT NINE
    case 0x003A:
      return 0x9A; // COLON
    case 0x003B:
      return 0x9B; // SEMICOLON
    case 0x003C:
      return 0x9C; // LESS-THAN SIGN
    case 0x003D:
      return 0x9D; // EQUALS SIGN
    case 0x003E:
      return 0x9E; // GREATER-THAN SIGN
    case 0x003F:
      return 0x9F; // QUESTION MARK
    case 0x0040:
      return 0xA0; // COMMERCIAL AT
    case 0x0041:
      return 0xA1; // LATIN CAPITAL LETTER A
    case 0x0042:
      return 0xA2; // LATIN CAPITAL LETTER B
    case 0x0043:
      return 0xA3; // LATIN CAPITAL LETTER C
    case 0x0044:
      return 0xA4; // LATIN CAPITAL LETTER D
    case 0x0045:
      return 0xA5; // LATIN CAPITAL LETTER E
    case 0x0046:
      return 0xA6; // LATIN CAPITAL LETTER F
    case 0x0047:
      return 0xA7; // LATIN CAPITAL LETTER G
    case 0x0048:
      return 0xA8; // LATIN CAPITAL LETTER H
    case 0x0049:
      return 0xA9; // LATIN CAPITAL LETTER I
    case 0x004A:
      return 0xAA; // LATIN CAPITAL LETTER J
    case 0x004B:
      return 0xAB; // LATIN CAPITAL LETTER K
    case 0x004C:
      return 0xAC; // LATIN CAPITAL LETTER L
    case 0x004D:
      return 0xAD; // LATIN CAPITAL LETTER M
    case 0x004E:
      return 0xAE; // LATIN CAPITAL LETTER N
    case 0x004F:
      return 0xAF; // LATIN CAPITAL LETTER O
    case 0x0050:
      return 0xB0; // LATIN CAPITAL LETTER P
    case 0x0051:
      return 0xB1; // LATIN CAPITAL LETTER Q
    case 0x0052:
      return 0xB2; // LATIN CAPITAL LETTER R
    case 0x0053:
      return 0xB3; // LATIN CAPITAL LETTER S
    case 0x0054:
      return 0xB4; // LATIN CAPITAL LETTER T
    case 0x0055:
      return 0xB5; // LATIN CAPITAL LETTER U
    case 0x0056:
      return 0xB6; // LATIN CAPITAL LETTER V
    case 0x0057:
      return 0xB7; // LATIN CAPITAL LETTER W
    case 0x0058:
      return 0xB8; // LATIN CAPITAL LETTER X
    case 0x0059:
      return 0xB9; // LATIN CAPITAL LETTER Y
    case 0x005A:
      return 0xBA; // LATIN CAPITAL LETTER Z
    case 0x005B:
      return 0xBB; // LEFT SQUARE BRACKET
    case 0x005C:
      return 0xBC; // REVERSE SOLIDUS
    case 0x005D:
      return 0xBD; // RIGHT SQUARE BRACKET
    case 0x005E:
      return 0xBE; // CIRCUMFLEX ACCENT
    case 0x005F:
      return 0xBF; // LOW LINE
    case 0x00E1:
      return 0xC0; // LATIN SMALL LETTER A WITH ACUTE
    case 0x00F9:
      return 0xC1; // LATIN SMALL LETTER U WITH GRAVE
    case 0x00D1:
      return 0xC2; // LATIN CAPITAL LETTER N WITH TILDE
    case 0x00C9:
      return 0xC3; // LATIN CAPITAL LETTER E WITH ACUTE
    case 0x00E7:
      return 0xC4; // LATIN SMALL LETTER C WITH CEDILLA
    case 0x00F4:
      return 0xC5; // LATIN SMALL LETTER O WITH CIRCUMFLEX
    case 0x00F2:
      return 0xC6; // LATIN SMALL LETTER O WITH GRAVE
    case 0x00EC:
      return 0xC7; // LATIN SMALL LETTER I WITH GRAVE
    case 0x00A3:
      return 0xC8; // POUND SIGN
    case 0x00EF:
      return 0xC9; // LATIN SMALL LETTER I WITH DIAERESIS
    case 0x00FC:
      return 0xCA; // LATIN SMALL LETTER U WITH DIAERESIS
    case 0x00E4:
      return 0xCB; // LATIN SMALL LETTER A WITH DIAERESIS
    case 0x00D6:
      return 0xCC; // LATIN CAPITAL LETTER O WITH DIAERESIS
    case 0x00FA:
      return 0xCD; // LATIN SMALL LETTER U WITH ACUTE
    case 0x00F3:
      return 0xCE; // LATIN SMALL LETTER O WITH ACUTE
    case 0x00F6:
      return 0xCF; // LATIN SMALL LETTER O WITH DIAERESIS
    case 0x00DC:
      return 0xD0; // LATIN CAPITAL LETTER U WITH DIAERESIS
    case 0x00E2:
      return 0xD1; // LATIN SMALL LETTER A WITH CIRCUMFLEX
    case 0x00FB:
      return 0xD2; // LATIN SMALL LETTER U WITH CIRCUMFLEX
    case 0x00EE:
      return 0xD3; // LATIN SMALL LETTER I WITH CIRCUMFLEX
    case 0x00E9:
      return 0xD4; // LATIN SMALL LETTER E WITH ACUTE
    case 0x00E8:
      return 0xD5; // LATIN SMALL LETTER E WITH GRAVE
    case 0x00F1:
      return 0xD6; // LATIN SMALL LETTER N WITH TILDE
    case 0x00EA:
      return 0xD7; // LATIN SMALL LETTER E WITH CIRCUMFLEX
    case 0x00E5:
      return 0xD8; // LATIN SMALL LETTER A WITH RING ABOVE
    case 0x00E0:
      return 0xD9; // LATIN SMALL LETTER A WITH GRAVE
    case 0x00C5:
      return 0xDA; // LATIN CAPITAL LETTER A WITH RING ABOVE
    case 0x241B:
      return 0xDB; // SYMBOL FOR ESCAPE
    case 0x2191:
      return 0xDC; // UPWARDS ARROW
    case 0x2193:
      return 0xDD; // DOWNWARDS ARROW
    case 0x2190:
      return 0xDE; // LEFTWARDS ARROW
    case 0x2192:
      return 0xDF; // RIGHTWARDS ARROW
    case 0x00A1:
      return 0xE0; // INVERTED EXCLAMATION MARK
    case 0x0061:
      return 0xE1; // LATIN SMALL LETTER A
    case 0x0062:
      return 0xE2; // LATIN SMALL LETTER B
    case 0x0063:
      return 0xE3; // LATIN SMALL LETTER C
    case 0x0064:
      return 0xE4; // LATIN SMALL LETTER D
    case 0x0065:
      return 0xE5; // LATIN SMALL LETTER E
    case 0x0066:
      return 0xE6; // LATIN SMALL LETTER F
    case 0x0067:
      return 0xE7; // LATIN SMALL LETTER G
    case 0x0068:
      return 0xE8; // LATIN SMALL LETTER H
    case 0x0069:
      return 0xE9; // LATIN SMALL LETTER I
    case 0x006A:
      return 0xEA; // LATIN SMALL LETTER J
    case 0x006B:
      return 0xEB; // LATIN SMALL LETTER K
    case 0x006C:
      return 0xEC; // LATIN SMALL LETTER L
    case 0x006D:
      return 0xED; // LATIN SMALL LETTER M
    case 0x006E:
      return 0xEE; // LATIN SMALL LETTER N
    case 0x006F:
      return 0xEF; // LATIN SMALL LETTER O
    case 0x0070:
      return 0xF0; // LATIN SMALL LETTER P
    case 0x0071:
      return 0xF1; // LATIN SMALL LETTER Q
    case 0x0072:
      return 0xF2; // LATIN SMALL LETTER R
    case 0x0073:
      return 0xF3; // LATIN SMALL LETTER S
    case 0x0074:
      return 0xF4; // LATIN SMALL LETTER T
    case 0x0075:
      return 0xF5; // LATIN SMALL LETTER U
    case 0x0076:
      return 0xF6; // LATIN SMALL LETTER V
    case 0x0077:
      return 0xF7; // LATIN SMALL LETTER W
    case 0x0078:
      return 0xF8; // LATIN SMALL LETTER X
    case 0x0079:
      return 0xF9; // LATIN SMALL LETTER Y
    case 0x007A:
      return 0xFA; // LATIN SMALL LETTER Z
    case 0x00C4:
      return 0xFB; // LATIN CAPITAL LETTER A WITH DIAERESIS
    case 0x007C:
      return 0xFC; // VERTICAL LINE
    case 0x1F8B0:
      return 0xFD; // ARROW POINTING UPWARDS THEN NORTH WEST
    case 0x25C0:
      return 0xFE; // BLACK LEFT-POINTING TRIANGLE
    case 0x25B6:
      return 0xFF; // BLACK RIGHT-POINTING TRIANGLE
    }
  }
};

} // namespace charset_impl

template <charset_impl::AtasciiString S> constexpr auto operator""_a() {
  return S.Str;
}
template <charset_impl::AtasciiInternationalString S> constexpr auto operator""_i() {
  return S.Str;
}

template <charset_impl::AtasciiVideoString S> constexpr auto operator""_av() {
  return S.Str;
}

template <charset_impl::AtasciiReverseVideoString S>
constexpr auto operator""_arv() {
  return S.Str;
}

template <charset_impl::AtasciiInternationalVideoString S> constexpr auto operator""_iv() {
  return S.Str;
}

template <charset_impl::AtasciiInternationalReverseVideoString S>
constexpr auto operator""_irv() {
  return S.Str;
}

#endif // not _CHARSET_H
#endif // __cplusplus >= 202002L
