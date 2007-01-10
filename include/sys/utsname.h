/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_SYS_UTSNAME_H
# define LIBC_SYS_UTSNAME_H

# include "compat/sys/utsname.h"


/* types */
struct utsname
{
	char sysname[_UTSNAME_SYSNAME_SIZE];
	char nodename[_UTSNAME_NODENAME_SIZE];
	char release[_UTSNAME_RELEASE_SIZE];
	char version[_UTSNAME_VERSION_SIZE];
	char machine[_UTSNAME_MACHINE_SIZE];
	char _padding[_UTSNAME_PADDING_SIZE];
};


/* functions */
int uname(struct utsname * name);

#endif /* LIBC_SYS_UTSNAME_H */
