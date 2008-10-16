/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



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
# ifndef key_t
#  define key_t key_t
typedef long key_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef unsigned int mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef unsigned int nlink_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
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
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
# endif

#endif /* !LIBC_SYS_TYPES_H */
