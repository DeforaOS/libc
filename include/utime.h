/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_UTIME_H
# define LIBC_UTIME_H


/* types */
# ifndef time_t
#  define time_t time_t
typedef long long time_t;
# endif

struct utimbuf
{
	time_t actime;
	time_t modtime;
};


/* functions */
int utime(char const * filename, struct utimbuf const * times);

#endif /* !LIBC_UTIME_H */
