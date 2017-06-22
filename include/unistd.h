/* $Id$ */
/* Copyright (c) 2004-2017 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_UNISTD_H
# define LIBC_UNISTD_H

# include "compat.h"


/* types */
# ifndef gid_t
#  define gid_t gid_t
typedef __gid_t gid_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef __id_t id_t;
# endif
# ifndef intptr_t
#  define intptr_t intptr_t
typedef __intptr_t intptr_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef __off_t off_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef __pid_t pid_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef __size_t size_t;
# endif
# ifndef ssize_t
#  define ssize_t ssize_t
typedef __ssize_t ssize_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef __uid_t uid_t;
# endif
# ifndef useconds_t
#  define useconds_t useconds_t
typedef __useconds_t useconds_t;
# endif

# include "compat/unistd.h"


/* constants */
/* for access() */
enum { F_OK, R_OK, W_OK, X_OK };

/* file streams */
# define STDIN_FILENO	0
# define STDOUT_FILENO	1
# define STDERR_FILENO	2

# define _POSIX_VERSION		200112L
# define _POSIX2_VERSION	200112L


/* variables */
extern char * optarg;
extern int optind, opterr, optopt;


/* functions */
int access(char const * filename, int mode);
unsigned int alarm(unsigned int seconds);
int brk(void * addr);
int chdir(char const * filename);
int chown(char const * filename, uid_t owner, gid_t group);
int chroot(char const * filename);
int close(int fildes);
int dup(int fildes);
int dup2(int fildes1, int fildes2);
int execl(char const * filename, char * const arg, ...);
int execle(char const * filename, char * const arg, ...);
int execlp(char const * filename, char * const arg, ...);
int execv(char const * filename, char * const argv[]);
int execve(char const * filename, char * const argv[], char * const envp[]);
int execvp(char const * filename, char * const argv[]);
void _exit(int status);
int fchdir(int fildes);
int fchown(int fildes, uid_t uid, gid_t gid);
pid_t fork(void);
int fsync(int fildes);
int ftruncate(int fildes, off_t offset);
char * getcwd(char * buf, size_t size);
gid_t getegid(void);
uid_t geteuid(void);
gid_t getgid(void);
int gethostname(char * name, size_t size);
char * getlogin(void);
int getlogin_r(char * buf, size_t size);
int getopt(int argc, char * const argv[], char const * optstring);
pid_t getpgrp(void);
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
char * getwd(char * buf);
int isatty(int fildes);
int lchown(char const * filename, uid_t owner, gid_t group);
int link(char const * from, char const * to);
int linkat(int fromfd, char const * from, int tofd, char const * to);
off_t lseek(int fildes, off_t offset, int whence);
int nice(int inc);
int pipe(int fildes[2]);
ssize_t read(int fildes, void * buf, size_t count);
ssize_t readlink(char const * filename, char * buf, size_t bufsiz);
ssize_t readlinkat(int fd, char const * filename, char * buf, size_t bufsiz);
int rmdir(char const * filename);
void * sbrk(intptr_t increment);
int setgid(gid_t gid);
int sethostname(char const * name, size_t size);
int setpgid(pid_t pid, pid_t pgid);
int setpgrp(void);
int setregid(gid_t rgid, gid_t egid);
int setreuid(uid_t ruid, uid_t euid);
pid_t setsid(void);
int setuid(uid_t uid);
unsigned int sleep(unsigned int seconds);
int symlink(char const * from, char const * to);
int symlinkat(char const * from, int fd, char const * to);
void sync(void);
long sysconf(int name);
int truncate(char const * filename, off_t offset);
char * ttyname(int fildes);
int unlink(char const * filename);
int unlinkat(int fd, char const * filename, int flags);
int usleep(useconds_t useconds);
pid_t vfork(void);
ssize_t write(int fildes, const void * buf, size_t count);

#endif /* !LIBC_UNISTD_H */
