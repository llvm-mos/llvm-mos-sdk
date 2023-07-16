#ifndef _INTTYPES_H_
#define _INTTYPES_H_

#include <stddef.h>
#include <stdint.h>

#define PRId8 "hhd"
#define PRIdLEAST8 PRId8
#define PRIdFAST8 PRId8
#define PRId16 "d"
#define PRIdLEAST16 PRId16
#define PRIdFAST16 PRId16
#define PRId32 "ld"
#define PRIdLEAST32 PRId32
#define PRIdFAST32 PRId32
#define PRId64 "lld"
#define PRIdLEAST64 PRId64
#define PRIdFAST64 PRId64
#define PRIdMAX PRId64
#define PRIdPTR PRId16

#define PRIi8 "hhi"
#define PRIiLEAST8 PRIi8
#define PRIiFAST8 PRIi8
#define PRIi16 "i"
#define PRIiLEAST16 PRIi16
#define PRIiFAST16 PRIi16
#define PRIi32 "li"
#define PRIiLEAST32 PRIi32
#define PRIiFAST32 PRIi32
#define PRIi64 "lli"
#define PRIiLEAST64 PRIi64
#define PRIiFAST64 PRIi64
#define PRIiMAX PRIi64
#define PRIiPTR PRIi16

#define PRIo8 "hho"
#define PRIoLEAST8 PRIo8
#define PRIoFAST8 PRIo8
#define PRIo16 "o"
#define PRIoLEAST16 PRIo16
#define PRIoFAST16 PRIo16
#define PRIo32 "lo"
#define PRIoLEAST32 PRIo32
#define PRIoFAST32 PRIo32
#define PRIo64 "llo"
#define PRIoLEAST64 PRIo64
#define PRIoFAST64 PRIo64
#define PRIoMAX PRIo64
#define PRIoPTR PRIo16

#define PRIu8 "hhu"
#define PRIuLEAST8 PRIu8
#define PRIuFAST8 PRIu8
#define PRIu16 "u"
#define PRIuLEAST16 PRIu16
#define PRIuFAST16 PRIu16
#define PRIu32 "lu"
#define PRIuLEAST32 PRIu32
#define PRIuFAST32 PRIu32
#define PRIu64 "llu"
#define PRIuLEAST64 PRIu64
#define PRIuFAST64 PRIu64
#define PRIuMAX PRIu64
#define PRIuPTR PRIu16

#define PRIx8 "hhx"
#define PRIxLEAST8 PRIx8
#define PRIxFAST8 PRIx8
#define PRIx16 "x"
#define PRIxLEAST16 PRIx16
#define PRIxFAST16 PRIx16
#define PRIx32 "lx"
#define PRIxLEAST32 PRIx32
#define PRIxFAST32 PRIx32
#define PRIx64 "llx"
#define PRIxLEAST64 PRIx64
#define PRIxFAST64 PRIx64
#define PRIxMAX PRIx64
#define PRIxPTR PRIx16

#define PRIX8 "hhX"
#define PRIXLEAST8 PRIX8
#define PRIXFAST8 PRIX8
#define PRIX16 "X"
#define PRIXLEAST16 PRIX16
#define PRIXFAST16 PRIX16
#define PRIX32 "lX"
#define PRIXLEAST32 PRIX32
#define PRIXFAST32 PRIX32
#define PRIX64 "llX"
#define PRIXLEAST64 PRIX64
#define PRIXFAST64 PRIX64
#define PRIXMAX PRIX64
#define PRIXPTR PRIX16

#endif // not _INTTYPES_H_
