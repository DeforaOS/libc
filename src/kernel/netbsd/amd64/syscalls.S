/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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
	jnc	.errnoret
.errno:
#ifdef PIC
	mov	errno@GOTPCREL(%rip), %rcx
	mov	%rax, (%rcx)
#else
	mov	%rax, errno
#endif
	mov	$-1, %rax
.errnoret:
	ret


/* macros */
#ifdef PIC
# define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall@PLT
#else
# define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall
#endif


/* functions */
/* _brk */
.global _brk
.type _brk,@function
_brk:
	mov	$SYS_brk, %rax
	syscall
	jc	.errno
	ret
#undef SYS_brk


/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %rax
#ifdef PIC
	jmp	_syscall@PLT
#else
	jmp	_syscall
#endif


/* execve */
.global execve
.type execve,@function
execve:
	mov	$SYS_execve, %rax
	syscall
#ifdef PIC
	mov	errno@GOTPCREL(%rip), %rcx
	mov	%rax, (%rcx)
#else
	mov	%rax, errno
#endif
	mov	$-1, %rax
	ret
#undef SYS_execve


/* lseek */
.global lseek
.type lseek,@function
lseek:
	mov	%rdx, %rcx
	mov	%rsi, %rdx
	mov	$0, %rsi
	mov	$SYS_lseek, %rax
	jmp	_syscall
#undef SYS_lseek


/* pipe */
.global pipe
.type pipe,@function
pipe:
	mov	$SYS_pipe, %rax
	syscall
	jc	.errno
	mov	%eax, (%rdi)
	mov	%edx, 4(%rdi)
	mov	$0, %rax
	ret
#undef SYS_pipe
