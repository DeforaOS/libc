/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SETJMP_H
# define LIBC_SETJMP_H


/* types */
# if defined(__i386__)
typedef long jmp_buf[6];
# elif defined(__amd64__)
typedef long jmp_buf[8];
# else
#  warning Unsupported platform
typedef struct _jmp_buf
{
} jmp_buf;
# endif


/* functions */
void longjmp(jmp_buf, int);
void siglongjmp(jmp_buf, int);
void _longjmp(jmp_buf, int);

int setjmp(jmp_buf);
int sigsetjmp(jmp_buf, int);
int _setjmp(jmp_buf);

#endif /* !LIBC_SETJMP_H */
