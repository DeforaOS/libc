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



_syscall:
	ta	0
	bcc	.errnoret
	nop
	set	errno, %g1
	st	%o0, [%g1]
	set	0xffffffff, %o0
.errnoret:
	retl
	nop


/* macros */
#define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	b	_syscall; \
	mov	SYS_ ## name, %g1


/* functions */
/* _brk */
.global _brk
.type _brk,@function
_brk:
	b	_syscall
	mov	SYS_brk, %g1
#undef SYS_brk


/* _exit */
.global _exit
.type _exit,@function
_exit:
	b	_syscall
	mov	SYS_exit, %g1
