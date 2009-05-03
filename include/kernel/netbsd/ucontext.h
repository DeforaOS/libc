/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



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

#endif /* !LIBC_KERNEL_NETBSD_UCONTEXT_H */
