/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_NETBSD_FCNTL_H
# define LIBC_KERNEL_NETBSD_FCNTL_H


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
# define F_GETOWN	5
# define F_SETOWN	6
# define F_GETLK	7
# define F_SETLK	8
# define F_SETLKW	9

# define FD_CLOEXEC	1

# define O_CREAT	0x0200
# define O_EXCL		0x0800
# define O_NOCTTY	0x8000
# define O_TRUNC	0x0400

# define O_NONBLOCK	0x00004
# define O_APPEND	0x00008
# define O_SYNC		0x00080
# define O_DSYNC	0x10000
# define O_RSYNC	0x20000

# define O_RDONLY	0
# define O_WRONLY	1
# define O_RDWR		2

# define O_ACCMODE	(O_WRONLY | O_RDWR)

#endif /* !LIBC_KERNEL_NETBSD_FCNTL_H */
