/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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
