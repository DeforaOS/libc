/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "tracer-syscalls.h"
#include "../src/syscalls.h"


/* private */
/* constants */
static const struct
{
	int number;
	char const * name;
}
_syscalls[] =
{
	{ SYS_access,	"access"	},
	{ SYS_brk,	"brk"		},
	{ SYS_close,	"close"		},
	{ SYS_exit,	"exit"		},
	{ SYS_fchdir,	"fchdir"	},
	{ SYS_getdents,	"getdents"	},
	{ SYS_getegid,	"getegid"	},
	{ SYS_geteuid,	"geteuid"	},
	{ SYS_getgid,	"getgid"	},
	{ SYS_getrlimit,"getrlimit"	},
	{ SYS_getuid,	"getuid"	},
	{ SYS_ioctl,	"ioctl"		},
	{ SYS_mmap,	"mmap"		},
	{ SYS_mprotect,	"mprotect"	},
	{ SYS_munmap,	"munmap"	},
	{ SYS_open,	"open"		},
	{ SYS_read,	"read"		},
	{ SYS_setrlimit,"setrlimit"	},
	{ SYS_sync,	"sync"		},
	{ SYS_sysctl,	"sysctl"	},
	{ SYS_write,	"write"		}
};


/* prototypes */
static void _analyze_print(char const * str);


/* public */
/* functions */
void analyze(int number, long arg2)
{
	size_t i;
	char buf[256];
	char const * s = (char const *)arg2;

	_analyze_print("tracer - syscall ");
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
		case SYS_access:
		case SYS_open:
			snprintf(buf, sizeof(buf), "(\"%s\")\n", s);
			break;
		case SYS_close:
		case SYS_ioctl:
		case SYS_exit:
			snprintf(buf, sizeof(buf), "(%d)\n", arg2);
			break;
		case SYS_munmap:
			snprintf(buf, sizeof(buf), "(%p)\n", arg2);
			break;
		default:
			snprintf(buf, sizeof(buf), "()\n");
			break;
	}
	_analyze_print(buf);
}


/* private */
/* functions */
static void _analyze_print(char const * str)
{
	size_t len;

	len = strlen(str);
	syscall(SYS_write, 0, str, len);
}
