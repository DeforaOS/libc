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



#ifndef LIBC_KERNEL_NETBSD_SYS_VT_H
# define LIBC_KERNEL_NETBSD_SYS_VT_H


/* types */
struct vt_mode
{
	char mode;
	char waitv;
	short relsig;
	short acqsig;
	short frsig;
};

typedef struct vt_mode vtmode_t;

struct vt_stat
{
	unsigned short v_active;
	unsigned short v_signal;
	unsigned short v_state;
};


/* constants */
# define VT_FALSE		0
# define VT_TRUE		1
# define VT_ACKACQ		2

# define VT_PROCESS		1

# define VT_ACTIVATE		0x20007605
# define VT_GETACTIVE		0x40047607
# define VT_GETMODE		0x40087603
# define VT_GETSTATE		0x40067664
# define VT_RELDISP		0x20007604
# define VT_SETMODE		0x80087602
# define VT_OPENQRY		0x40047601
# define VT_WAITACTIVE		0x20007606

#endif /* !LIBC_KERNEL_NETBSD_SYS_VT_H */
