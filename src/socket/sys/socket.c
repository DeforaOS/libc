/* $Id$ */
/* Copyright (c) 2008-2017 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/types.h"
#include "unistd.h"
#include "stddef.h"
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


/* connect */
#ifndef SYS_connect
# warning Unsupported platform: connect() is missing
int connect(int fd, const struct sockaddr * addr, socklen_t len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* getpeername */
#ifndef SYS_getpeername
# warning Unsupported platform: getpeername() is missing
int getpeername(int fd, struct sockaddr * addr, socklen_t * len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* getsockname */
#ifndef SYS_getsockname
# warning Unsupported platform: getsockname() is missing
int getsockname(int fd, struct sockaddr * addr, socklen_t * len)
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
# ifdef SYS_recvfrom
ssize_t recv(int fd, void * buf, size_t len, int flags)
{
	return recvfrom(fd, buf, len, flags, NULL, NULL);
}
# else
#  warning Unsupported platform: recv() is missing
ssize_t recv(int fd, void * buf, size_t len, int flags)
{
	if(flags == 0)
		return read(fd, buf, len);
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* recvfrom */
#ifndef SYS_recvfrom
# warning Unsupported platform: recvfrom() is missing
# ifdef SYS_recv
ssize_t recvfrom(int fd, void * buf, size_t len, int flags,
		struct sockaddr * addr, socklen_t * addrlen)
{
	if(addr == NULL)
		return recv(fd, buf, len, flags);
	errno = ENOSYS;
	return -1;
}
# else
ssize_t recvfrom(int fd, void * buf, size_t len, int flags,
		struct sockaddr * addr, socklen_t * addrlen)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* recvmsg */
#ifndef SYS_recvmsg
ssize_t recvmsg(int fd, struct msghdr * msg, int flags)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* send */
#ifndef SYS_send
# ifdef SYS_sendto
ssize_t send(int fd, const void * buf, size_t len, int flags)
{
	return sendto(fd, buf, len, flags, NULL, 0);
}
# else
#  warning Unsupported platform: send() is missing
ssize_t send(int fd, const void * buf, size_t len, int flags)
{
	if(flags == 0)
		return write(fd, buf, len);
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* sendmsg */
#ifndef SYS_sendmsg
ssize_t sendmsg(int fd, const struct msghdr * msg, int flags)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sendto */
#ifndef SYS_sendto
# warning Unsupported platform: sendto() is missing
# ifdef SYS_send
ssize_t sendto(int fd, const void * buf, size_t len, int flags,
		struct sockaddr * addr, socklen_t addrlen)
{
	if(addr == NULL)
		return send(fd, buf, len, flags);
	errno = ENOSYS;
	return -1;
}
# else
ssize_t sendto(int fd, const void * buf, size_t len, int flags,
		struct sockaddr * addr, socklen_t addrlen)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* setsockopt */
#ifndef SYS_setsockopt
# warning Unsupported platform: setsockopt() is missing
int setsockopt(int fd, int level, int optname, const void * optval,
		socklen_t len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* shutdown */
#ifndef SYS_shutdown
# warning Unsupported platform: shutdown() is missing
int shutdown(int fd, int how)
{
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


/* socketpair */
#ifndef SYS_socketpair
# warning Unsupported platform: socketpair() is missing
int socketpair(int domain, int type, int protocol, int fds[2])
{
	errno = ENOSYS;
	return -1;
}
#endif
