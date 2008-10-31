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



#ifndef LIBC_UTMPX_H
# define LIBC_UTMPX_H

# include "compat/sys/time.h"
# include "compat/utmpx.h"


/* constants */
#define EMPTY		0
#define BOOT_TIME	2
#define OLD_TIME	3
#define NEW_TIME	4
#define INIT_PROCESS	5
#define LOGIN_PROCESS	6
#define USER_PROCESS	7
#define DEAD_PROCESS	8


/* functions */
void endutxent(void);
struct utmpx * getutxent(void);
struct utmpx * getutxid(struct utmpx const * ut);
struct utmpx * getutxline(struct utmpx const * ut);
struct utmpx * pututxline(struct utmpx const * ut);
void setutxent(void);

#endif /* !LIBC_UTMPX_H */
