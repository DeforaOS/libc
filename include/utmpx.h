/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
