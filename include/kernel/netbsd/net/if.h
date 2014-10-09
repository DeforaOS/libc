/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_NETBSD_NET_IF_H
# define LIBC_KERNEL_NETBSD_NET_IF_H


/* types */
# ifndef sa_family_t
#  define sa_family_t sa_family_t
typedef unsigned char sa_family_t;
# endif

# ifndef sockaddr
#  define sockaddr sockaddr
struct sockaddr
{
	unsigned char sa_len;
	sa_family_t sa_family;
	char sa_data[14];
};

# endif
# ifndef ifreq
#  define ifreq ifreq
#  define IFNAMSIZ 16
struct ifreq
{
	char ifr_name[IFNAMSIZ];
	union
	{
		struct sockaddr ifru_addr;
		short ifru_flags;
	} ifr_ifru;
};
#  define ifr_addr	ifr_ifru.ifru_addr
#  define ifr_flags	ifr_ifru.ifru_flags
# endif


/* constants */
# define SIOCGIFADDR	0xc0906921

#endif /* !LIBC_KERNEL_NETBSD_NET_IF_H */
