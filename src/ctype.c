/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "ctype.h"


/* isascii */
int isascii(int c)
{
	return c >= 0 && c <= 127;
}


/* isblank */
int isblank(int c)
{
	return c == ' ' || c == '\t';
}


/* isdigit */
int isdigit(int c)
{
	return c >= '0' && c <= '9';
}


/* islower */
int islower(int c)
{
	return c >= 'a' && c <= 'z';
}


/* isprint */
int isprint(int c)
{
	return c >= ' ' && c <= '~';
}


/* isspace */
int isspace(int c)
{
	return c == ' ' || (c >= '\t' && c <= '\r');
}


/* isupper */
int isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}


/* tolower */
int tolower(int c)
{
	if(isupper(c))
		return c + 'a' - 'A';
	return c;
}


/* toupper */
int toupper(int c)
{
	if(islower(c))
		return c + 'A' - 'a';
	return c;
}
