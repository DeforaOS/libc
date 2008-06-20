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



#include "sys/types.h"
#include "unistd.h"
#include "errno.h"
#include "../syscalls.h"
#include "sys/socket.h"


/* functions */
#ifndef SYS_accept
# warning Unsupported platform: accept() is missing
int accept(int fd, struct sockaddr * addr, socklen_t * len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* bind */
#ifndef SYS_bind
# warning Unsupported platform: bind() is missing
int bind(int fd, const struct sockaddr * addr, socklen_t len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* listen */
#ifndef SYS_listen
# warning Unsupported platform: listen() is missing
int listen(int fd, int backlog)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* recv */
#ifndef SYS_recv
# warning Unsupported platform: recv() is missing
ssize_t recv(int fd, void * buf, size_t len, int flags)
{
	if(flags == 0)
		return read(fd, buf, len);
	errno = ENOSYS;
	return -1;
}
#endif


/* send */
#ifndef SYS_send
# warning Unsupported platform: send() is missing
ssize_t send(int fd, const void * buf, size_t len, int flags)
{
	if(flags == 0)
		return write(fd, buf, len);
	errno = ENOSYS;
	return -1;
}
#endif


/* socket */
#ifndef SYS_socket
# warning Unsupported platform: socket() is missing
int socket(int domain, int type, int protocol)
{
	errno = ENOSYS;
	return -1;
}
#endif
