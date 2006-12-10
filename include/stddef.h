/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_STDDEF_H
# define LIBC_STDDEF_H


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif
typedef char wchar_t;


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

#endif /* !LIBC_STDDEF_H */
