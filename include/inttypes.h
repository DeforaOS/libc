/* $Id$ */
/* Copyright (c) 2005-2017 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef LIBC_INTTYPES_H
# define LIBC_INTTYPES_H

# include "stdint.h"


/* types */
# ifndef imaxdiv_t
#  define imaxdiv_t imaxdiv_t
typedef struct _imaxdiv_t
{
	intmax_t quot;
	intmax_t rem;
} imaxdiv_t;
# endif
# ifndef wchar_t
#  define wchar_t wchar_t
typedef __wchar_t wchar_t;
# endif


/* constants */
#ifdef __INTPTR_FMTd__
# define PRId8		__INT8_FMTd__
# define PRId16		__INT16_FMTd__
# define PRId32		__INT32_FMTd__
# define PRId64		__INT64_FMTd__
# define PRIdLEAST8	__INTLEAST8_FMTd__
# define PRIdLEAST16	__INTLEAST16_FMTd__
# define PRIdLEAST32	__INTLEAST32_FMTd__
# define PRIdLEAST64	__INTLEAST64_FMTd__
# define PRIdFAST8	__INTFAST8_FMTd__
# define PRIdFAST16	__INTFAST16_FMTd__
# define PRIdFAST32	__INTFAST32_FMTd__
# define PRIdFAST64	__INTFAST64_FMTd__
# define PRIdMAX	__INTMAX_FMTd__
# define PRIdPTR	__INTPTR_FMTd__

# define PRIi8		__INT8_FMTi__
# define PRIi16		__INT16_FMTi__
# define PRIi32		__INT32_FMTi__
# define PRIi64		__INT64_FMTi__
# define PRIiLEAST8	__INTLEAST8_FMTi__
# define PRIiLEAST16	__INTLEAST16_FMTi__
# define PRIiLEAST32	__INTLEAST32_FMTi__
# define PRIiLEAST64	__INTLEAST64_FMTi__
# define PRIiFAST8	__INTFAST8_FMTi__
# define PRIiFAST16	__INTFAST16_FMTi__
# define PRIiFAST32	__INTFAST32_FMTi__
# define PRIiFAST64	__INTFAST64_FMTi__
# define PRIiMAX	__INTMAX_FMTi__
# define PRIiPTR	__INTPTR_FMTi__

# define PRIo8		__UINT8_FMTo__
# define PRIo16		__UINT16_FMTo__
# define PRIo32		__UINT32_FMTo__
# define PRIo64		__UINT64_FMTo__
# define PRIoLEAST8	__UINTLEAST8_FMTo__
# define PRIoLEAST16	__UINTLEAST16_FMTo__
# define PRIoLEAST32	__UINTLEAST32_FMTo__
# define PRIoLEAST64	__UINTLEAST64_FMTo__
# define PRIoFAST8	__UINTFAST8_FMTo__
# define PRIoFAST16	__UINTFAST16_FMTo__
# define PRIoFAST32	__UINTFAST32_FMTo__
# define PRIoFAST64	__UINTFAST64_FMTo__
# define PRIoMAX	__UINTMAX_FMTo__
# define PRIoPTR	__UINTPTR_FMTo__

# define PRIu8		__UINT8_FMTu__
# define PRIu16		__UINT16_FMTu__
# define PRIu32		__UINT32_FMTu__
# define PRIu64		__UINT64_FMTu__
# define PRIuLEAST8	__UINTLEAST8_FMTu__
# define PRIuLEAST16	__UINTLEAST16_FMTu__
# define PRIuLEAST32	__UINTLEAST32_FMTu__
# define PRIuLEAST64	__UINTLEAST64_FMTu__
# define PRIuFAST8	__UINTFAST8_FMTu__
# define PRIuFAST16	__UINTFAST16_FMTu__
# define PRIuFAST32	__UINTFAST32_FMTu__
# define PRIuFAST64	__UINTFAST64_FMTu__
# define PRIuMAX	__UINTMAX_FMTu__
# define PRIuPTR	__UINTPTR_FMTu__

