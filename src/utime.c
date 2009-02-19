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



#include "syscalls.h"
#include "utime.h"


/* utime */
#if !defined(SYS_utime) && defined(SYS_utimes)
# include "sys/time.h"
# include "stdlib.h"
int utime(char const * filename, struct utimbuf const * times)
{
	struct timeval tv[2];

	if(times == NULL)
		return utimes(filename, NULL);
	tv[0].tv_sec = times->actime;
	tv[0].tv_usec = 0;
	tv[1].tv_sec = times->modtime;
	tv[1].tv_usec = 0;
	return utimes(filename, tv);
}
#endif /* !SYS_utime && SYS_utimes */
