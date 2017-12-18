/* $Id$ */
/* Copyright (c) 2012-2017 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>


/* socket */
static int _socket(char const * progname, char const * title, int type)
{
	int fd;

	printf("%s: Testing %s(%s)\n", progname, "socket", title);
	if((fd = socket(AF_INET, type, 0)) < 0)
		return 2;
	if(close(fd) != 0)
		return 3;
	return 0;
}


/* socket_udp */
static int _socket_udp(char const * progname)
{
	int ret;
	int fds = -1;
	int fdc;
	struct sockaddr_in sa;
	uint16_t port;
	socklen_t salen;
	int nfds;
	fd_set rfds;
	fd_set wfds;
	struct timeval timeout;
	int res;
	char const bufc[14] = "DeforaOS libc";
	char bufs[14];

	printf("%s: Testing %s\n", progname, "UDP");
	if((fds = socket(AF_INET, SOCK_DGRAM, 0)) < 0
			|| (fdc = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		if(fds >= 0)
			close(fds);
		return 2;
	}
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(0);
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	salen = sizeof(sa);
	if(bind(fds, (struct sockaddr *)&sa, sizeof(sa)) != 0
			|| getsockname(fds, (struct sockaddr *)&sa,
				&salen) != 0)
	{
		close(fdc);
		close(fds);
		return 3;
	}
	port = ntohs(sa.sin_port);
	nfds = fdc + 1;
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(fdc, &wfds);
	for(ret = 0; ret == 0;)
	{
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		if((res = select(nfds, &rfds, &wfds, NULL, &timeout)) < 0)
			ret = 4;
		else if(res == 0)
			ret = 5;
		else if(FD_ISSET(fds, &rfds))
		{
			if((res = recvfrom(fds, bufs, sizeof(bufs), 0,
							(struct sockaddr *)&sa,
							&salen)) < 0
					|| res != sizeof(bufs))
				ret = 6;
			if(memcmp(bufs, bufc, sizeof(bufs)) != 0)
				ret = 7;
			break;
		}
		else if(FD_ISSET(fdc, &wfds))
		{
			memset(&sa, 0, sizeof(sa));
			sa.sin_family = AF_INET;
			sa.sin_port = htons(port);
			sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
			if(sendto(fdc, bufc, sizeof(bufc), 0,
						(struct sockaddr *)&sa,
						sizeof(sa)) < 0)
				ret = 8;
			FD_CLR(fdc, &wfds);
			nfds = fds + 1;
			FD_SET(fds, &rfds);
		}
		else
			ret = 9;
	}
	if(close(fdc) != 0)
		ret = 10;
	if(close(fds) != 0)
		ret = 11;
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret |= _socket(argv[0], "1/2", SOCK_DGRAM);
	ret |= _socket(argv[0], "2/2", SOCK_STREAM);
	ret |= _socket_udp(argv[0]);
	return (ret == 0) ? 0 : 2;
}
