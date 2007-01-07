/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_LIMITS_H
# define LIBC_LIMITS_H


/* constants */
# ifndef NAME_MAX
#  define NAME_MAX 256
# endif

/* numerical */
/* FIXME architecture dependent */
# ifndef LONG_MAX
#  define LONG_MAX 0x7fffffff
# endif
# ifndef LONG_MIN
#  define LONG_MIN (-0x7fffffff-1)
# endif

#endif /* !LIBC_LIMITS_H */
