/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_SOLARIS_SYS_TYPES_H
# define LIBC_KERNEL_SOLARIS_SYS_TYPES_H


/* types */
# ifndef blkcnt_t
#  define blkcnt_t blkcnt_t
typedef unsigned long blkcnt_t;
# endif
# ifndef dev_t
#  define dev_t dev_t
typedef long dev_t;
# endif
# ifndef fsblkcnt_t
#  define fsblkcnt_t fsblkcnt_t
typedef unsigned long fsblkcnt_t;
# endif
# ifndef fsfilcnt_t
#  define fsfilcnt_t fsfilcnt_t
typedef unsigned long fsfilcnt_t;
# endif
# ifndef ino_t
#  define ino_t
typedef long ino_t;
#endif
# ifndef off_t
#  define off_t off_t
typedef long off_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef unsigned long time_t;
# endif

#endif /* !LIBC_KERNEL_SOLARIS_SYS_TYPES_H */
