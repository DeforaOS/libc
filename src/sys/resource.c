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



#include "../syscalls.h"
#include "sys/resource.h"


/* functions */
/* getpriority */
#ifndef SYS_getpriority
# warning Unsupported platform: getpriority() is missing
#endif


/* getrlimit */
#ifndef SYS_getrlimit
# warning Unsupported platform: getrlimit() is missing
#endif


/* getrusage */
#ifndef SYS_getrusage
# warning Unsupported platform: getrusage() is missing
#endif


/* setpriority */
#ifndef SYS_setpriority
# warning Unsupported platform: setpriority() is missing
#endif


/* setrlimit */
#ifndef SYS_setrlimit
# warning Unsupported platform: setrlimit() is missing
#endif
