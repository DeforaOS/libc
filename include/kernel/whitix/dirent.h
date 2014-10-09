/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_WHITIX_DIRENT_H
# define LIBC_KERNEL_WHITIX_DIRENT_H


/* FIXME nothing checked */
/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned long long ino_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef unsigned int off_t;
# endif

# pragma pack(1)
struct dirent
{
# ifdef __arm__
	unsigned long d_ino;
	unsigned long d_off;
	unsigned char d_reclen;
	unsigned char d_type;
	char d_name[256]; /* NAME_MAX + 1 */
# else
	ino_t d_ino;
	off_t _padding;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[256]; /* NAME_MAX + 1 */
# endif
};
# pragma pack()

#endif /* !LIBC_KERNEL_WHITIX_DIRENT_H */
