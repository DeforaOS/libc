/* $Id$ */
/* Copyright (c) 2005-2010 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_STDINT_H
# define LIBC_STDINT_H


/* types */
typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
# ifndef uint16_t
#  define uint16_t uint16_t
typedef unsigned short uint16_t;
# endif
# ifndef uint32_t
#  define uint32_t uint32_t
typedef unsigned int uint32_t;
# endif
typedef unsigned long long uint64_t;

# ifndef intmax_t
#  define intmax_t intmax_t
typedef long intmax_t;
# endif
# ifndef intptr_t
#  define intptr_t intptr_t
typedef signed long intptr_t;
# endif
# ifndef uintmax_t
#  define uintmax_t uintmax_t
typedef unsigned long uintmax_t;
# endif
# ifndef uintptr_t
#  define uintptr_t uintptr_t
typedef unsigned long uintptr_t;
# endif

#endif /* !LIBC_STDINT_H */
