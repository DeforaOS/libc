/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include "sys/stat.h"
#include "sys/types.h"
#include "inttypes.h"
#include "stdarg.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "dirent.h"
#include "errno.h"
#include "string.h"
#include "termios.h"
#include "time.h"
#include "limits.h"
#include "signal.h"
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
/* XXX when wrongly used this is a potential security flaw */
#ifndef SYS_access
# warning Unsupported platform: access() is missing
int access(char const * filename, int mode)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* alarm */
#ifndef SYS_alarm
# ifdef SYS_setitimer
# include "sys/time.h"
unsigned int alarm(unsigned int seconds)
{
	struct itimerval cur;
	struct itimerval old;

	memset(&cur, 0, sizeof(cur));
	cur.it_interval.tv_sec = seconds;
	memset(&old, 0, sizeof(old));
	if(setitimer(ITIMER_REAL, &cur, &old) != 0)
		return -1;
	return old.it_interval.tv_sec;
}
# else
#  warning Unsupported platform: alarm() is missing
unsigned int alarm(unsigned int seconds)
{
	errno = ENOSYS;
	return -1;
}
# endif
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
int chdir(char const * filename)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* chown */
#ifndef SYS_chown
# warning Unsupported platform: chown() is missing
int chown(char const * filename, uid_t owner, gid_t group)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* close */
#ifndef SYS_close
# warning Unsupported platform: close() is missing
int close(int fildes)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* dup */
#ifndef SYS_dup
# warning Unsupported platform: dup() is missing
int dup(int fildes)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* dup2 */
#ifndef SYS_dup2
# warning Unsupported platform: dup2() is missing
int dup(int fildes1, int fildes2)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* execl */
int execl(char const * filename, char * const arg, ...)
{
	int ret = 0;
	va_list ap;
	char const ** argv = NULL;
	size_t argv_cnt = 0;
	char * p = arg;
	char const ** q;

	va_start(ap, arg);
	do
	{
		if((q = realloc(argv, sizeof(*argv) * (argv_cnt + 2))) == NULL)
		{
			free(argv);
			va_end(ap);
			return -1;
		}
		argv = q;
		argv[argv_cnt++] = p;
	}
	while((p = va_arg(ap, char *)) != NULL);
	va_end(ap);
	argv[argv_cnt] = NULL;
	ret = execv(filename, argv);
	free(argv);
	return ret;
}


/* execle */
int execle(char const * filename, char * const arg, ...)
{
	int ret = 0;
	va_list ap;
	char const ** argv = NULL;
	size_t argv_cnt = 0;
	char * p = arg;
	char const ** q;
	char ** envp;

	va_start(ap, arg);
	do
	{
		if((q = realloc(argv, sizeof(*argv) * (argv_cnt + 1))) == NULL)
		{
			free(argv);
			va_end(ap);
			return -1;
		}
		argv = q;
		argv[argv_cnt++] = p;
	}
	while((p = va_arg(ap, char *)) != NULL);
	va_end(ap);
	envp = (char **)argv[--argv_cnt];
	argv[argv_cnt] = NULL;
	ret = execve(filename, argv, envp);
	free(argv);
	return ret;
}


/* execlp */
int execlp(char const * filename, char * const arg, ...)
{
	int ret = 0;
	va_list ap;
	char const ** argv = NULL;
	size_t argv_cnt = 0;
	char * p = arg;
	char const ** q;

	va_start(ap, arg);
	do
	{
		if((q = realloc(argv, sizeof(*argv) * (argv_cnt + 2))) == NULL)
		{
			free(argv);
			va_end(ap);
			return -1;
		}
		argv = q;
		argv[argv_cnt++] = p;
	}
	while((p = va_arg(ap, char *)) != NULL);
	va_end(ap);
	argv[argv_cnt] = NULL;
	ret = execvp(filename, argv);
	free(argv);
	return ret;
}


/* execv */
int execv(char const * filename, char * const argv[])
{
	return execve(filename, argv, environ);
}


/* execve */
#ifndef SYS_execve
# warning Unsupported platform: execve() is missing
int execve(char const * filename, char * const argv[], char * const envp[])
{
	errno = ENOSYS;
	return -1;
}
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
	if((path = getenv("PATH")) == NULL
			|| path[0] == '\0')
	{
		errno = ENOENT;
		return -1;
	}
	len = strlen(filename) + 2;
	do
	{
		if(path[i] != ':' && path[i] != '\0')
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
		oldi = i + 1;
	}
	while(path[i++] != '\0');
	free(buf);
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


/* exit */
#ifndef SYS_exit
# warning Unsupported platform: exit() is missing
void _exit(int status)
{
	char ** p = NULL;

	/* XXX make it crash */
	p = *p;
}
#endif


