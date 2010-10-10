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



_syscall:
	svc	0x00000000
	mov	%r7, %ip
	cmp	%r0, #0
	bge	.errnoret
	mov	%r1, #0
	sub	%r0, %r1, %r0
	ldr	%r1, =errno
	str	%r0, [%r1]
	mov	%r0, #-1
.errnoret:
	mov	%pc, %lr


/* macros */
#define SYSCALL(name) \
.global name; \
.type name,%function; \
name:; \
	mov	%ip, %r7; \
	ldr	%r7, =SYS_ ## name; \
	b	_syscall;


/* functions */
/* _brk */
.global _brk
_brk:
	mov	%ip, %r7
	ldr	%r7, =SYS_brk
	b	_syscall
#undef SYS_brk


/* _exit */
.global _exit
_exit:
	mov	%ip, %r7
	ldr	%r7, =SYS_exit
	b	_syscall


/* FIXME mount needs to be implemented too (wrong order of arguments) */
