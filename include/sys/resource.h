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



#ifndef LIBC_SYS_RESOURCE_H
# define LIBC_SYS_RESOURCE_H

# include "compat/sys/resource.h"


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif


/* functions */
int getpriority(int which, id_t who);
int getrlimit(int resource, struct rlimit * rlp);
int getrusage(int who, struct rusage * rup);
int setpriority(int which, id_t who, int value);
int setrlimit(int resource, const struct rlimit * rlp);

#endif /* !LIBC_SYS_RESOURCE_H */