/* fchdir */
#ifndef SYS_fchdir
# warning Unsupported platform: fchdir() is missing
int fchdir(int fildes)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* fchown */
#ifndef SYS_fchown
# warning Unsupported platform: fchown() is missing
int fchown(int fildes, uid_t uid, gid_t gid)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* fork */
#ifndef SYS_fork
# warning Unsupported platform: fork() is missing
pid_t fork(void)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* fsync */
#ifndef SYS_fsync
# warning Unsupported platform: fsync() is missing
int fsync(int fildes)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* ftruncate */
#ifndef SYS_ftruncate
# warning Unsupported platform: ftruncate() is missing
int ftruncate(int fildes, off_t offset)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* getcwd */
#ifndef SYS_getcwd
# warning Unsupported platform: getcwd() is missing
char * getcwd(char * buf, size_t size)
{
	errno = ENOSYS;
	return NULL;
}
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
gid_t getgid(void)
{
	/* XXX not allowed to fail */
	return 0;
}
#endif


/* gethostname */
int gethostname(char * buf, size_t size)
{
#if defined(SYS_sysctl) && defined(CTL_KERN) && defined(KERN_HOSTNAME)
	int mib[2] = { CTL_KERN, KERN_HOSTNAME };

	if(sysctl(mib, 2, buf, &size, NULL, 0) != 0)
		return -1;
	return 0;
#else
# warning Unsupported platform: gethostname() is missing
	errno = ENOSYS;
	return -1;
#endif
}


/* getlogin */
char * getlogin(void)
{
	static char login[LOGIN_NAME_MAX + 1];

	if(getlogin_r(login, sizeof(login)) != 0)
		return NULL;
	return login;
}


/* getlogin_r */
#ifndef SYS_getlogin_r
# include "pwd.h"
int getlogin_r(char * buf, size_t size)
{
	struct passwd * pw;

	if((pw = getpwuid(getuid())) == NULL) /* FIXME maybe not re-entrant */
		return 1;
	if(strlen(pw->pw_name) + 1 > size)
	{
		errno = ERANGE;
		return 1;
	}
	strcpy(buf, pw->pw_name);
	return 0;
}
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
pid_t getpid(void)
{
	/* XXX not allowed to fail */
	return 1;
}
#endif


/* getppid */
#ifndef SYS_getppid
# warning Unsupported platform: getppid() is missing
pid_t getppid(void)
{
	/* XXX not allowed to fail */
	return 1;
}
#endif


/* getuid */
#ifndef SYS_getuid
# warning Unsupported platform: getuid() is missing
uid_t getuid(void)
{
	/* XXX not allowed to fail */
	return 0;
}
#endif


/* getwd */
char * getwd(char * buf)
{
	/* XXX this is a potential security flaw */
	return getcwd(buf, PATH_MAX);
}


/* isatty */
int isatty(int fildes)
{
	struct termios t;

	return tcgetattr(fildes, &t) == 0 ? 1 : 0;
}


/* lchown */
#ifndef SYS_lchown
# warning Unsupported platform: lchown() is missing
int lchown(char const * filename, uid_t owner, gid_t group)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* link */
#ifndef SYS_link
# warning Unsupported platform: link() is missing
int link(char const * from, char const * to)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* lseek */
#ifndef SYS_lseek
# warning Unsupported platform: lseek() is missing
off_t lseek(int fildes, off_t offset, int whence)
{
	errno = ENOSYS;
	return -1;
}
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
int pipe(int fildes[2])
{
	errno = ENOSYS;
	return -1;
}
#endif


/* read */
#ifndef SYS_read
# warning Unsupported platform: read() is missing
ssize_t read(int fildes, void * buf, size_t count)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* readlink */
#ifndef SYS_readlink
# warning Unsupported platform: readlink() is missing
ssize_t readlink(char const * filename, char * buf, size_t bufsiz)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* rmdir */
#ifndef SYS_rmdir
# warning Unsupported platform: rmdir() is missing
int rmdir(char const * filename)
{
	errno = ENOSYS;
	return -1;
}
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
void * sbrk(intptr_t increment)
{
	errno = ENOSYS;
	return (void*)-1;
}
#endif


/* setgid */
#ifndef SYS_setgid
# warning Unsupported platform: setgid() is missing
int setgid(gid_t gid)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setpgid */
#ifndef SYS_setpgid
# warning Unsupported platform: setpgid() is missing
int setpgid(pid_t pid, pid_t pgid)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setregid */
#ifndef SYS_setregid
# warning Unsupported platform: setregid() is missing
int setregid(gid_t rgid, gid_t egid)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setreuid */
#ifndef SYS_setreuid
# warning Unsupported platform: setreuid() is missing
int setreuid(uid_t ruid, uid_t euid)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setsid */
#ifndef SYS_setsid
# warning Unsupported platform: setsid() is missing
int setsid(void)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setuid */
#ifndef SYS_setuid
# warning Unsupported platform: setuid() is missing
int setuid(uid_t uid)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sleep */
unsigned int sleep(unsigned int seconds)
{
	struct timespec ts;
	
	ts.tv_sec = seconds;
	ts.tv_nsec = 0;
	if(nanosleep(&ts, &ts) == 0)
		return 0;
	return ts.tv_sec;
}


