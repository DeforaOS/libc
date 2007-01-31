/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_LINUX_FCNTL_H
# define LIBC_KERNEL_LINUX_FCNTL_H


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