# define PRIx8		__UINT8_FMTx__
# define PRIx16		__UINT16_FMTx__
# define PRIx32		__UINT32_FMTx__
# define PRIx64		__UINT64_FMTx__
# define PRIxLEAST8	__UINTLEAST8_FMTx__
# define PRIxLEAST16	__UINTLEAST16_FMTx__
# define PRIxLEAST32	__UINTLEAST32_FMTx__
# define PRIxLEAST64	__UINTLEAST64_FMTx__
# define PRIxFAST8	__UINTFAST8_FMTx__
# define PRIxFAST16	__UINTFAST16_FMTx__
# define PRIxFAST32	__UINTFAST32_FMTx__
# define PRIxFAST64	__UINTFAST64_FMTx__
# define PRIxMAX	__UINTMAX_FMTx__
# define PRIxPTR	__UINTPTR_FMTx__

# define PRIX8		__UINT8_FMTX__
# define PRIX16		__UINT16_FMTX__
# define PRIX32		__UINT32_FMTX__
# define PRIX64		__UINT64_FMTX__
# define PRIXLEAST8	__UINTLEAST8_FMTX__
# define PRIXLEAST16	__UINTLEAST16_FMTX__
# define PRIXLEAST32	__UINTLEAST32_FMTX__
# define PRIXLEAST64	__UINTLEAST64_FMTX__
# define PRIXFAST8	__UINTFAST8_FMTX__
# define PRIXFAST16	__UINTFAST16_FMTX__
# define PRIXFAST32	__UINTFAST32_FMTX__
# define PRIXFAST64	__UINTFAST64_FMTX__
# define PRIXMAX	__UINTMAX_FMTX__
# define PRIXPTR	__UINTPTR_FMTX__

# define SCNd8		__INT8_FMTd__
# define SCNd16		__INT16_FMTd__
# define SCNd32		__INT32_FMTd__
# define SCNd64		__INT64_FMTd__
# define SCNdLEAST8	__INT_LEAST8_FMTd__
# define SCNdLEAST16	__INT_LEAST16_FMTd__
# define SCNdLEAST32	__INT_LEAST32_FMTd__
# define SCNdLEAST64	__INT_LEAST64_FMTd__
# define SCNdFAST8	__INT_FAST8_FMTd__
# define SCNdFAST16	__INT_FAST16_FMTd__
# define SCNdFAST32	__INT_FAST32_FMTd__
# define SCNdFAST64	__INT_FAST64_FMTd__
# define SCNdMAX	__INTMAX_FMTd__
# define SCNdPTR	__INTPTR_FMTd__

# define SCNi8		__INT8_FMTi__
# define SCNi16		__INT16_FMTi__
# define SCNi32		__INT32_FMTi__
# define SCNi64		__INT64_FMTi__
# define SCNiLEAST8	__INT_LEAST8_FMTi__
# define SCNiLEAST16	__INT_LEAST16_FMTi__
# define SCNiLEAST32	__INT_LEAST32_FMTi__
# define SCNiLEAST64	__INT_LEAST64_FMTi__
# define SCNiFAST8	__INT_FAST8_FMTi__
# define SCNiFAST16	__INT_FAST16_FMTi__
# define SCNiFAST32	__INT_FAST32_FMTi__
# define SCNiFAST64	__INT_FAST64_FMTi__
# define SCNiMAX	__INTMAX_FMTi__
# define SCNiPTR	__INTPTR_FMTi__

# define SCNo8		__UINT8_FMTo__
# define SCNo16		__UINT16_FMTo__
# define SCNo32		__UINT32_FMTo__
# define SCNo64		__UINT64_FMTo__
# define SCNoLEAST8	__UINT_LEAST8_FMTo__
# define SCNoLEAST16	__UINT_LEAST16_FMTo__
# define SCNoLEAST32	__UINT_LEAST32_FMTo__
# define SCNoLEAST64	__UINT_LEAST64_FMTo__
# define SCNoFAST8	__UINT_FAST8_FMTo__
# define SCNoFAST16	__UINT_FAST16_FMTo__
# define SCNoFAST32	__UINT_FAST32_FMTo__
# define SCNoFAST64	__UINT_FAST64_FMTo__
# define SCNoMAX	__UINTMAX_FMTo__
# define SCNoPTR	__UINTPTR_FMTo__

