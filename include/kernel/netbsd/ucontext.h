/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_NETBSD_UCONTEXT_H
# define LIBC_KERNEL_NETBSD_UCONTEXT_H


/* types */
# ifndef sigset_t
#  define sigset_t sigset_t
typedef struct { unsigned int bits[4]; } sigset_t;
# endif

# ifndef stack_t
#  define stack_t stack_t
typedef struct {
	void * ss_sp;
	unsigned long ss_size;
	int ss_flags;
} stack_t;
# endif

# ifndef ucontext_t
#  define ucontext_t ucontext_t
typedef struct _ucontext_t
{
	unsigned int uc_flags;
	struct _ucontext_t * uc_link;
	sigset_t uc_sigmask;
	stack_t uc_stack;
#  if 0 /* FIXME implement */
	mcontext_t uc_mcontext;
#  endif
} ucontext_t;
# endif

#endif /* !LIBC_KERNEL_NETBSD_UCONTEXT_H */
