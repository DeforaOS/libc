/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_NETBSD_TERMIOS_H
# define LIBC_KERNEL_NETBSD_TERMIOS_H

# define NCCS 20


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
	cc_t c_cc[NCCS];
	int _padding[2];
};


/* constants */
# define ISIG			0x0080
# define ICANON			0x0100

# define INPCK			0x0010
# define ISTRIP			0x0020
# define INLCR			0x0040
# define IGNCR			0x0080
# define ICRNL			0x0100
# define IXON			0x0200
# define IXOFF			0x0400
# define IXANY			0x0800

# define VEOF			0
# define VEOL			1
# define VEOL2			2
# define VERASE			3
# define VWERASE		4
# define VKILL			5
# define VREPRINT		6
# define VINTR			8
# define VQUIT			9
# define VSUSP			10
# define VSTART			12
# define VSTOP			13
# define VDISCARD		15
# define VMIN			16
# define VTIME			17

#endif /* !LIBC_KERNEL_NETBSD_TERMIOS_H */
