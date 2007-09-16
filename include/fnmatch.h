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



#ifndef LIBC_FNMATCH_H
# define LIBC_FNMATCH_H


/* constants */
# define FNM_NOMATCH	1
# define FNM_NOSYS	2

# define FNM_PATHNAME	0x1
# define FNM_PERIOD	0x2
# define FNM_NOESCAPE	0x4


/* functions */
int fnmatch(char const * pattern, char const * string, int flags);

#endif /* !LIBC_FNMATCH_H */
