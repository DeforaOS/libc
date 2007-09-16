/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#ifndef LIBC_STDARG_H
# define LIBC_STDARG_H


/* macros */
# if defined(__i386__)
#  ifndef va_list
#   define va_list va_list
typedef void * va_list;
#  endif
#  define va_start(ap, arg)	(ap) = ((char*)&arg) + 4
#  define va_arg(ap, type)	((ap) += sizeof(type), \
		*(type*)((void*)ap - sizeof(type)))
#  define va_copy(copy, arg)	(copy) = (arg)	/* FIXME not tested */
#  define va_end(ap)
# elif defined(__amd64__) \
	|| defined(__arm__) \
	|| defined(__mips__) \
	|| defined(__sparc__) \
	|| defined(__sparc64__)	/* XXX compiler dependent */
#  define va_start(ap, arg)	__builtin_va_start((ap), (arg))
#  define va_arg		__builtin_va_arg
#  define va_copy		__builtin_va_copy
#  define va_end(ap)		__builtin_va_end(ap)
# else /* !__i386__ */
#  warning Unsupported architecture
#  define va_start(ap, arg)
#  define va_arg(ap, type) (type)(ap)
#  define va_copy(dest, src)
#  define va_end(ap)
# endif

#endif /* !LIBC_STDARG_H */
