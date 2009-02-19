/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/ioctl.h"
#include "errno.h"
#include "syscalls.h"
#include "termios.h"


/* tcgetattr */
int tcgetattr(int fildes, struct termios * tp)
{
#if defined(TCGETS)
	return ioctl(fildes, TCGETS, tp);
#elif defined(TIOCGETA)
	return ioctl(fildes, TIOCGETA, tp);
#else
	errno = ENOSYS;
	return -1;
#endif
}


/* tcsetattr */
int tcsetattr(int fildes, int action, const struct termios * tp)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}
