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



_syscall:
	ta	8
	/* FIXME handle errno */
	retl
	nop


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	b	_syscall; \
	mov	SYS_ ## name, %g1


/* functions */
/* _exit */
.global _exit
_exit:
	b	_syscall
	mov	SYS_exit, %g1
