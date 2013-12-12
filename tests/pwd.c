/* $Id$ */
/* Copyright (c) 2013 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <pwd.h>


/* getpwent */
static int _getpwent(char const * progname)
{
	struct passwd * pw;

	setpwent();
	printf("%s: Testing getpwent()\n", progname);
	while((pw = getpwent()) != NULL)
		printf("%s: Testing getpwent(): %s (%u:%u) %s\n", progname,
				pw->pw_name, pw->pw_uid, pw->pw_gid,
				pw->pw_shell);
	endpwent();
	return 0;
}


/* getpwnam */
static int _getpwnam(char const * progname)
{
	struct passwd * pw;

	printf("%s: Testing getpwnam()\n", progname);
	if((pw = getpwnam("root")) == NULL
			|| pw->pw_uid != 0)
		return -1;
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int res = 0;

	res += _getpwnam(argv[0]);
	res += _getpwent(argv[0]);
	return (res == 0) ? 0 : 2;
}
