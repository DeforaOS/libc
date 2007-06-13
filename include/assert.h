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



#ifndef LIBC_ASSERT_H
# define LIBC_ASSERT_H


# ifdef NDEBUG
#  define assert(ignore) ((void)0)
# else
#  include <stdio.h>
#  define assert(value) if(!(value)) { fprintf(stderr, "%s%s%s%d%s", \
			"assertion failed in \"", __FILE__, "\", line ", \
			__LINE__, "\n"); }
# endif

#endif /* !LIBC_ASSERT_H */
