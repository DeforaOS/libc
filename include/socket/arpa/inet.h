/* $Id$ */
/* Copyright (c) 2008-2015 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_ARPA_INET_H
# define LIBSOCKET_ARPA_INET_H

# include <netinet/in.h>


/* types */
#ifndef uint16_t
# define uint16_t uint16_t
typedef unsigned short uint16_t;
#endif
#ifndef uint32_t
# define uint32_t uint32_t
typedef unsigned int uint32_t;
#endif


/* macros */
# define htonl(host32)	htonl(host32)
# define htons(host16)	htons(host16)
# define ntohl(net32)	ntohl(net32)
# define ntohs(net16)	ntohs(net16)


/* functions */
uint32_t htonl(uint32_t host32);
uint16_t htons(uint16_t host16);
in_addr_t inet_addr(const char * cp);
int inet_aton(const char * cp, struct in_addr *addr);
char * inet_ntoa(struct in_addr in);
char const * inet_ntop(int family, const void * src, char * dst,
		socklen_t size);
uint32_t ntohl(uint32_t net32);
uint16_t ntohs(uint16_t net16);

#endif /* !LIBSOCKET_ARPA_INET_H */
