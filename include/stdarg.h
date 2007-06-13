/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_STDARG_H
# define LIBC_STDARG_H


/* types */
# ifndef va_list
#  define va_list va_list
typedef void * va_list;
# endif


/* macros */
# if defined(__i386__)
#  define va_start(ap, arg)	(ap) = ((char*)&arg) + 4
#  define va_arg(ap, type)	((ap) += sizeof(type), \
		*(type*)((void*)ap - sizeof(type)))
#  define va_end(ap)
# elif defined(__sparc64__) \
	|| defined(__sparc__)	/* XXX compiler dependent */
#  define va_start(ap, arg)	__builtin_va_start(ap, arg)
#  define va_arg(ap, type)	__builtin_va_arg(ap, type)
#  define va_end(ap)		__builtin_va_end(ap)
# else /* !__i386__ */
#  warning Unsupported architecture
#  define va_start(ap, arg)
#  define va_arg(ap, type) (type)(ap)
#  define va_end(ap)
# endif

#endif /* !LIBC_STDARG_H */
