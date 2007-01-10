/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_UTMPX_H
# define LIBC_UTMPX_H

# define _UTMPX_USER_SIZE	32
# define _UTMPX_ID_SIZE		4
# define _UTMPX_LINE_SIZE	32


/* types */
# ifndef pid_t
#  define pid_t pid_t
typedef int pid_t;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
# endif
#ifndef timeval
# define timeval timeval
struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};
#endif

struct utmpx
{
	char ut_user[_UTMPX_USER_SIZE];
	char ut_id[_UTMPX_ID_SIZE];
	char ut_line[_UTMPX_LINE_SIZE];
	pid_t ut_pid;
	short ut_type;
	struct timeval ut_tv;
};


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
