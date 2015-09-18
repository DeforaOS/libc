/* $Id$ */
/* Copyright (c) 2008-2015 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SETJMP_H
# define LIBC_SETJMP_H


/* types */
# if defined(__amd64__)
typedef long jmp_buf[9 + 1 + 4];
# elif defined(__i386__)
typedef long jmp_buf[6 + 1 + 4];
# else
#  warning Unsupported platform: jmp_buf and sigjmp_buf are not defined
typedef long jmp_buf[16];
# endif
typedef jmp_buf sigjmp_buf;


/* functions */
void longjmp(jmp_buf env, int val);
void siglongjmp(sigjmp_buf env, int val);
void _longjmp(jmp_buf env, int val);

int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int savemask);
int _setjmp(jmp_buf env);

#endif /* !LIBC_SETJMP_H */