/* strsignal */
char * strsignal(int sig)
{
	static const struct
	{
		int signal;
		const char * name;
	} names[] = {
		{ SIGABRT,	"SIGABRT"	},
		{ SIGCONT,	"SIGCONT"	},
		{ SIGHUP,	"SIGHUP"	},
		{ SIGILL,	"SIGILL"	},
		{ SIGINT,	"SIGINT"	},
		{ SIGKILL,	"SIGKILL"	},
		{ SIGPIPE,	"SIGPIPE"	},
		{ SIGQUIT,	"SIGQUIT"	},
		{ SIGSEGV,	"SIGSEGV"	},
		{ SIGSTOP,	"SIGSTOP"	},
		{ SIGTRAP,	"SIGTRAP"	},
		{ SIGUSR1,	"SIGUSR1"	},
		{ SIGUSR2,	"SIGUSR2"	},
		{ 0,		NULL		}
	};
	static char buf[8];
	size_t i;

	for(i = 0; names[i].name != NULL; i++)
		if(names[i].signal == sig)
		{
			snprintf(buf, sizeof(buf), "%s", names[i].name);
			return buf;
		}
	return NULL;
}


/* symlink */
#ifndef SYS_symlink
# warning Unsupported platform: symlink() is missing
int symlink(char const * from, char const * to)
{
	errno = -ENOSYS;
	return -1;
}
#endif


/* sync */
#ifndef SYS_sync
# warning Unsupported platform: sync() is missing
#endif


/* sysconf */
long sysconf(int name)
{
#if defined(__linux__)
	switch(name)
	{
		case _SC_CLK_TCK:
			return 100;
		case _SC_PAGESIZE:
			return 4096;
	}
#elif defined(__NetBSD__)
# include "kernel/netbsd/sys/sysctl.h"
	int mib[2];
	size_t len;
	struct clockinfo ci;

	switch(name)
	{
		case _SC_CLK_TCK:
			mib[0] = CTL_KERN;
			mib[1] = KERN_CLOCKRATE;
			len = sizeof(ci);
			return sysctl(mib, 2, &ci, &len, NULL, 0) != -1
				? ci.hz : -1;
		case _SC_PAGESIZE:
			mib[0] = CTL_HW;
			mib[1] = HW_PAGESIZE;
			len = sizeof(name);
			return sysctl(mib, 2, &name, &len, NULL, 0) != -1
				? name : -1;
	}
#else
# warning Unsupported platform: sysconf() is missing
#endif
	errno = ENOSYS;
	return -1;
}


/* truncate */
#ifndef SYS_truncate
# warning Unsupported platform: truncate() is missing
int truncate(char const * filename, off_t offset)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* ttyname */
char * ttyname(int fildes)
{
	static char buf[260]; /* XXX strlen(_PATH_DEV) + NAME_MAX + 2 */
	struct stat st;
	dev_t rdev;
	DIR * dir;
	struct dirent * de;

	if(isatty(fildes) != 1)
		return NULL;
	if(fstat(fildes, &st) != 0)
		return NULL;
	if(!S_ISCHR(st.st_mode))
	{
		errno = ENOTTY;
		return NULL;
	}
	if((dir = opendir("/dev")) == NULL)
		return NULL;
	rdev = st.st_rdev;
	strcpy(buf, "/dev/");
	while((de = readdir(dir)) != NULL)
	{
		strcpy(&buf[5], de->d_name);
		if(stat(buf, &st) != 0)
			continue;
		if(!S_ISCHR(st.st_mode) || rdev != st.st_rdev)
			continue;
		closedir(dir);
		return buf;
	}
	closedir(dir);
	errno = ENOTTY;
	return NULL;
}


/* unlink */
#ifndef SYS_unlink
# warning Unsupported platform: unlink() is missing
int unlink(char const * filename)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* usleep */
int usleep(useconds_t useconds)
{
	struct timespec tv;

	tv.tv_sec = 0;
	tv.tv_nsec = useconds * 1000;
	return nanosleep(&tv, NULL);
}


/* vfork */
#ifndef SYS_vfork
# warning Unsupported platform: vfork() is missing
pid_t vfork(void)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* write */
#ifndef SYS_write
# warning Unsupported platform: write() is missing
ssize_t write(int fildes, const void * buf, size_t count)
{
	errno = ENOSYS;
	return -1;
}
#endif
