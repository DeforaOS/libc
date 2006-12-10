/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_UTSNAME_H
# define LIBC_SYS_UTSNAME_H


/* types */
struct utsname
{
	/* FIXME these are of fixed size */
	char * sysname;
	char * nodename;
	char * release;
	char * version;
	char * machine;
};


/* functions */
int uname(struct utsname * name);

#endif /* LIBC_SYS_UTSNAME_H */
