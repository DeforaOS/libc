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



#ifndef LIBC_KERNEL_NETBSD_UTMPX_H
# define LIBC_KERNEL_NETBSD_UTMPX_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
#ifndef timeval
# define timeval timeval
struct timeval
{
	long tv_sec;
	long tv_usec;
};
#endif

# define _UTMPX_HOST_SIZE	256
# define _UTMPX_ID_SIZE		4
# define _UTMPX_LINE_SIZE	32
# define _UTMPX_USER_SIZE	32
struct utmpx
{
	char ut_user[_UTMPX_USER_SIZE];
	char ut_id[_UTMPX_ID_SIZE];
	char ut_line[_UTMPX_LINE_SIZE];
	char ut_host[_UTMPX_HOST_SIZE];
	char _padding0[2];
	unsigned short int ut_type; /* XXX uint16_t */
	pid_t ut_pid;
	char _padding1[4];
	char _padding2[0]; /* FIXME struct sockaddr_storage */
	struct timeval ut_tv;
	char _padding3[168];
};

#endif /* !LIBC_KERNEL_NETBSD_UTMPX_H */
