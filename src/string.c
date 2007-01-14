/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "stdlib.h"
#include "string.h"
#include "errno.h"


/* FIXME */
#define max(a, b) ((a) > (b) ? (a) : (b))


/* memchr */
void * memchr(void const * s, int c, size_t n)
{
	unsigned char const * ls = s;
	unsigned char lc = c;

	while(n-- && *ls != lc)
		ls++;
	return n != 0 ? ls : NULL;
}


/* memcmp */
int memcmp(void const * s1, void const * s2, size_t n)
{
	unsigned char const * u1 = s1;
	unsigned char const * u2 = s2;

	while(n-- && *u1 == *u2)
	{
		u1++;
		u2++;
	}
	return *u1 - *u2;
}


/* memcpy */
void * memcpy(void * dest, void const * src, size_t n)
{
	int * d;
	int const * s;
	
	d = dest;
	s = src;
	while(n--)
		*d++ = *s++;
	return dest;
}


/* memmove */
void * memmove(void * dest, void const * src, size_t n)
{
	if(n == 0 || dest == src)
		return dest;
	if(dest + n < src || dest > src + n)
		return memcpy(dest, src, n);
	if(src < dest)
	{
		int * d;
		int const * s;

		d = dest + n - 1;
		s = src + n - 1;
		while(n--)
			*d-- = *s--;
		return dest;
	}
	return memcpy(dest, src, n);
}


/* memset */
void * memset(void * dest, int c, size_t n)
{
	unsigned char * d;

	d = dest;
	while(n--)
		*d++ = c;
	return dest;
}


/* strcat */
char * strcat(char * dest, char const * src)
{
	char * res;
	
	res = dest;
	while(*dest++);
	while(*src)
		*dest++ = *src++;
	*dest = '\0';
	return res;
}


/* strchr */
char * strchr(char const * s, int c)
{
	unsigned char u = c;

	for(; *s != '\0'; s++)
		if(*s == u)
			return s;
	return u == 0 ? s : NULL;
}


/* strcmp */
int strcmp(char const * s1, char const * s2)
{
	unsigned char const * u1;
	unsigned char const * u2;

	u1 = s1;
	u2 = s2;
	while(*u1 && *u2 && *u1 == *u2)
	{
		u1++;
		u2++;
	}
	return *u1 - *u2;
}


/* strcpy */
char * strcpy(char * dest, char const * src)
{
	char * res;

	res = dest;
	while(*src)
		*dest++ = *src++;
	return res;
}


/* strcspn */
size_t strcspn(char const * s1, char const * s2)
{
	unsigned int ret = 0;
	unsigned int len = 0;
	unsigned int i;

	for(; *s1 != '\0'; s1++)
	{
		len++;
		for(i = 0; s2[i] != '\0'; i++)
			if(*s1 == s2[i])
			{
				ret = max(ret, len);
				len = -1;
				break;
			}
	}
	return ret;
}


/* strdup */
char * strdup(char const * s)
{
	size_t len;
	char * str;

	len = strlen(s) + 1;
	if((str = malloc(sizeof(char) * len)) == NULL)
		return NULL;
	strcpy(str, s);
	return str;
}


/* strerror */
char * strerror(int errnum)
{
	static char einval[] = "Invalid argument";
	struct
	{
		int errno;
		char * errmsg;
	} err[] =
	{
		{ 0,		"Success"		},
		{ E2BIG,	"Argument list too long"},
		{ EACCES,	"Permission denied"	},
		{ EINVAL,	einval			},
		{ ENOMEM,	"Not enough memory"	},
		{ ENOSYS,	"Not implemented"	},
		{ EXDEV,	"Cross-device link"	}
	};
#define EXLAST EXDEV
	unsigned int i;

	for(i = 0; err[i].errno != EXLAST; i++)
		if(err[i].errno == errnum)
			return err[i].errmsg;
	return einval;
}


/* strlen */
size_t strlen(char const * s)
{
	size_t len = 0;

	while(*s++)
		len++;
	return len;
}


/* strncat */
char * strncat(char * dest, char const * src, size_t n)
{
	char * res;

	res = dest;
	while(*dest++);
	while(n-- && *src)
		*dest++ = *src++;
	*dest = '\0';
	return res;
}


/* strncmp */
int strncmp(char const * s1, char const * s2, size_t n)
{
	unsigned char const * u1;
	unsigned char const * u2;

	u1 = s1;
	u2 = s2;
	while(n-- && *u1 && *u2 && *u1 == *u2)
	{
		*u1++;
		*u2++;
	}
	return *u1 - *u2;
}


/* strncpy */
char * strncpy(char * dest, char const * src, size_t n)
{
	char * res;

	res = dest;
	while(n-- && *src)
		*dest++ = *src++;
	return res;
}


/* strrchr */
char * strrchr(char const * s, int c)
{
	unsigned char u = c;
	char const * last = NULL;

	for(; *s != '\0'; s++)
		if(*s == c)
			last = s;
	return u == 0 ? s : last;
}


/* strstr */
char * strstr(char const * s1, char const * s2)
{
	unsigned int len1 = strlen(s1);
	unsigned int len2 = strlen(s2);
	unsigned int i;

	if(len2 == 0)
		return s1;
	if(len1 < len2)
		return NULL;
	for(i = 0; i < len1 - len2; i++)
		if(strncmp(&s1[i], s2, len2) == 0)
			return s1 + i;
	return NULL;
}


/* strtok */
char * strtok(char * s1, char const * s2)
{
	static char * s = NULL;
	unsigned int i;
	unsigned int j;

	if(s1 != NULL)
		s = s1;
	for(i = 0; s[i] != '\0'; i++)
	{
		for(j = 0; s2[j] != '\0'; j++)
		{
			if(s[i] == s2[j])
			{
				s+=(i + 1);
				return s - i - 1;
			}
		}
	}
	return NULL;
}
