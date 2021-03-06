/* $Id$ */
/* Copyright (c) 2005-2017 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYS_MMAN_H
# define LIBC_SYS_MMAN_H

# include "../compat.h"


/* types */
# ifndef mode_t
#  define mode_t mode_t
typedef __mode_t mode_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef __off_t off_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef __size_t size_t;
# endif

# include "../compat/sys/mman.h"


/* constants */
# define MAP_FAILED	((void *)-1)


/* functions */
int mlock(const void * addr, size_t length);
void * mmap(void * addr, size_t length, int prot, int flags, int fd,
		off_t offset);
int mprotect(void * addr, size_t length, int prot);
int munlock(const void * addr, size_t length);
int munmap(void * addr, size_t length);

#endif /* !LIBC_SYS_MMAN_H */
