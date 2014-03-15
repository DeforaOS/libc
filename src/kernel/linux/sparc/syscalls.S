/* $Id$ */
/* Copyright (c) 2007-2014 Pierre Pronchery <khorben@defora.org> */
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



_syscall0:
	jmp	.trap
	nop

_syscall1:
	mov	%i1, %o0
	jmp	.trap
	nop

_syscall2:
	mov	%i2, %o1
	jmp	.trap
	nop

_syscall3:
	mov	%i3, %o2
	jmp	.trap
	nop

_syscall4:
	mov	%i4, %o3
	jmp	.trap
	nop

_syscall5:
	mov	%i5, %o4
	jmp	.trap
	nop

_syscall6:
	/* FIXME how to get the last arg? */

.trap:
	mov	%i0, %g1	/* syscall number */
	ta	8
	/* FIXME errno */
	ret
	nop
