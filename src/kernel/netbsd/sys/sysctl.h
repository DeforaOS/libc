/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#ifndef KERNEL_NETBSD_SYS_SYSCTL_H
# define KERNEL_NETBSD_SYS_SYSCTL_H


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

/* sysctl name */
# define CTL_KERN	1
# define CTL_HW		6

# define KERN_OSTYPE	1
# define KERN_OSRELEASE	2
# define KERN_VERSION	4
# define KERN_HOSTNAME	10

# define HW_MACHINE	1


/* functions */
int sysctl(int * name, unsigned int namecnt, void * from, size_t * fromsize,
		void * to, size_t tosize);

#endif /* !KERNEL_NETBSD_SYS_SYSCTL_H */
