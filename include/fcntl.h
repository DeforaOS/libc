/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_FCNTL_H
# define LIBC_FCNTL_H

# include "compat/fcntl.h"


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif


/* functions */
int creat(const char *, mode_t);
int fcntl(int, int, ...);
int open(char const * filename, int flags, ...);

#endif /* !LIBC_FCNTL_H */
