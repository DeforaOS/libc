/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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
#ifndef SYS_socket
# warning Unsupported platform: socket() is missing
int socketpair(int domain, int type, int protocol, int fds[2])
{
	errno = ENOSYS;
	return -1;
}
#endif
