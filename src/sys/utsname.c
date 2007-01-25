/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/utsname.h"


/* uname */
#ifdef SYS_uname
syscall1(int, uname, struct utsname *, name);
#elif defined(__NetBSD__)
# include "../kernel/netbsd/sys/sysctl.h"
int uname(struct utsname * name)
{
	int mib[2];
	size_t len;

	mib[0] = CTL_KERN;
	mib[1] = KERN_OSTYPE;
	len = sizeof(name->sysname);
	if(sysctl(mib, 2, &name->sysname, &len, NULL, 0) == -1)
		return -1;
	mib[1] = KERN_HOSTNAME;
	len = sizeof(name->nodename);
	if(sysctl(mib, 2, &name->nodename, &len, NULL, 0) == -1)
		return -1;
	mib[1] = KERN_OSRELEASE;
	len = sizeof(name->release);
	if(sysctl(mib, 2, &name->release, &len, NULL, 0) == -1)
		return -1;
	mib[1] = KERN_VERSION;
	len = sizeof(name->version);
	if(sysctl(mib, 2, &name->version, &len, NULL, 0) == -1)
		return -1;
	mib[0] = CTL_HW;
	mib[1] = HW_MACHINE;
	len = sizeof(name->machine);
	if(sysctl(mib, 2, &name->machine, &len, NULL, 0) == -1)
		return -1;
	return 0;
}
#endif
