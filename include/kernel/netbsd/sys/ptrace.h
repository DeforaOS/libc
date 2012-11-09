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



#ifndef LIBC_KERNEL_NETBSD_SYS_PTRACE_H
# define LIBC_KERNEL_NETBSD_SYS_PTRACE_H


/* constants */
# define PT_TRACE_ME		0
# define PT_ATTACH		9
# define PT_DETACH		10
# define PT_SYSCALL		14

#endif /* !LIBC_KERNEL_NETBSD_SYS_PTRACE_H */
