/* $Id$ */
/* Copyright (c) 2005-2017 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef LIBC_SYS_STAT_H
# define LIBC_SYS_STAT_H

# include "../compat.h"


/* types */
# ifndef blksize_t
#  define blksize_t blksize_t
typedef __blksize_t blksize_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef __gid_t gid_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef __id_t id_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef __nlink_t nlink_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef __uid_t uid_t;
# endif

# include "../compat/sys/stat.h"


/* constants */
# define S_IFMT		0170000
# define S_IFSOCK	0140000
# define S_IFLNK	0120000
# define S_IFREG	0100000
# define S_IFBLK	0060000
# define S_IFDIR	0040000
# define S_IFCHR	0020000
# define S_IFIFO	0010000
# define S_ISUID	0004000
# define S_ISGID	0002000
# define S_ISVTX	0001000
# define S_IRUSR	0000400
# define S_IWUSR	0000200
# define S_IXUSR	0000100
# define S_IRWXU	(S_IRUSR | S_IWUSR | S_IXUSR)
# define S_IRGRP	0000040
# define S_IWGRP	0000020
# define S_IXGRP	0000010
# define S_IRWXG	(S_IRGRP | S_IWGRP | S_IXGRP)
# define S_IROTH	0000004
# define S_IWOTH	0000002
# define S_IXOTH	0000001
# define S_IRWXO	(S_IROTH | S_IWOTH | S_IXOTH)


/* macros */
# define S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
# define S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
# define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
# define S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
# define S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
# define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
# define S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)


/* functions */
int chmod(char const * name, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, char const * name, mode_t mode, int flags);
int fstat(int fd, struct stat * st);
int fstatat(int fd, char const * name, struct stat * st, int flags);
int lstat(char const * name, struct stat * st);
int mkdir(char const * name, mode_t mode);
int mkdirat(int fd, char const * name, mode_t mode);
int mkfifo(char const * name, mode_t mode);
int mkfifoat(int fd, char const * name, mode_t mode);
int mknod(char const * name, mode_t mode, dev_t dev);
int mknodat(int fd, char const * name, mode_t mode, dev_t dev);
int stat(char const * name, struct stat * st);
mode_t umask(mode_t mask);

#endif /* !LIBC_SYS_STAT_H */
