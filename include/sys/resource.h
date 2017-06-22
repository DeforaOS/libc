/* $Id$ */
/* Copyright (c) 2007-2016 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYS_RESOURCE_H
# define LIBC_SYS_RESOURCE_H

# include "../compat.h"


/* types */
# ifndef id_t
#  define id_t id_t
typedef __id_t id_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef __time_t time_t;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef __suseconds_t suseconds_t;
# endif

# include "../compat/sys/resource.h"


/* constants */
# define RLIM_INFINITY		(~0)
# define RLIMIT_SAVED_CUR	RLIM_INFINITY
# define RLIMIT_SAVED_MAX	RLIM_INFINITY


/* functions */
int getpriority(int which, id_t who);
int getrlimit(int resource, struct rlimit * rlp);
int getrusage(int who, struct rusage * rup);
int setpriority(int which, id_t who, int value);
int setrlimit(int resource, const struct rlimit * rlp);

#endif /* !LIBC_SYS_RESOURCE_H */
