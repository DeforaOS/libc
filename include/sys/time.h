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



#ifndef LIBC_SYS_TIME_H
# define LIBC_SYS_TIME_H

# include "compat/sys/time.h"


/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct _fd_set fd_set;
# endif
# ifndef itimerval
#  define itimerval itimerval
struct itimerval
{
	struct timeval it_interval;
	struct timeval it_value;
};
# endif


/* functions */
int gettimeofday(struct timeval * tv, void * null);
int select(int fdcnt, fd_set * rfds, fd_set * wfds, fd_set * efds,
		struct timeval * timeout);
int utimes(char const * path, const struct timeval times[2]);

#endif /* !LIBC_SYS_TIME_H */
