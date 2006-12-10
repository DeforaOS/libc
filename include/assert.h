/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



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
