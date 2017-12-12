/* $Id$ */
/* Copyright (c) 2012-2017 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "tracer-syscalls.h"
#include "../src/syscalls.h"


/* private */
/* types */
struct flag
{
	unsigned long bits;
	char const * string;
};

struct value
{
	unsigned long value;
	char const * string;
};


/* constants */
/* flags */
static struct flag _flags_access[] =
{
	{ R_OK,		"R_OK"	},
	{ W_OK,		"W_OK"	},
	{ X_OK,		"X_OK"	},
	{ 0,		NULL	}
};

static struct flag _flags_open[] =
{
	{ O_RDONLY,	"O_RDONLY"	},
	{ O_RDWR,	"O_RDWR"	},
	{ O_WRONLY,	"O_WRONLY"	},
	{ O_NONBLOCK,	"O_NONBLOCK"	},
	{ O_APPEND,	"O_APPEND"	},
	{ O_CREAT,	"O_CREAT"	},
	{ O_TRUNC,	"O_TRUNC"	},
	{ O_EXCL,	"O_EXCL"	},
#ifdef O_CLOEXEC
	{ O_CLOEXEC,	"O_CLOEXEC"	},
#endif
	{ 0,		NULL		}
};

/* values */
static struct value _values_signal[] =
{
	{ SIGHUP,	"SIGHUP"	},
	{ SIGINT,	"SIGINT"	},
	{ SIGQUIT,	"SIGQUIT"	},
	{ SIGILL,	"SIGILL"	},
	{ SIGTRAP,	"SIGTRAP"	},
	{ SIGABRT,	"SIGABRT"	},
	{ SIGIOT,	"SIGIOT"	},
	{ SIGFPE,	"SIGFPE"	},
	{ SIGKILL,	"SIGKILL"	},
	{ SIGBUS,	"SIGBUS"	},
	{ SIGSEGV,	"SIGSEGV"	},
	{ SIGPIPE,	"SIGPIPE"	},
	{ SIGALRM,	"SIGALRM"	},
	{ SIGTERM,	"SIGTERM"	},
	{ SIGSTOP,	"SIGSTOP"	},
	{ SIGTSTP,	"SIGTSTP"	},
	{ SIGCONT,	"SIGCONT"	},
	{ SIGCHLD,	"SIGCHLD"	},
	{ SIGUSR1,	"SIGUSR1"	},
	{ SIGUSR2,	"SIGUSR2"	},
	{ 0,		NULL		}
};

