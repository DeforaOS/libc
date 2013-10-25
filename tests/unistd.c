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



#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "../src/unistd.c"


/* fork */
static int _fork(char const * progname)
{
	pid_t pid;
	int res = 42;
	pid_t p;
	int status;

	printf("%s: Testing fork()\n", progname);
	if((pid = fork()) == -1)
		return -1;
	if(pid == 0)
		/* child process */
		_exit(res);
	/* parent process */
	for(;;)
	{
		if((p = waitpid(pid, &status, 0)) == -1)
			break;
		if(p != pid)
			continue;
		if(WIFEXITED(status) && WEXITSTATUS(status) == res)
			return 0;
	}
	return -1;
}


/* sleep */
static int _sleep(char const * progname)
{
	time_t before;
	time_t after;

	printf("%s: Testing sleep()\n", progname);
	before = time(NULL);
	sleep(1);
	after = time(NULL);
	return (after == before + 1) ? 0 : -1;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _fork(argv[0]);
	ret += _sleep(argv[0]);
	return (ret == 0) ? 0 : 2;
}
