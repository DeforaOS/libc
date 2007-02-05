/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_MMAN_H
# define LIBC_SYS_MMAN_H

# include "compat/sys/mman.h"


/* types */
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif


/* constants */
# define MAP_FAILED	((void*)-1)


/* functions */
void * mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);

#endif /* !LIBC_SYS_MMAN_H */
