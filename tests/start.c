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



#include <stdio.h>
#include <string.h>
extern char ** environ;


/* main */
int main(int argc, char * argv[], char * envp[])
{
	int ret = 0;
	int i;
	char const * sep;

	printf("%s: %s\n", argv[0], "Testing arguments:");
	if(argv == NULL)
		ret |= 1;
	else if(strcmp(argv[0], "./start") != 0)
		ret |= 2;
	else if(strcmp(argv[1], "argv1") != 0)
		ret |= 4;
	else if(strcmp(argv[2], "argv2") != 0)
		ret |= 8;
	else if(argv[3] != NULL)
		ret |= 16;
	else
	{
		for(i = 0, sep = ""; i < argc; i++)
		{
			printf("%s%d: %s", sep, i, argv[i]);
			sep = ", ";
		}
		putchar('\n');
	}
	printf("%s: %s\n", argv[0], "Testing the environment");
	if(envp == NULL || environ == NULL)
		ret |= 32;
	else
		for(i = 0; envp[i] != NULL && environ[i] != NULL; i++)
			if(strcmp(envp[i], environ[i]) != 0)
				ret |= 64;
	return ret;
}
