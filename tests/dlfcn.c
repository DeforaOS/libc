/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include "../src/dl/dlfcn.c"


/* dlfcn */
/* private */
/* functions */
static int _dlfcn(char const * progname, char const * soname)
{
	int ret = 0;
	void * handle;
	int * p;
	pid_t (*g)(void);

	printf("%s: Testing %s\n", progname, "dlopen()");
	if((handle = dlopen(soname, RTLD_LAZY)) == NULL)
	{
		printf("%s: %s\n", progname, dlerror());
		return -1;
	}
	/* checking the value of a known variable */
	printf("%s: Testing %s\n", progname, "dlsym() (1/2)");
	if((p = dlsym(handle, "errno")) == NULL)
	{
		printf("%s: %s\n", progname, dlerror());
		ret++;
	}
	else if(*p != 0)
	{
		printf("%s: errno: Wrong value (%d)\n", progname, *p);
		ret++;
	}
	/* calling a simple syscall */
	printf("%s: Testing %s\n", progname, "dlsym() (2/2)");
	if((g = dlsym(handle, "getpid")) == NULL)
	{
		printf("%s: %s\n", progname, dlerror());
		ret++;
	}
	else if(getpid() != g())
	{
		printf("%s: getpid(): Wrong value\n", progname);
		ret++;
	}
	dlclose(handle);
	return ret;
}


/* public */
/* functions */
int main(int argc, char * argv[])
{
	char const * soname = argv[0];

	if(argc == 2)
		soname = argv[1];
	return (_dlfcn(argv[0], soname) == 0) ? 0 : 2;
}
