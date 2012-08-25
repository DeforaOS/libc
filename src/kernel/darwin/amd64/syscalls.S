/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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
	mov	%rcx, %r10
	syscall
	jnc	_syscall_return
.errno:
#ifdef PIC
	mov	errno@GOTPCREL(%rip), %rcx
	mov	%rax, (%rcx)
#else
	mov	%rax, errno
#endif
	mov	$-1, %rax
_syscall_return:
	ret


/* macros */
#ifndef SYSCALL
# define SYSCALL(name) \
name:; \
	mov	$SYS_ ## name, %rax; \
	add	$0x2000000, %rax; \
	jmp	_syscall
#endif


/* functions */
/* _exit */
_exit:
	mov	$SYS_exit, %rax
	jmp	_syscall