# define SCNu8		__UINT8_FMTu__
# define SCNu16		__UINT16_FMTu__
# define SCNu32		__UINT32_FMTu__
# define SCNu64		__UINT64_FMTu__
# define SCNuLEAST8	__UINT_LEAST8_FMTu__
# define SCNuLEAST16	__UINT_LEAST16_FMTu__
# define SCNuLEAST32	__UINT_LEAST32_FMTu__
# define SCNuLEAST64	__UINT_LEAST64_FMTu__
# define SCNuFAST8	__UINT_FAST8_FMTu__
# define SCNuFAST16	__UINT_FAST16_FMTu__
# define SCNuFAST32	__UINT_FAST32_FMTu__
# define SCNuFAST64	__UINT_FAST64_FMTu__
# define SCNuMAX	__UINTMAX_FMTu__
# define SCNuPTR	__UINTPTR_FMTu__

# define SCNx8		__UINT8_FMTx__
# define SCNx16		__UINT16_FMTx__
# define SCNx32		__UINT32_FMTx__
# define SCNx64		__UINT64_FMTx__
# define SCNxLEAST8	__UINT_LEAST8_FMTx__
# define SCNxLEAST16	__UINT_LEAST16_FMTx__
# define SCNxLEAST32	__UINT_LEAST32_FMTx__
# define SCNxLEAST64	__UINT_LEAST64_FMTx__
# define SCNxFAST8	__UINT_FAST8_FMTx__
# define SCNxFAST16	__UINT_FAST16_FMTx__
# define SCNxFAST32	__UINT_FAST32_FMTx__
# define SCNxFAST64	__UINT_FAST64_FMTx__
# define SCNxMAX	__UINTMAX_FMTx__
# define SCNxPTR	__UINTPTR_FMTx__

# define SCNX8		__UINT8_FMTX__
# define SCNX16		__UINT16_FMTX__
# define SCNX32		__UINT32_FMTX__
# define SCNX64		__UINT64_FMTX__
# define SCNXLEAST8	__UINT_LEAST8_FMTX__
# define SCNXLEAST16	__UINT_LEAST16_FMTX__
# define SCNXLEAST32	__UINT_LEAST32_FMTX__
# define SCNXLEAST64	__UINT_LEAST64_FMTX__
# define SCNXFAST8	__UINT_FAST8_FMTX__
# define SCNXFAST16	__UINT_FAST16_FMTX__
# define SCNXFAST32	__UINT_FAST32_FMTX__
# define SCNXFAST64	__UINT_FAST64_FMTX__
# define SCNXMAX	__UINTMAX_FMTX__
# define SCNXPTR	__UINTPTR_FMTX__
#elif defined(_LP64) && _LP64
# define PRId8		"d"
# define PRId16		"d"
# define PRId32		"d"
# define PRId64		"ld"
# define PRIdLEAST8	"d"
# define PRIdLEAST16	"d"
# define PRIdLEAST32	"d"
# define PRIdLEAST64	"ld"
# define PRIdFAST8	"d"
# define PRIdFAST16	"d"
# define PRIdFAST32	"d"
# define PRIdFAST64	"ld"
# define PRIdMAX	"ld"
# define PRIdPTR	"ld"

# define PRIi8		"i"
# define PRIi16		"i"
# define PRIi32		"i"
# define PRIi64		"li"
# define PRIiLEAST8	"i"
# define PRIiLEAST16	"i"
# define PRIiLEAST32	"i"
# define PRIiLEAST64	"li"
# define PRIiFAST8	"i"
# define PRIiFAST16	"i"
# define PRIiFAST32	"i"
# define PRIiFAST64	"li"
# define PRIiMAX	"li"
# define PRIiPTR	"li"

