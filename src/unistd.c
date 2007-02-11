/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "sys/types.h"
#include "inttypes.h"
#include "stddef.h"
#include "errno.h"
#include "stdlib.h"
#include "string.h"
#include "termios.h"
#include "time.h"
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
#ifndef SYS_access
# warning Unsupported platform: access() is missing
#endif


/* alarm */
#ifndef SYS_alarm
# warning Unsupported platform: alarm() is missing
#endif


/* brk */
#if defined(SYS_brk)
extern int _brk(void * addr); /* XXX in-kernel prototype */
int brk(void * addr)
{
	return _brk(addr) != -1 ? 0 : -1;
}
#elif defined(SYS_sbrk) /* !SYS_brk && SYS_sbrk */
int brk(void * addr)
{
	void * cur;

	if((cur = sbrk(NULL)) == (void*)-1)
		return -1;
	return sbrk(addr - cur) != (void*)-1 ? 0 : -1;
}
#else /* !SYS_brk && !SYS_sbrk */
# warning Unsupported platform: brk() is missing
#endif


/* chdir */
#ifndef SYS_chdir
# warning Unsupported platform: chdir() is missing
#endif


/* chown */
#ifndef SYS_chown
# warning Unsupported platform: chown() is missing
#endif


/* close */
#ifndef SYS_close
# warning Unsupported platform: close() is missing
#endif


/* dup */
#ifndef SYS_dup
# warning Unsupported platform: dup() is missing
#endif


/* dup2 */
#ifndef SYS_dup2
# warning Unsupported platform: dup2() is missing
#endif


/* execv */
int execv(char const * filename, char * const argv[])
{
	return execve(filename, argv, environ);
}


/* execve */
#ifndef SYS_execve
# warning Unsupported platform: execve() is missing
#endif


/* execvp */
static void _execvp_do(char const * filename, char * const argv[]);

int execvp(char const * filename, char * const argv[])
{
	char const * path;
	size_t i = 0;
	size_t oldi = 0;
	char * buf = NULL;
	size_t buf_cnt = 0;
	size_t len;
	char * p;

	if(strchr(filename, '/') != NULL)
		return execve(filename, argv, environ);
	if((path = getenv("PATH")) != NULL && path[0] != '\0')
	{
		len = strlen(filename) + 2;
		do
		{
			if(path[i] != ':')
				continue;
			if(i - oldi + len > buf_cnt)
			{
				buf_cnt = i - oldi + len;
				if((p = realloc(buf, buf_cnt)) == NULL)
				{
					free(buf);
					return -1;
				}
				buf = p;
			}
			strncpy(buf, &path[oldi], i - oldi);
			buf[i - oldi] = '/';
			strcpy(&buf[i - oldi + 1], filename);
			_execvp_do(buf, argv);
			oldi = i+1;
		}
		while(path[i++] != '\0');
		free(buf);
	}
	return -1;
}

static void _execvp_do(char const * filename, char * const argv[])
{
	size_t i;
	size_t len;
	char const ** arg;

	execve(filename, argv, environ);
	if(errno != ENOEXEC)
		return;
	/* try with a shell instead */
	for(i = 0; argv[i] != NULL; i++);
	len = (i + 2) * sizeof(char*);
	if((arg = malloc(len)) == NULL)
		return;
	arg[0] = argv[0];
	arg[1] = filename;
	for(i = 0; argv[i++] != NULL;)
		arg[i + 1] = argv[i];
	execv("/bin/sh", (char * const *)arg);
	free(arg);
}


/* fork */
#ifndef SYS_fork
# warning Unsupported platform: fork() is missing
#endif


/* fsync */
#ifndef SYS_fsync
# warning Unsupported platform: fsync() is missing
#endif


/* getcwd */
#ifndef SYS_getcwd
# warning Unsupported platform: getcwd() is missing
#endif


/* getegid */
#ifndef SYS_getegid
# warning Unsupported platform: getegid() is missing
#endif


/* geteuid */
#ifndef SYS_geteuid
# warning Unsupported platform: geteuid() is missing
#endif


/* getgid */
#ifndef SYS_getgid
# warning Unsupported platform: getgid() is missing
#endif


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
		return -1; /* there is nothing to parse */
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
#ifndef SYS_getpid
# warning Unsupported platform: getpid() is missing
#endif


