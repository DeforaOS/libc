/* $Id$ */
/* Copyright (c) 2022 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBSOCKET_KERNEL_DARWIN_NETINET_IN_H
# define LIBSOCKET_KERNEL_DARWIN_NETINET_IN_H


/* types */
# ifndef in_addr_t
#  define in_addr_t in_addr_t
typedef uint32_t in_addr_t;
# endif

# ifndef in_port_t
#  define in_port_t in_port_t
typedef uint16_t in_port_t;
#endif

# ifndef in_addr
#  define in_addr in_addr
struct in_addr
{
	in_addr_t s_addr;
};
# endif

# ifndef sockaddr_in
#  define sockaddr_in sockaddr_in
struct sockaddr_in
{
	unsigned char sin_len;
	sa_family_t sin_family;
	in_port_t sin_port;
	struct in_addr sin_addr;
	char _padding[8];
};
# endif

# ifndef in6_addr
#  define in6_addr in6_addr
struct in6_addr
{
	uint8_t s6_addr[16];
};
# endif

# ifndef sockaddr_in6
#  define sockaddr_in6 sockaddr_in6
struct sockaddr_in6
{
	unsigned char sin6_len;
	sa_family_t sin6_family;
	in_port_t sin6_port;
	unsigned int sin6_flowinfo;
	struct in6_addr sin6_addr;
	unsigned int sin6_scope_id;
};
# endif

#endif /* !LIBSOCKET_KERNEL_DARWIN_NETINET_IN_H */
