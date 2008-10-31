/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



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
