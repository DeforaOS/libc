/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "sys/types.h"
#include "syscalls.h"
#include "stddef.h"
#include "unistd.h"
#include "inttypes.h"


/* variables */
char * optarg = NULL;
int optind = 1, opterr, optopt = '?';

char ** environ;


/* functions */
/* access */
syscall2(int, access, char const *, filename, int, mode);


/* alarm */
#ifndef __NetBSD__
syscall1(unsigned int, alarm, unsigned int, seconds);
#endif


/* brk */
#ifndef __NetBSD__
syscall1(int, brk, void *, end_data_segment);
#endif


/* chdir */
syscall1(int, chdir, char const *, filename);


/* chown */
syscall3(int, chown, char const *, filename, uid_t, owner, gid_t, group);


/* close */
syscall1(int, close, int, fildes);


/* dup */
syscall1(int, dup, int, fildes);


/* dup2 */
syscall2(int, dup2, int, fildes1, int, fildes2);


/* execve */
syscall3(int, execve, char const *, filename, char const **, argv,
		char const **, envp);


/* _exit */
void _exit(int status)
{
	_syscall1(SYS_exit, status);
}


/* fork */
syscall0(pid_t, fork);


/* getcwd */
#ifndef __NetBSD__
syscall2(char *, getcwd, char *, buf, size_t, size);
#endif


/* getegid */
syscall0(gid_t, getegid);


/* geteuid */
syscall0(uid_t, geteuid);


/* getgid */
syscall0(gid_t, getgid);


/* getopt */
int getopt(int argc, char * const argv[], char const * optstring)
{
	static char const * p = NULL;
	static int8_t flag = 1;
	int i;

	if(flag)
	{
		flag = 0;
		p = *argv;
	}
	optarg = NULL;
	optopt = '?';
	if(argv[optind] == NULL || *argv[optind] != '-'
			|| *(argv[optind]+1) == '\0')
		return -1;
	if(*(argv[optind]+1) == '-' && *(argv[optind]+2) == '\0')
	{
		optind++;
		return -1;
	}
	if(*p == '\0')
	{
		optind++;
		if(optind >= argc || argv[optind][0] != '-')
			return -1;
		p = argv[optind]+1;
	}
	for(i = 0; optstring[i] != '\0'; i++)
	{
		if(optstring[i] == ':')
			continue;
		if(optstring[i] == *p)
			break;
	}
	if(optstring[i] != *p)
	{
		p++;
		return '?';
	}
	p++;
	if(optstring[i+1] == ':')
	{
		if(*p != '\0' || optind+1 >= argc)
			return '?';
		optarg = (char*)argv[++optind];
		return optstring[i];
	}
	return optstring[i];
}


/* getpid */
syscall0(pid_t, getpid);


/* getppid */
syscall0(pid_t, getppid);


/* getuid */
syscall0(uid_t, getuid);


/* isatty */
int isatty(int fd)
{
	/* FIXME */
	return 0;
}


/* lchown */
syscall3(int, lchown, char const *, filename, uid_t, owner, gid_t, group);


/* link */
syscall2(int, link, char const *, from, char const *, to);


/* nice */
#ifndef __NetBSD__
syscall1(int, nice, int, inc);
#endif


/* pipe */
syscall1(int, pipe, int, filedes[2]);


/* read */
syscall3(ssize_t, read, int, fd, void *, buf, size_t, count);


/* readlink */
syscall3(ssize_t, readlink, char const *, filename, char *, buf,
		size_t, bufsiz);


/* rmdir */
syscall1(int, rmdir, char const *, filename);


/* sbrk */
void * sbrk(unsigned int increment) /* FIXME */
{
	return NULL;
}


/* setgid */
syscall1(int, setgid, gid_t, gid);


/* setpgid */
syscall2(int, setpgid, pid_t, pid, pid_t, pgid);


/* setregid */
syscall2(int, setregid, gid_t, rgid, gid_t, egid);


/* setreuid */
syscall2(int, setreuid, uid_t, ruid, uid_t, euid);


/* setsid */
syscall0(pid_t, setsid);


/* setuid */
syscall1(int, setuid, uid_t, uid);


/* symlink */
syscall2(int, symlink,char const *, from, char const *, to);


/* sync */
syscall0(void, sync);


/* unlink */
syscall1(int, unlink, char const *, filename);


/* vfork */
syscall0(pid_t, vfork);


/* write */
syscall3(ssize_t, write, int, fildes, void const *, buf, size_t, count);
