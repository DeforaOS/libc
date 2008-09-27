/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_CTYPE_H
# define LIBC_CTYPE_H


/* function prototypes */
# define isalnum(c) (isalpha(c) || isdigit(c))
# define isalpha(c) (islower(c) || isupper(c))
int isascii(int c);
int isblank(int c);
int isdigit(int c);
int islower(int c);
int isprint(int c);
# define ispunct(c) (isprint(c) && (!(isspace(c) || isalnum(c))))
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int tolower(int c);
# define _tolower(c) (c + 'a' - 'A')
int toupper(int c);
# define _toupper(c) (c + 'A' - 'a')

#endif /* !LIBC_CTYPE_H */
