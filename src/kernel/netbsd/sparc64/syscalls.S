/* $Id$ */
/* Copyright (c) 2008-2014 Pierre Pronchery <khorben@defora.org> */
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



#include "../sparc/syscalls.S"


/* functions */
/* lseek */
.global lseek
.type lseek,@function
lseek:
	mov	%o2, %o3
	mov	%o1, %o2
	mov	%g0, %o1
	b	_syscall
	mov	SYS_lseek, %g1
#undef SYS_lseek


/* mmap */
.global mmap
.type mmap,@function
mmap:
	save	%sp, -208, %sp
	mov	%i0, %o0
	mov	%i1, %o1
	mov	%i2, %o2
	mov	%i3, %o3
	mov	%i4, %o4
	mov	0, %o5
	stx	%i5, [%sp + 0x8af]
	mov	SYS_mmap, %g1
	ta 0
	bcc	.merrnoret
	nop
	set	errno, %g1
	st	%o0, [%g1]
	set	0xffffffff, %o0
.merrnoret:
	mov	%o0, %i0
	ret
	restore
#undef SYS_mmap
