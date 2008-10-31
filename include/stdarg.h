/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_STDARG_H
# define LIBC_STDARG_H


/* types */
# ifndef va_list
#  if defined(__i386__)
#   define va_list va_list
typedef void * va_list;
#  elif defined(__amd64__) \
	|| defined(__arm__) \
	|| defined(__mips__) \
	|| defined(__sparc__) \
	|| defined(__sparc64__)	/* XXX compiler dependent */
#   define va_list		__builtin_va_list
#  else
#   warning Unsupported architecture
#   define va_list va_list
typedef void * va_list;
#  endif
# endif


/* macros */
# if defined(__i386__)
#  define va_start(ap, arg)	(ap) = ((char*)&arg) + 4
#  define va_arg(ap, type)	((ap) += sizeof(type), \
		*(type*)((void*)(ap) - sizeof(type)))
#  define va_copy(copy, arg)	(copy) = (arg)	/* FIXME not tested */
#  define va_end(ap)
# elif defined(__amd64__)	/* XXX compiler dependent */ \
	|| defined(__arm__) \
	|| defined(__mips__) \
	|| defined(__sparc__) \
	|| defined(__sparc64__)
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
