/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_POLL_H
# define LIBC_POLL_H


/* types */
# ifndef pollfd
#  define pollfd pollfd
struct pollfd
{
	int fd;
	short int events;
	short int revents;
};
# endif
# ifndef nfds_t
# define nfds_t nfds_t
typedef unsigned int nfds_t;
# endif


/* functions */
int poll(struct pollfd * fds, nfds_t nfds, int timeout);

#endif /* !LIBC_POLL_H */