# define PRIo8		"o"
# define PRIo16		"o"
# define PRIo32		"o"
# define PRIo64		"lo"
# define PRIoLEAST8	"o"
# define PRIoLEAST16	"o"
# define PRIoLEAST32	"o"
# define PRIoLEAST64	"lo"
# define PRIoFAST8	"o"
# define PRIoFAST16	"o"
# define PRIoFAST32	"o"
# define PRIoFAST64	"lo"
# define PRIoMAX	"lo"
# define PRIoPTR	"lo"

# define PRIu8		"u"
# define PRIu16		"u"
# define PRIu32		"u"
# define PRIu64		"lu"
# define PRIuLEAST8	"u"
# define PRIuLEAST16	"u"
# define PRIuLEAST32	"u"
# define PRIuLEAST64	"lu"
# define PRIuFAST8	"u"
# define PRIuFAST16	"u"
# define PRIuFAST32	"u"
# define PRIuFAST64	"lu"
# define PRIuMAX	"lu"
# define PRIuPTR	"lu"

# define PRIx8		"x"
# define PRIx16		"x"
# define PRIx32		"x"
# define PRIx64		"lx"
# define PRIxLEAST8	"x"
# define PRIxLEAST16	"x"
# define PRIxLEAST32	"x"
# define PRIxLEAST64	"lx"
# define PRIxFAST8	"x"
# define PRIxFAST16	"x"
# define PRIxFAST32	"x"
# define PRIxFAST64	"lx"
# define PRIxMAX	"lx"
# define PRIxPTR	"lx"

# define PRIX8		"X"
# define PRIX16		"X"
# define PRIX32		"X"
# define PRIX64		"lX"
# define PRIXLEAST8	"X"
# define PRIXLEAST16	"X"
# define PRIXLEAST32	"X"
# define PRIXLEAST64	"lX"
# define PRIXFAST8	"X"
# define PRIXFAST16	"X"
# define PRIXFAST32	"X"
# define PRIXFAST64	"lX"
# define PRIXMAX	"lX"
# define PRIXPTR	"lX"

# define SCNd8		"hhd"
# define SCNd16		"hd"
# define SCNd32		"d"
# define SCNd64		"ld"
# define SCNdLEAST8	"hhd"
# define SCNdLEAST16	"hd"
# define SCNdLEAST32	"d"
# define SCNdLEAST64	"ld"
# define SCNdFAST8	"d"
# define SCNdFAST16	"d"
# define SCNdFAST32	"d"
# define SCNdFAST64	"ld"
# define SCNdMAX	"ld"
# define SCNdPTR	"ld"

# define SCNi8		"hhi"
# define SCNi16		"hi"
# define SCNi32		"i"
# define SCNi64		"li"
# define SCNiLEAST8	"hhi"
# define SCNiLEAST16	"hi"
# define SCNiLEAST32	"i"
# define SCNiLEAST64	"li"
# define SCNiFAST8	"i"
# define SCNiFAST16	"i"
# define SCNiFAST32	"i"
# define SCNiFAST64	"li"
# define SCNiMAX	"li"
# define SCNiPTR	"li"

# define SCNo8		"hho"
# define SCNo16		"ho"
# define SCNo32		"o"
# define SCNo64		"lo"
# define SCNoLEAST8	"hho"
# define SCNoLEAST16	"ho"
# define SCNoLEAST32	"o"
# define SCNoLEAST64	"lo"
# define SCNoFAST8	"o"
# define SCNoFAST16	"o"
# define SCNoFAST32	"o"
# define SCNoFAST64	"lo"
# define SCNoMAX	"lo"
# define SCNoPTR	"lo"

# define SCNu8		"hhu"
# define SCNu16		"hu"
# define SCNu32		"u"
# define SCNu64		"lu"
# define SCNuLEAST8	"hhu"
# define SCNuLEAST16	"hu"
# define SCNuLEAST32	"u"
# define SCNuLEAST64	"lu"
# define SCNuFAST8	"u"
# define SCNuFAST16	"u"
# define SCNuFAST32	"u"
# define SCNuFAST64	"lu"
# define SCNuMAX	"lu"
# define SCNuPTR	"lu"