/* getppid */
#ifndef SYS_getppid
# warning Unsupported platform: getppid() is missing
#endif


/* getuid */
#ifndef SYS_getuid
# warning Unsupported platform: getuid() is missing
#endif


/* isatty */
int isatty(int fildes)
{
	struct termios t;

	return tcgetattr(fildes, &t) == 0 ? 1 : 0;
}


/* lchown */
#ifndef SYS_lchown
# warning Unsupported platform: lchown() is missing
#endif


/* link */
#ifndef SYS_link
# warning Unsupported platform: link() is missing
#endif


/* nice */
#if !defined(SYS_nice)
# if defined(SYS_setpriority)
#  include "sys/resource.h"
int nice(int inc)
{
	int prio;

	errno = 0;
	if((prio = getpriority(PRIO_PROCESS, 0)) == -1 && errno != 0)
		return -1;
	return setpriority(PRIO_PROCESS, 0, prio + inc);
}
# else
#  warning Unsupported platform: nice() is missing
# endif
#endif /* !SYS_nice */


/* pipe */
#ifndef SYS_pipe
# warning Unsupported platform: pipe() is missing
#endif


/* read */
#ifndef SYS_read
# warning Unsupported platform: read() is missing
#endif


/* readlink */
#ifndef SYS_readlink
# warning Unsupported platform: readlink() is missing
#endif


/* rmdir */
#ifndef SYS_rmdir
# warning Unsupported platform: rmdir() is missing
#endif


/* sbrk */
#if defined(SYS_sbrk)
extern void * _sbrk(intptr_t increment); /* XXX in-kernel prototype */
# if defined(SYS_brk) /* SYS_sbrk && SYS_brk */
extern int _brk(void * addr); /* XXX in-kernel prototype */
void * sbrk(intptr_t increment) /* _brk is used to actually allocate memory */
{
	void * cur;

	if((cur = _sbrk(0)) == (void*)-1 || increment == 0)
		return cur;
	return _brk(cur + increment) != (void*)-1 ? cur : (void*)-1;
}
# else /* SYS_sbrk && !SYS_brk */
void * sbrk(intptr_t increment)
{
	return _sbrk(increment);
}
# endif
#elif defined(SYS_brk) /* !SYS_sbrk && SYS_brk */
extern int _brk(void * addr); /* XXX in-kernel prototype */
extern void * end;
void * sbrk(intptr_t increment)
{
	static void * cur = &end;
	void * ptr;

	if(increment == 0)
		return cur;
	if(_brk(cur + increment) == -1)
		return (void*)-1;
	ptr = cur;
	cur += increment;
	return ptr;
}
#else /* !SYS_sbrk && !SYS_brk */
# warning Unsupported platform: sbrk() is missing
#endif


/* setgid */
#ifndef SYS_setgid
# warning Unsupported platform: setgid() is missing
#endif


/* setpgid */
#ifndef SYS_setpgid
# warning Unsupported platform: setpgid() is missing
#endif


/* setregid */
#ifndef SYS_setregid
# warning Unsupported platform: setregid() is missing
#endif


/* setreuid */
#ifndef SYS_setreuid
# warning Unsupported platform: setreuid() is missing
#endif


/* setsid */
#ifndef SYS_setsid
# warning Unsupported platform: setsid() is missing
#endif


/* setuid */
#ifndef SYS_setuid
# warning Unsupported platform: setuid() is missing
#endif


/* sleep */
unsigned int sleep(unsigned int seconds)
{
	struct timespec ts = { seconds, 0 };

	if(nanosleep(&ts, &ts) == 0)
		return 0;
	return ts.tv_sec;
}


/* symlink */
#ifndef SYS_symlink
# warning Unsupported platform: symlink() is missing
#endif


/* sync */
#ifndef SYS_sync
# warning Unsupported platform: sync() is missing
#endif


/* ttyname */
char * ttyname(int fildes)
{
	errno = ENOSYS; /* FIXME not implemented */
	return NULL;
}


/* unlink */
#ifndef SYS_unlink
# warning Unsupported platform: unlink() is missing
#endif


/* vfork */
#ifndef SYS_vfork
# warning Unsupported platform: vfork() is missing
#endif


/* write */
#ifndef SYS_write
# warning Unsupported platform: write() is missing
#endif
