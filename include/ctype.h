/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_CTYPE_H
# define LIBC_CTYPE_H


/* function prototypes */
# define isalnum(c) (isalpha(c) || isdigit(c))
# define isalpha(c) (islower(c) || isupper(c))
int isascii(int c);
int isblank(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
# define ispunct(c) (isprint(c) && (!(isspace(c) || isalnum(c))))
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int toascii(int c);
int tolower(int c);
# define _tolower(c) (c + 'a' - 'A')
int toupper(int c);
# define _toupper(c) (c + 'A' - 'a')

#endif /* !LIBC_CTYPE_H */
