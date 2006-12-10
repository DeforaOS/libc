/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_GRP_H
# define LIBC_GRP_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef int id_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
struct group
{
	char * gr_name;
	gid_t gr_gid;
	char ** gr_mem;
};


/* functions */
struct group * getgrgid(gid_t gid);
struct group * getgrnam(char const * name);

#endif /* !LIBC_GRP_H */