/* syscalls */
static const struct
{
	int number;
	char const * name;
}
_syscalls[] =
{
#ifdef SYS_access
	{ SYS_access,		"access"	},
#endif
#ifdef SYS_brk
	{ SYS_brk,		"brk"		},
#endif
	{ SYS_chmod,		"chmod"		},
	{ SYS_chown,		"chown"		},
	{ SYS_close,		"close"		},
	{ SYS_dup,		"dup"		},
#ifdef SYS_dup2
	{ SYS_dup2,		"dup2"		},
#endif
	{ SYS_execve,		"execve"	},
	{ SYS_exit,		"_exit"		},
#ifdef SYS_fchdir
	{ SYS_fchdir,		"fchdir"	},
#endif
	{ SYS_fchmod,		"fchmod"	},
	{ SYS_fchown,		"fchown"	},
	{ SYS_fcntl,		"fcntl"		},
#ifdef SYS_flock
	{ SYS_flock,		"flock"		},
#endif
	{ SYS_fork,		"fork"		},
	{ SYS_fstat,		"fstat"		},
#ifdef SYS_fsync
	{ SYS_fsync,		"fsync"		},
#endif
#ifdef SYS_getdents
	{ SYS_getdents,		"getdents"	},
#endif
#ifdef SYS_getegid
	{ SYS_getegid,		"getegid"	},
#endif
#ifdef SYS_geteuid
	{ SYS_geteuid,		"geteuid"	},
#endif
	{ SYS_getgid,		"getgid"	},
#ifdef SYS_getpgrp
	{ SYS_getpgrp,		"getpgrp"	},
#endif
	{ SYS_getpid,		"getpid"	},
#ifdef SYS_getppid
	{ SYS_getppid,		"getppid"	},
#endif
#ifdef SYS_getpriority
	{ SYS_getpriority,	"getpriority"	},
#endif
#ifdef SYS_getrlimit
	{ SYS_getrlimit,	"getrlimit"	},
#endif
#ifdef SYS_getrusage
	{ SYS_getrusage,	"getrusage"	},
#endif
	{ SYS_gettimeofday,	"gettimeofday"	},
	{ SYS_getuid,		"getuid"	},
#ifdef SYS_ioctl
	{ SYS_ioctl,		"ioctl"		},
#endif
	{ SYS_kill,		"kill"		},
	{ SYS_lchown,		"lchown"	},
	{ SYS_link,		"link"		},
	{ SYS_lseek,		"lseek"		},
	{ SYS_lstat,		"lstat"		},
	{ SYS_mknod,		"mknod"		},
#ifdef SYS_mlock
	{ SYS_mlock,		"mlock"		},
#endif
	{ SYS_mmap,		"mmap"		},
#ifdef SYS_mprotect
	{ SYS_mprotect,		"mprotect"	},
#endif
	{ SYS_munmap,		"munmap"	},
	{ SYS_open,		"open"		},
	{ SYS_pipe,		"pipe"		},
#ifdef SYS_poll
	{ SYS_poll,		"poll"		},
#endif
	{ SYS_read,		"read"		},
	{ SYS_readlink,		"readlink"	},
#ifdef SYS_select
	{ SYS_select,		"select"	},
#endif
	{ SYS_setgid,		"setgid"	},
#ifdef SYS_setpriority
	{ SYS_setpriority,	"setpriority"	},
#endif
	{ SYS_setregid,		"setregid"	},
	{ SYS_setreuid,		"setreuid"	},
#ifdef SYS_setrlimit
	{ SYS_setrlimit,	"setrlimit"	},
#endif
#ifdef SYS_setsid
	{ SYS_setsid,		"setsid"	},
#endif
	{ SYS_setuid,		"setuid"	},
	{ SYS_stat,		"stat"		},
	{ SYS_symlink,		"symlink"	},
	{ SYS_sync,		"sync"		},
#ifdef SYS_sysctl
	{ SYS_sysctl,		"sysctl"	},
#endif
	{ SYS_umask,		"umask"		},
	{ SYS_unlink,		"unlink"	},
#ifdef SYS_wait4
	{ SYS_wait4,		"wait4"		},
#endif
#ifdef SYS_waitpid
	{ SYS_waitpid,		"waitpid"	},
#endif
	{ SYS_write,		"write"		}
};


/* prototypes */
static void _analyze_print_mask(struct flag * flags, unsigned long mask);
static void _analyze_print_value(struct value * values, unsigned long value);

static void _analyze_print(char const * str);


