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



#ifndef LIBC_KERNEL_LINUX_FCNTL_H
# define LIBC_KERNEL_LINUX_FCNTL_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif


/* constants */
# define F_DUPFD	0
# define F_GETFD	1
# define F_SETFD	2
# define F_GETFL	3
# define F_SETFL	4
# define F_GETLK	5	/* XXX 12 for 64 bits */
# define F_SETLK	6	/* XXX 13 for 64 bits */
# define F_SETLKW	7	/* XXX 14 for 64 bits */
# define F_SETOWN	8
# define F_GETOWN	9

# define FD_CLOEXEC	1

# define O_CREAT	00001
# define O_EXCL		00002
# define O_NOCTTY	00004
# define O_TRUNC	01000

# define O_APPEND	002000
# define O_NONBLOCK	004000
# define O_SYNC		010000
# define O_DSYNC	O_SYNC
# define O_RSYNC	O_SYNC

# define O_RDONLY	0
# define O_WRONLY	1
# define O_RDWR		2

# define O_ACCMODE	(O_WRONLY | O_RDWR)

#endif /* !LIBC_KERNEL_LINUX_FCNTL_H */
