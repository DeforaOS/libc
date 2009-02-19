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



#include "string.h"
#include "libgen.h"


/* basename */
char * basename(char * path)
{
	int i;

	if(path == NULL || path[0] == '\0')
		return "";
	for(i = strlen(path) - 1; i >= 0 && path[i] == '/'; i--);
	if(i == -1)
		return "/";
	for(path[i+1] = '\0'; i >= 0 && path[i] != '/'; i--);
	return &path[i+1];
}


/* dirname */
char * dirname(char * path)
{
	int i;

	if(path == NULL || path[0] == '\0')
		return ".";
	for(i = strlen(path) - 1; i >= 0 && path[i] == '/'; i--);
	if(i == -1)
		return "/";
	for(i--; i >= 0 && path[i] != '/'; i--);
	if(i == -1)
		return ".";
	path[i] = '\0';
	for(i--; i >= 0 && path[i] == '/'; i--);
	if(i == -1)
		return "/";
	path[i+1] = '\0';
	return path;
}
