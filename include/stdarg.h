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
# ifdef __i386__
#  define va_start(ap, arg) (ap) = ((char*)&arg) + 4
#  define va_arg(ap, type) ((ap) += sizeof(type), \
		*(type*)((void*)ap - sizeof(type)))
#  define va_end(ap)
# else /* !__i386__ */
#  warning Unsupported architecture
#  define va_start(ap, arg)
#  define va_arg(ap, type) (type)(ap)
#  define va_end(ap)
# endif

#endif /* !LIBC_STDARG_H */