/* public */
/* functions */
void analyze(int number, long arg1, long arg2, long arg3, long arg4)
{
	size_t i;
	char buf[256];
	char const * s;
	void * p;

	_analyze_print("tracer: syscall: ");
	snprintf(buf, sizeof(buf), "%d", number);
	for(i = 0; i < sizeof(_syscalls) / sizeof(*_syscalls); i++)
		if(_syscalls[i].number == number)
		{
			snprintf(buf, sizeof(buf), "%s", _syscalls[i].name);
			break;
		}
	_analyze_print(buf);
	switch(number)
	{
#ifdef SYS_access
		case SYS_access:
			s = (char const *)arg1;
			snprintf(buf, sizeof(buf), "(\"%s\", ", s);
			_analyze_print(buf);
			_analyze_print_mask(_flags_access, arg2);
			snprintf(buf, sizeof(buf), ")\n");
			break;
#endif
		case SYS_close:
		case SYS_exit:
#ifdef SYS_fchdir
		case SYS_fchdir:
#endif
#ifdef SYS_fsync
		case SYS_fsync:
#endif
			snprintf(buf, sizeof(buf), "(%d)\n", arg1);
			break;
		case SYS_execve:
			/* FIXME analyze the arguments and environment */
			s = (char const *)arg1;
			snprintf(buf, sizeof(buf), "(\"%s\")\n", s);
			break;
		case SYS_fstat:
			p = (void *)arg2;
			snprintf(buf, sizeof(buf), "(%d, %p)\n", arg1, p);
			break;
		case SYS_fcntl:
#ifdef SYS_flock
		case SYS_flock:
#endif
			snprintf(buf, sizeof(buf), "(%d, %d)\n", arg1, arg2);
			break;
		case SYS_kill:
			snprintf(buf, sizeof(buf), "(%d, ", arg1);
			_analyze_print(buf);
			_analyze_print_value(_values_signal, arg2);
			snprintf(buf, sizeof(buf), ")\n");
			break;
#ifdef SYS_ioctl
		case SYS_ioctl:
			snprintf(buf, sizeof(buf), "(%d, %lu)\n", arg1, arg2);
			break;
#endif
		case SYS_lseek:
			snprintf(buf, sizeof(buf), "(%d, %ld, %d)\n", arg1,
					arg2, arg3);
			break;
		case SYS_lstat:
		case SYS_stat:
			s = (char const *)arg1;
			p = (void *)arg2;
			snprintf(buf, sizeof(buf), "(\"%s\", %p)\n", s, p);
			break;
		case SYS_munmap:
			snprintf(buf, sizeof(buf), "(%p, %lu)\n", arg1, arg2);
			break;
		case SYS_open:
			s = (char const *)arg1;
			snprintf(buf, sizeof(buf), "(\"%s\", ", s);
			_analyze_print(buf);
			_analyze_print_mask(_flags_open, arg2);
			snprintf(buf, sizeof(buf), ")\n");
			break;
		case SYS_read:
		case SYS_write:
			p = (void *)arg2;
			snprintf(buf, sizeof(buf), "(%d, %p, %lu)\n", arg1, p,
					arg3);
			break;
#ifdef SYS_sysctl
		case SYS_sysctl:
			/* FIXME analyze the name */
			snprintf(buf, sizeof(buf), "(%p, %u)\n", arg1, arg2);
			break;
#endif
		default:
			snprintf(buf, sizeof(buf), "()\n");
			break;
	}
	_analyze_print(buf);
}


/* private */
/* functions */
/* analyze_print_mask */
static void _analyze_print_mask(struct flag * flags, unsigned long mask)
{
	char const * sep = "";
	size_t i;
	unsigned long m = mask;
	char buf[32];

	/* print the known flags set for this mask */
	for(i = 0; flags[i].string != NULL; i++)
		if((flags[i].bits & mask) == flags[i].bits)
		{
			_analyze_print(sep);
			_analyze_print(flags[i].string);
			sep = " | ";
			m -= (flags[i].bits & m);
		}
	/* print the remaining part of the mask (as hexadecimal) */
	if(m != 0)
	{
		_analyze_print(sep);
		snprintf(buf, sizeof(buf), "0x%x", m);
		_analyze_print(buf);
	}
}


/* analyze_print_value */
static void _analyze_print_value(struct value * values, unsigned long value)
{
	size_t i;
	char buf[32];

	/* print the value if known */
	for(i = 0; values[i].string != NULL; i++)
		if(values[i].value == value)
		{
			_analyze_print(values[i].string);
			return;
		}
	/* print the value (as decimal) */
	snprintf(buf, sizeof(buf), "%u", value);
	_analyze_print(buf);
}


/* analyze_print */
static void _analyze_print(char const * str)
{
	size_t len;

	len = strlen(str);
	syscall(SYS_write, STDERR_FILENO, str, len);
}
