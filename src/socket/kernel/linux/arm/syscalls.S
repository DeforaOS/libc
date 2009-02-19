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
/* FIXME not tested */



_syscall:
	swi
	/* FIXME implement
	bcc	.errnoret
	set	errno, %g1
	st	%o0, [%g1]
	set	-1, %o0
.errnoret: */
	mov	%pc, %lr


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	ldr	%r0, =SYS_socketcall; \
	ldr	%r1, =SYS_ ## name; \
	b	_syscall;