# define SCNx8		"hhx"
# define SCNx16		"hx"
# define SCNx32		"x"
# define SCNx64		"lx"
# define SCNxLEAST8	"hhx"
# define SCNxLEAST16	"hx"
# define SCNxLEAST32	"x"
# define SCNxLEAST64	"lx"
# define SCNxFAST8	"x"
# define SCNxFAST16	"x"
# define SCNxFAST32	"x"
# define SCNxFAST64	"lx"
# define SCNxMAX	"lx"
# define SCNxPTR	"lx"

# define SCNX8		"hhX"
# define SCNX16		"hX"
# define SCNX32		"X"
# define SCNX64		"lX"
# define SCNXLEAST8	"hhX"
# define SCNXLEAST16	"hX"
# define SCNXLEAST32	"X"
# define SCNXLEAST64	"lX"
# define SCNXFAST8	"X"
# define SCNXFAST16	"X"
# define SCNXFAST32	"X"
# define SCNXFAST64	"lX"
# define SCNXMAX	"lX"
# define SCNXPTR	"lX"
#else /* !_LP64 */
# define PRId8		"d"
# define PRId16		"d"
# define PRId32		"d"
# define PRId64		"lld"
# define PRIdLEAST8	"d"
# define PRIdLEAST16	"d"
# define PRIdLEAST32	"d"
# define PRIdLEAST64	"lld"
# define PRIdFAST8	"d"
# define PRIdFAST16	"d"
# define PRIdFAST32	"d"
# define PRIdFAST64	"lld"
# define PRIdMAX	"lld"
# define PRIdPTR	"d"

# define PRIi8		"i"
# define PRIi16		"i"
# define PRIi32		"i"
# define PRIi64		"lli"
# define PRIiLEAST8	"i"
# define PRIiLEAST16	"i"
# define PRIiLEAST32	"i"
# define PRIiLEAST64	"lli"
# define PRIiFAST8	"i"
# define PRIiFAST16	"i"
# define PRIiFAST32	"i"
# define PRIiFAST64	"lli"
# define PRIiMAX	"lli"
# define PRIiPTR	"i"

# define PRIo8		"o"
# define PRIo16		"o"
# define PRIo32		"o"
# define PRIo64		"llo"
# define PRIoLEAST8	"o"
# define PRIoLEAST16	"o"
# define PRIoLEAST32	"o"
# define PRIoLEAST64	"llo"
# define PRIoFAST8	"o"
# define PRIoFAST16	"o"
# define PRIoFAST32	"o"
# define PRIoFAST64	"llo"
# define PRIoMAX	"llo"
# define PRIoPTR	"o"

# define PRIu8		"u"
# define PRIu16		"u"
# define PRIu32		"u"
# define PRIu64		"llu"
# define PRIuLEAST8	"u"
# define PRIuLEAST16	"u"
# define PRIuLEAST32	"u"
# define PRIuLEAST64	"llu"
# define PRIuFAST8	"u"
# define PRIuFAST16	"u"
# define PRIuFAST32	"u"
# define PRIuFAST64	"llu"
# define PRIuMAX	"llu"
# define PRIuPTR	"u"

# define PRIx8		"x"
# define PRIx16		"x"
# define PRIx32		"x"
# define PRIx64		"llx"
# define PRIxLEAST8	"x"
# define PRIxLEAST16	"x"
# define PRIxLEAST32	"x"
# define PRIxLEAST64	"llx"
# define PRIxFAST8	"x"
# define PRIxFAST16	"x"
# define PRIxFAST32	"x"
# define PRIxFAST64	"llx"
# define PRIxMAX	"llx"
# define PRIxPTR	"x"

