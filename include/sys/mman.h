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



#ifndef LIBC_SYS_MMAN_H
# define LIBC_SYS_MMAN_H

# include "compat/sys/mman.h"


/* types */
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif


/* constants */
# define MAP_FAILED	((void*)-1)


/* functions */
void * mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);

#endif /* !LIBC_SYS_MMAN_H */
