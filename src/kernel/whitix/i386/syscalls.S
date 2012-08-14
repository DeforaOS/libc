/* $Id$ */
/* Copyright (c) 2009-2012 Pierre Pronchery <khorben@defora.org> */
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
	mov	%ebp, %edx
	add	$4, %edx
	int	$0x30
.errno:
	cmp	$0, %eax
	jge	.errnoret
	neg	%eax
	mov	%eax, errno
	mov	$-1, %eax
.errnoret:
	ret


/* macros */
#define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %eax; \
	mov	$SYSL_ ## name, %ecx; \
	jmp	_syscall


/* functions */
/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %eax
	mov	$SYSL_exit, %ecx
	jmp	_syscall


/* _sbrk */
.global _sbrk
.type _sbrk,@function
_sbrk:
	mov	$SYS_sbrk, %eax
	mov	$SYSL_sbrk, %ecx
	jmp	_syscall
#undef SYS_sbrk
