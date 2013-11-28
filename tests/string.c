/* $Id$ */
/* Copyright (c) 2012-2013 Pierre Pronchery <khorben@defora.org> */
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



#include <string.h>
#include <stdio.h>
#include <errno.h>


/* memchr */
static int _memchr(void)
{
	int ret = 0;
	char const search[] = "sear\xff\xfe\x7f\x7e\x00\x01ch";
	size_t i;
	void * p;

	for(i = 0; i < sizeof(search); i++)
	{
		p = memchr(search, search[i], sizeof(search));
		if(p == NULL || strcmp(p, &search[i]) != 0)
			ret += 1;
	}
	ret += memchr(search, 'z', sizeof(search)) == NULL ? 0 : 1;
	return ret;
}


/* strerror */
static void _strerror(char const * progname)
{
	int errors[] =
	{
		0,
		E2BIG,
		EACCES,
		EAGAIN,
		EBADF,
		EBUSY,
		ECHILD,
#ifdef EDOM
		EDOM,
#endif
		EEXIST,
		EFAULT,
		EINTR,
		EINVAL,
		EIO,
		EISDIR,
		ENODEV,
		ENOENT,
		ENOEXEC,
		ENOMEM,
#ifdef ENOSPC
		ENOSPC,
#endif
		ENOSYS,
		ENOTDIR,
		ENOTSUP,
		ENOTTY,
		ENXIO,
		EPERM,
		EPIPE,
		ERANGE,
		EROFS,
#ifdef ESPIPE
		ESPIPE,
#endif
#ifdef ESRCH
		ESRCH,
#endif
		ETIMEDOUT,
		EXDEV
	};
	size_t i;

	for(i = 0; i < sizeof(errors) / sizeof(*errors); i++)
		printf("%s: Testing %s: \"%s\" (%u)\n", progname,
				"strerror()", strerror(errors[i]), errors[i]);
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _memchr();
	_strerror(argv[0]);
	return (ret == 0) ? 0 : 2;
}
