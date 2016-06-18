/* $Id$ */
/* Copyright (c) 2016 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_COMPAT_H
# define LIBC_COMPAT_H


/* types */
# ifndef __intptr_t
#  ifdef __INTPTR_TYPE__
#   define __intptr_t __INTPTR_TYPE__
#  else
#   define __intptr_t __intptr_t
typedef signed long __intptr_t;
#  endif
# endif
# ifndef __size_t
#  ifdef __SIZE_TYPE__
#   define __size_t __SIZE_TYPE__
#  else
#   define __size_t __size_t
typedef unsigned long __size_t;
#  endif
# endif
# ifndef __ssize_t
#  ifdef __SSIZE_TYPE__
#   define __ssize_t __SSIZE_TYPE__
#  else
#   define __ssize_t __ssize_t
typedef long __ssize_t;
#  endif
# endif
# ifndef __ptrdiff_t
#  ifdef __PTRDIFF_TYPE__
#   define __ptrdiff_t __PTRDIFF_TYPE__
#  else
#   define __ptrdiff_t __ptrdiff_t
typedef long __ptrdiff_t;
#  endif
# endif
# ifndef __uintptr_t
#  ifdef __UINTPTR_TYPE__
#   define __uintptr_t __UINTPTR_TYPE__
#  else
#   define __uintptr_t __uintptr_t
typedef unsigned long __uintptr_t;
#  endif
# endif
# ifndef __wchar_t
#  ifdef __WCHAR_TYPE__
#   define __wchar_t __WCHAR_TYPE__
#  else
#   define __wchar_t __wchar_t
typedef char __wchar_t;
#  endif
# endif
# ifndef __wint_t
#  ifdef __WINT_TYPE__
#   define __wint_t __WINT_TYPE__
#  else
#   define __wint_t __wint_t
typedef int __wint_t;
#  endif
# endif

#endif /* !LIBC_COMPAT_H */
