/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_MMAN_H
# define LIBC_SYS_MMAN_H


/* types */
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef int off_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif


/* constants */
# define PROT_READ	0x1
# define PROT_WRITE	0x2
# define PROT_EXEC	0x4
# define PROT_NONE	0x0

# define MAP_SHARED	0x1
# define MAP_PRIVATE	0x2
# define MAP_FIXED	0x10
# define MAP_ANONYMOUS	0x20
# define MAP_FAILED	((void*)-1)


/* functions */
void * mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);

#endif /* !LIBC_SYS_MMAN_H */
