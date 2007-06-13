/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



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
