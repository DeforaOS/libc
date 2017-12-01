/* $Id$ */
/* Copyright (c) 2008-2017 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_FLOAT_H
# define LIBC_FLOAT_H


/* constants */
# ifdef __DBL_MAX__
#  define DBL_MAX		__DBL_MAX__
# endif
# ifdef __DBL_MAX_10_EXP__
#  define DBL_MAX_10_EXP	__DBL_MAX_10_EXP__
# endif
# ifdef __DBL_MAX_EXP__
#  define DBL_MAX_EXP		__DBL_MAX_EXP__
# endif
# ifdef __DBL_MIN__
#  define DBL_MIN		__DBL_MIN__
# endif
# ifdef __DBL_MIN_10_EXP__
#  define DBL_MIN_10_EXP	__DBL_MIN_10_EXP__
# endif
# ifdef __DBL_MIN_EXP__
#  define DBL_MIN_EXP		__DBL_MIN_EXP__
# endif

# ifdef __FLT_EVAL_METHOD__
#  define FLT_EVAL_METHOD	__FLT_EVAL_METHOD__
# else
#  define FLT_EVAL_METHOD	-1
# endif
# ifdef __FLT_RADIX__
#  define FLT_RADIX		__FLT_RADIX__
# endif
# ifdef __FLT_ROUNDS__
#  define FLT_ROUNDS		__FLT_ROUNDS__
# else
#  define FLT_ROUNDS		-1
# endif

# ifdef __FLT_MAX__
#  define FLT_MAX		__FLT_MAX__
# endif
# ifdef __FLT_MAX_10_EXP__
#  define FLT_MAX_10_EXP	__FLT_MAX_10_EXP__
# endif
# ifdef __FLT_MAX_EXP__
#  define FLT_MAX_EXP		__FLT_MAX_EXP__
# endif
# ifdef __FLT_MIN__
#  define FLT_MIN		__FLT_MIN__
# endif
# ifdef __FLT_MIN_10_EXP__
#  define FLT_MIN_10_EXP	__FLT_MIN_10_EXP__
# endif
# ifdef __FLT_MIN_EXP__
#  define FLT_MIN_EXP		__FLT_MIN_EXP__
# endif

# ifdef __LDBL_MAX__
#  define LDBL_MAX		__LDBL_MAX__
# endif
# ifdef __LDBL_MAX_10_EXP__
#  define LDBL_MAX_10_EXP	__LDBL_MAX_10_EXP__
# endif
# ifdef __LDBL_MAX_EXP__
#  define LDBL_MAX_EXP		__LDBL_MAX_EXP__
# endif
# ifdef __LDBL_MIN__
#  define LDBL_MIN		__LDBL_MIN__
# endif
# ifdef __LDBL_MIN_10_EXP__
#  define LDBL_MIN_10_EXP	__LDBL_MIN_10_EXP__
# endif
# ifdef __LDBL_MIN_EXP__
#  define LDBL_MIN_EXP		__LDBL_MIN_EXP__
# endif

#endif /* !LIBC_FLOAT_H */
