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



#ifndef LIBC_STDDEF_H
# define LIBC_STDDEF_H


/* types */
# ifndef ptrdiff_t
#  define ptrdiff_t ptrdiff_t
typedef long ptrdiff_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif
# ifndef wchar_t
#  define wchar_t wchar_t
typedef char wchar_t;
# endif


/* constants */
# ifndef NULL
#  define NULL ((void*)0)
# endif

#endif /* !LIBC_STDDEF_H */
