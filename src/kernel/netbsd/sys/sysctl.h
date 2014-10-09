/* $Id$ */
/* Copyright (c) 2007-2012 Pierre Pronchery <khorben@defora.org> */
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



#ifndef KERNEL_NETBSD_SYS_SYSCTL_H
# define KERNEL_NETBSD_SYS_SYSCTL_H


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
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
		void const * to, size_t tosize);

#endif /* !KERNEL_NETBSD_SYS_SYSCTL_H */
