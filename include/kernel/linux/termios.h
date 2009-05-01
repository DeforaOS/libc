/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>. */



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
