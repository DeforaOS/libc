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
