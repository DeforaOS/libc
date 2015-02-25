/* $Id$ */
/* Copyright (c) 2005-2013 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_STDARG_H
# define LIBC_STDARG_H


/* types */
# ifndef va_list
#  if defined(__amd64__) \
	|| defined(__arm__) \
	|| defined(__mips__) \
	|| defined(__sparc__) \
	|| defined(__sparc64__)	/* XXX compiler dependent */
#   define va_list __builtin_va_list
#  else
#   warning Unsupported architecture: va_list is not supported
#   define va_list va_list
typedef char * va_list;
#  endif
# endif


/* macros */
# if defined(__amd64__) \
	|| defined(__arm__) \
	|| defined(__mips__) \
	|| defined(__sparc__) \
	|| defined(__sparc64__)	/* XXX compiler dependent */
#  define va_start(ap, arg)	__builtin_va_start((ap), (arg))
#  define va_arg		__builtin_va_arg
#  define va_copy		__builtin_va_copy
#  define va_end(ap)		__builtin_va_end((ap))
# else
/* FIXME works only in particular cases */
#  define va_start(ap, arg)	((ap) = ((va_list)&(arg)) \
		+ ((sizeof(long) > sizeof(arg)) ? sizeof(long) : sizeof(arg)))
#  define va_arg(ap, type)	*(type *)(ap), \
	((ap) += ((sizeof(long) > sizeof(type)) ? sizeof(long) : sizeof(type)))
#  define va_copy(copy, arg)	((copy) = (arg))
#  define va_end(ap)
# endif

#endif /* !LIBC_STDARG_H */
