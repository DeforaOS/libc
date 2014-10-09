/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_LINUX_TERMIOS_H
# define LIBC_KERNEL_LINUX_TERMIOS_H

# define NCCS 32


/* types */
typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

struct termios
{
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t _padding1;
	cc_t c_cc[NCCS];
	speed_t _padding2[2];
};


/* constants */
# define ISIG			0000001
# define ICANON			0000002
# define INPCK			0000020
# define ISTRIP			0000040
# define INLCR			0000100
# define IGNCR			0000200
# define ICRNL			0000400
# define IXON			0002000
# define IXANY			0004000
# define IXOFF			0010000

# define VINTR			0
# define VQUIT			1
# define VERASE			2
# define VKILL			3
# define VEOF			4
# define VTIME			5
# define VMIN			6
# define VSWTC			7
# define VSTART			8
# define VSTOP			9
# define VSUSP			10
# define VEOL			11
# define VREPRINT		12
# define VDISCARD		13
# define VWERASE		14
# define VLNEXT			15
# define VEOL2			16

#endif /* !LIBC_KERNEL_LINUX_TERMIOS_H */
