/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_SOLARIS_TIME_H
# define LIBC_KERNEL_SOLARIS_TIME_H


/* types */
# ifndef clock_t
#  define clock_t clock_t
typedef unsigned long clock_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef unsigned long time_t;
# endif

#endif /* !LIBC_KERNEL_SOLARIS_TIME_H */
