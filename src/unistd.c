/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "sys/types.h"
#include "inttypes.h"
#include "stddef.h"
#include "time.h"
#include "errno.h"
#include "syscalls.h"
#include "unistd.h"


/* variables */
char * optarg = NULL;
int optind = 1;
int opterr = 1;
int optopt = -1;

char ** environ;


/* functions */
/* access */
syscall2(int, access, char const *, filename, int, mode);


/* alarm */
#ifdef SYS_alarm
syscall1(unsigned int, alarm, unsigned int, seconds);
#endif


/* brk */
#ifdef SYS_brk
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


/* execvp */
int execvp(char const * filename, char const * argv[])
{
	return execve(filename, argv, environ);
}


/* _exit */
void _exit(int status)
{
	_syscall1(SYS_exit, status);
}


/* fork */
syscall0(pid_t, fork);


/* getcwd */
#ifdef SYS_getcwd
syscall2(char *, getcwd, char *, buf, size_t, size);
#endif


/* getegid */
syscall0(gid_t, getegid);


/* geteuid */
syscall0(uid_t, geteuid);


/* getgid */
syscall0(gid_t, getgid);


/* getopt */
static void _getopt_reset(char * const ** oldargv, char * const * argv,
		int * i);

int getopt(int argc, char * const argv[], char const * optstring)
{
	static char * const * oldargv = NULL;
	static int i = 0;
	size_t j;

	if(argv == NULL)
	{
		_getopt_reset(&oldargv, NULL, &i);
		errno = EINVAL;
		return -1;
	}
	if(argv != oldargv) /* reset state */
		_getopt_reset(&oldargv, argv, &i);
	if(optind == argc || (i == 0 && argv[optind][0] != '-'))
		/* there is nothing to parse */
		return -1;
	if(argv[optind][++i] == '\0')
	{
		if(++optind == argc) /* every argument had options */
			return -1;
		if(argv[optind][0] != '-' /* next argument has no options */
				|| argv[optind][1] == '\0')
			return -1;
		if(argv[optind][0] == '-' && argv[optind][1] == '-'
				&& argv[optind][2] == '\0') /* "--" stops */
		{
			optind++;
			return -1;
		}
		i = 1;
	}
	optopt = argv[optind][i];
	for(j = 0; optstring[j] != '\0'; j++)
	{
		if(optstring[j] == ':')
			continue;
		if(optopt == optstring[j])
			break;
	}
	if(optstring[j] == '\0')
		return optstring[0] != ':' ? '?' : ':';
	if(optstring[j+1] == ':')
	{
		if(argv[optind][i+1] != '\0')
		{
			optarg = &argv[optind][i+1];
			optind++;
			i = 0;
			return optopt;
		}
		optarg = argv[optind+1];
		optind+=2;
		i = 0;
	}
	return optopt;
}

static void _getopt_reset(char * const ** oldargv, char * const * argv,
		int * i)
{
	optarg = NULL;
	optind = 1;
	opterr = 1;
	optopt = -1;
	*oldargv = argv;
	*i = 0;
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
	/* FIXME implement */
	return 0;
}


/* lchown */
syscall3(int, lchown, char const *, filename, uid_t, owner, gid_t, group);


/* link */
syscall2(int, link, char const *, from, char const *, to);


/* nice */
#ifdef SYS_nice
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
	errno = ENOSYS;
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


/* sleep */
unsigned int sleep(unsigned int seconds)
{
	struct timespec ts = { seconds, 0 };

	if(nanosleep(&ts, &ts) == 0)
		return 0;
	return ts.tv_sec;
}


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
