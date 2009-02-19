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



#ifndef LIBDL_DLFCN_H
# define LIBDL_DLFCN_H


/* constants */
# define RTLD_NOW	0
# define RTLD_LAZY	1


/* functions */
int dlclose(void * handle);
char * dlerror(void);
void * dlopen(char const * pathname, int mode);
void * dlsym(void * handle, char const * name);

#endif /* !LIBDL_DLFCN_H */
