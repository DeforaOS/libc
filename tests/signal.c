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



#include <unistd.h>
#include <signal.h>
#include <stdio.h>


/* signal */
/* private */
/* variables */
static int _ret;


/* prototypes */
static void _on_sigusr1(int signal);
static void _on_sigusr2(int signal);


/* functions */
/* on_sigusr1 */
static void _on_sigusr1(int signal)
{
	if(_ret == 3)
		_ret = 0;
}


/* on_sigusr2 */
static void _on_sigusr2(int signal)
{
	if(_ret == 2)
		_ret = 3;
}


/* public */
/* functions */
int main(int argc, char * argv[])
{
	_ret = 2;
	printf("%s: %s", argv[0], "Testing signal()\n");
	signal(SIGUSR1, _on_sigusr1);
	signal(SIGUSR2, _on_sigusr2);
	printf("%s: %s", argv[0], "Testing kill()\n");
	kill(getpid(), SIGUSR2);
	kill(getpid(), SIGUSR1);
	return _ret;
}
