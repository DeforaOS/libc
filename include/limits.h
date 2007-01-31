/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_LIMITS_H
# define LIBC_LIMITS_H


/* constants */
/* runtime invariant values */
# ifndef PAGESIZE
#  define PAGESIZE 4096 /* XXX OS and architecture dependent */
# endif
# ifndef PAGE_SIZE
#  define PAGE_SIZE PAGE_SIZE
# endif

/* pathname variable values */
# ifndef NAME_MAX
#  define NAME_MAX 256 /* XXX OS dependent */
# endif
# ifndef PATH_MAX
#  define PATH_MAX 1024 /* XXX OS dependent */
# endif

/* numerical */
/* FIXME architecture dependent */
# ifndef INT_MAX
#  define INT_MAX 0x7fffffff
# endif
# ifndef LONG_MAX
#  define LONG_MAX 0x7fffffff
# endif
# ifndef LONG_MIN
#  define LONG_MIN (-0x7fffffff-1)
# endif

#endif /* !LIBC_LIMITS_H */
