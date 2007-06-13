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



#ifndef LIBC_STRINGS_H
# define LIBC_STRINGS_H

# include <stddef.h>


/* macros */
# define bcmp(s1, s2, n)	memcmp((s1), (s2), (size_t)(n))
# define bcopy(s1, s2, n)	memmove((s1), (s2), (size_t)(n))
# define bzero(s1, n)		memset((s1), 0, (size_t)(n))
# define index(s, c)		strchr((s), (c))
# define rindex(s, c)		strrchr((s), (c))


/* functions */
int ffs(int i);
int strcasecmp(char const * s1, char const * s2);
int strncasecmp(char const * s1, char const * s2, size_t n);

#endif /* !LIBC_STRINGS_H */
