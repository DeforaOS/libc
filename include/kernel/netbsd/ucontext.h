/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



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
