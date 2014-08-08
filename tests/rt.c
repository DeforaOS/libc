/* $Id$ */
/* Copyright (c) 2014 Pierre Pronchery <khorben@defora.org> */
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



#include <sched.h>
#include <stdio.h>


/* rt */
static int _rt(char const * progname)
{
	int d;

	printf("%s: Testing %s()\n", progname, "sched_get_priority_max");
	d = sched_get_priority_max(0);
	printf("%s: sched_get_priority_max() => %d\n", progname, d);
	printf("%s: Testing %s()\n", progname, "sched_get_priority_min");
	d = sched_get_priority_min(0);
	printf("%s: sched_get_priority_min() => %d\n", progname, d);
	printf("%s: Testing %s()\n", progname, "sched_yield");
	d = sched_yield();
	printf("%s: sched_yield() => %d\n", progname, d);
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _rt(argv[0]);
	return (ret == 0) ? 0 : 2;
}
