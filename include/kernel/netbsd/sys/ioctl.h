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



#ifndef LIBC_KERNEL_NETBSD_SYS_IOCTL_H
# define LIBC_KERNEL_NETBSD_SYS_IOCTL_H


/* macros */
# define _IOC(inout, group, num, len) \
		(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
# define _IO(g, n)	_IOC(IOC_VOID, (g), (n), 0)
# define _IOR(g, n, t)	_IOC(IOC_OUT, (g), (n), sizeof(t))
# define _IOW(g, n, t)	_IOC(IOC_IN, (g), (n), sizeof(t))
# define _IORW(g, n, t)	_IOC(IOC_INOUT, (g), (n), sizeof(t))


/* constants */
# define IOCPARM_MASK	0x1fff
# define IOC_VOID	(unsigned long)0x20000000
# define IOC_OUT	(unsigned long)0x40000000
# define IOC_IN		(unsigned long)0x80000000
# define IOC_DIRMASK	(unsigned long)0xe0000000

# define TIOCGETA	_IOR('t', 19, struct termios)

#endif /* !LIBC_KERNEL_NETBSD_SYS_IOCTL_H */