# define PRIX8		"X"
# define PRIX16		"X"
# define PRIX32		"X"
# define PRIX64		"llX"
# define PRIXLEAST8	"X"
# define PRIXLEAST16	"X"
# define PRIXLEAST32	"X"
# define PRIXLEAST64	"llX"
# define PRIXFAST8	"X"
# define PRIXFAST16	"X"
# define PRIXFAST32	"X"
# define PRIXFAST64	"llX"
# define PRIXMAX	"llX"
# define PRIXPTR	"X"

# define SCNd8		"hhd"
# define SCNd16		"hd"
# define SCNd32		"d"
# define SCNd64		"lld"
# define SCNdLEAST8	"hhd"
# define SCNdLEAST16	"hd"
# define SCNdLEAST32	"d"
# define SCNdLEAST64	"lld"
# define SCNdFAST8	"d"
# define SCNdFAST16	"d"
# define SCNdFAST32	"d"
# define SCNdFAST64	"lld"
# define SCNdMAX	"lld"
# define SCNdPTR	"ld"

# define SCNi8		"hhi"
# define SCNi16		"hi"
# define SCNi32		"i"
# define SCNi64		"lli"
# define SCNiLEAST8	"hhi"
# define SCNiLEAST16	"hi"
# define SCNiLEAST32	"i"
# define SCNiLEAST64	"lli"
# define SCNiFAST8	"i"
# define SCNiFAST16	"i"
# define SCNiFAST32	"i"
# define SCNiFAST64	"lli"
# define SCNiMAX	"lli"
# define SCNiPTR	"li"

# define SCNo8		"hho"
# define SCNo16		"ho"
# define SCNo32		"o"
# define SCNo64		"llo"
# define SCNoLEAST8	"hho"
# define SCNoLEAST16	"ho"
# define SCNoLEAST32	"o"
# define SCNoLEAST64	"llo"
# define SCNoFAST8	"o"
# define SCNoFAST16	"o"
# define SCNoFAST32	"o"
# define SCNoFAST64	"llo"
# define SCNoMAX	"llo"
# define SCNoPTR	"lo"

# define SCNu8		"hhu"
# define SCNu16		"hu"
# define SCNu32		"u"
# define SCNu64		"llu"
# define SCNuLEAST8	"hhu"
# define SCNuLEAST16	"hu"
# define SCNuLEAST32	"u"
# define SCNuLEAST64	"llu"
# define SCNuFAST8	"u"
# define SCNuFAST16	"u"
# define SCNuFAST32	"u"
# define SCNuFAST64	"llu"
# define SCNuMAX	"llu"
# define SCNuPTR	"lu"

# define SCNx8		"hhx"
# define SCNx16		"hx"
# define SCNx32		"x"
# define SCNx64		"llx"
# define SCNxLEAST8	"hhx"
# define SCNxLEAST16	"hx"
# define SCNxLEAST32	"x"
# define SCNxLEAST64	"llx"
# define SCNxFAST8	"x"
# define SCNxFAST16	"x"
# define SCNxFAST32	"x"
# define SCNxFAST64	"llx"
# define SCNxMAX	"llx"
# define SCNxPTR	"lx"

# define SCNX8		"hhX"
# define SCNX16		"hX"
# define SCNX32		"X"
# define SCNX64		"llX"
# define SCNXLEAST8	"hhX"
# define SCNXLEAST16	"hX"
# define SCNXLEAST32	"X"
# define SCNXLEAST64	"llX"
# define SCNXFAST8	"X"
# define SCNXFAST16	"X"
# define SCNXFAST32	"X"
# define SCNXFAST64	"llX"
# define SCNXMAX	"llX"
# define SCNXPTR	"lX"
#endif


/* functions */
intmax_t imaxabs(intmax_t);
imaxdiv_t imaxdiv(intmax_t, intmax_t);
intmax_t strtoimax(const char *, char **, int);
uintmax_t strtoumax(const char *, char **, int);
intmax_t wcstoimax(const wchar_t *, wchar_t **, int);
uintmax_t wcstoumax(const wchar_t *, wchar_t **, int);

#endif /* !LIBC_INTTYPES_H */
