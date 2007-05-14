/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_PWD_H
# define LIBC_PWD_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
# endif

struct passwd
{
	char * pw_name;
	uid_t pw_uid;
	gid_t pw_gid;
	char * pw_dir;
	char * pw_shell;
};


/* functions */
struct passwd * getpwnam(char const * name);
struct passwd * getpwuid(uid_t uid);

struct passwd * getpwent(void);
void endpwent(void);
void setpwent(void);

#endif /* !LIBC_PWD_H */
