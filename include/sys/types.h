/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_TYPES_H
# define LIBC_SYS_TYPES_H

# include "compat/sys/types.h"


/* types */
# ifndef blksize_t
#  define blksize_t blksize_t
typedef unsigned int blksize_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned int ino_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef unsigned int mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef unsigned int nlink_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif
# ifndef ssize_t
#  define ssize_t ssize_t
typedef signed long ssize_t;
# endif

# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
# endif

#endif /* !LIBC_SYS_TYPES_H */
