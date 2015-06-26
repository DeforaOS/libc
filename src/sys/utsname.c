/* $Id$ */
/* Copyright (c) 2005-2015 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#include "sys/sysctl.h"
#include "stddef.h"
#include "errno.h"
#include "../syscalls.h"
#include "sys/utsname.h"


/* functions */
/* uname */
#if defined(SYS_sysctl) && defined(CTL_KERN) && defined(KERN_OSTYPE) \
	&& defined(KERN_HOSTNAME) && defined(KERN_OSRELEASE) \
	&& defined(KERN_VERSION) && defined(CTL_HW) && defined(HW_MACHINE)
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
#elif !defined(SYS_uname)
# warning Unsupported platform: uname() is missing
int uname(struct utsname * name)
{
	errno = ENOSYS;
	return -1;
}
#endif
