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



#ifndef KERNEL_NETBSD_SYS_SYSCTL_H
# define KERNEL_NETBSD_SYS_SYSCTL_H


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif

struct clockinfo
{
	int hz;
	int tick;
	int tickadj;
	int stathz;
	int profhz;
};


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

/* sysctl name */
# define CTL_KERN	1
# define CTL_VM		2
# define CTL_HW		6

# define KERN_OSTYPE	1
# define KERN_OSRELEASE	2
# define KERN_VERSION	4
# define KERN_HOSTNAME	10
# define KERN_CLOCKRATE	12

# define VM_LOADAVG	2

# define HW_MACHINE	1
# define HW_PAGESIZE	7


/* functions */
int sysctl(int * name, unsigned int namecnt, void * from, size_t * fromsize,
		void * to, size_t tosize);

#endif /* !KERNEL_NETBSD_SYS_SYSCTL_H */
