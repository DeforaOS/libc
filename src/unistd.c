/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "sys/types.h"
#include "inttypes.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
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
#ifndef SYS_access
# warning Unsupported platform: access() is missing
#endif


/* alarm */
#ifndef SYS_alarm
# warning Unsupported platform: alarm() is missing
#endif


/* brk */
#ifndef SYS_brk
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


/* _exit */


/* fork */


/* getcwd */


/* getegid */


/* geteuid */


/* getgid */


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


/* getppid */


/* getuid */


/* isatty */
int isatty(int fildes)
	/* FIXME implement */
{
	errno = ENOSYS;
	return 0;
}


/* lchown */


/* link */


/* nice */


/* pipe */


/* read */


/* readlink */


/* rmdir */


/* sbrk */
void * sbrk(unsigned int increment)
	/* FIXME implement */
{
	errno = ENOSYS;
	return NULL;
}


/* setgid */


/* setpgid */


/* setregid */


/* setreuid */


/* setsid */


/* setuid */


/* sleep */
unsigned int sleep(unsigned int seconds)
{
	struct timespec ts = { seconds, 0 };

	if(nanosleep(&ts, &ts) == 0)
		return 0;
	return ts.tv_sec;
}


/* symlink */


/* sync */


/* ttyname */
char * ttyname(int fildes)
	/* FIXME implement */
{
	errno = ENOSYS;
	return NULL;
}


/* unlink */


/* vfork */


/* write */
