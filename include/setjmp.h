/* $Id$ */
/* Copyright (c) 2008-2012 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SETJMP_H
# define LIBC_SETJMP_H


/* types */
# if defined(__amd64__)
typedef long jmp_buf[8];
# elif defined(__i386__)
typedef long jmp_buf[6];
# else
#  warning Unsupported platform: jmp_buf is not defined
# endif

# if defined(__amd64__)
/* XXX extra data */
typedef long sigjmp_buf[8];
# elif defined(__i386__)
/* XXX extra data */
typedef long sigjmp_buf[6];
# else
#  warning Unsupported platform: sigjmp_buf is not defined
# endif


/* functions */
void longjmp(jmp_buf env, int);
void siglongjmp(sigjmp_buf env, int);
void _longjmp(jmp_buf env, int);

int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int);
int _setjmp(jmp_buf env);

#endif /* !LIBC_SETJMP_H */
