/* $Id$ */
/* Copyright (c) 2004-2019 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"

#ifndef max
# define max(a, b) ((a) > (b) ? (a) : (b))
#endif


/* memchr */
void * memchr(void const * s, int c, size_t n)
{
	unsigned char const * ls;
	unsigned char lc = c;

	for(ls = s; n--; ls++)
		if(*ls == lc)
			return (void *)ls;
	return NULL;
}


/* memcmp */
int memcmp(void const * s1, void const * s2, size_t n)
{
	unsigned char const * u1 = s1;
	unsigned char const * u2 = s2;

	if(n == 0)
		return 0;
	while(--n && *u1 == *u2)
	{
		u1++;
		u2++;
	}
	return *u1 - *u2;
}


/* memcpy */
void * memcpy(void * dest, void const * src, size_t n)
{
	char * d = dest;
	char const * s = src;

	while(n--)
		*d++ = *s++;
	return dest;
}


/* memmove */
void * memmove(void * dest, void const * src, size_t n)
{
	char * d = dest;
	char const * s = src;

	if(n == 0 || dest == src)
		return dest;
	if(d + n < s || d > s + n)
		return memcpy(dest, src, n);
	if(s < d)
	{
		d += n - 1;
		s += n - 1;
		while(n--)
			*d-- = *s--;
		return dest;
	}
	return memcpy(dest, src, n);
}


/* memset */
void * memset(void * dest, int c, size_t n)
{
	unsigned char * d = dest;

	while(n--)
		*d++ = c;
	return dest;
}


/* strcat */
char * strcat(char * dest, char const * src)
{
	char * ret = dest;
	
	for(; *dest; dest++);
	while(*src)
		*(dest++) = *(src++);
	*dest = '\0';
	return ret;
}


/* strchr */
char * strchr(char const * s, int c)
{
	unsigned char const * ls;
	unsigned char lc = c;

	for(ls = (unsigned char const *)s; *ls != '\0'; ls++)
		if(*ls == lc)
			return (char *)ls;
	return (lc == '\0') ? (char *)ls : NULL;
}


/* strcmp */
int strcmp(char const * s1, char const * s2)
{
	unsigned char const * u1;
	unsigned char const * u2;

	u1 = (unsigned char const *)s1;
	u2 = (unsigned char const *)s2;
	while(*u1 && *u2 && *u1 == *u2)
	{
		u1++;
		u2++;
	}
	return *u1 - *u2;
}


/* strcoll */
int strcoll(char const * s1, char const * s2)
{
	return strcmp(s1, s2);
}


/* strcpy */
char * strcpy(char * dest, char const * src)
{
	char * ret = dest;

	while((*dest++ = *src++));
	return ret;
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

	if((len = strlen(s) + 1) == 0)
	{
		errno = ENOMEM;
		return NULL;
	}
	if((str = malloc(sizeof(char) * len)) == NULL)
		return NULL;
	strcpy(str, s);
	return str;
}


/* strerror */
char * strerror(int errnum)
{
	static char ret[256];

	if(strerror_r(errnum, ret, sizeof(ret)) != 0)
		errno = EINVAL;
	return ret;
}


/* strerror_r */
int strerror_r(int errnum, char * strerrbuf, size_t buflen)
{
	static const struct
	{
		const int errnum;
		const char * errmsg;
	} err[] =
	{
		{ 0,		"Success"				},
		{ E2BIG,	"Argument list too long"		},
		{ EACCES,	"Permission denied"			},
		{ EAGAIN,	"Resource temporarily unavailable"	},
		{ EBADF,	"Bad file descriptor"			},
		{ EBUSY,	"Device or resource busy"		},
		{ ECHILD,	"No child processes"			},
		{ EEXIST,	"File exists"				},
		{ EFAULT,	"Bad address"				},
		{ EINTR,	"Interrupted system call"		},
		{ EINVAL,	"Invalid argument"			},
		{ EISDIR,	"Is a directory"			},
		{ ENOBUFS,	"No buffer space available"		},
		{ ENODEV,	"No such device"			},
		{ ENOENT,	"No such file or directory"		},
		{ ENOEXEC,	"Exec format error"			},
		{ ENOMEM,	"Not enough memory"			},
		{ ENOSYS,	"Not implemented"			},
		{ ENOTDIR,	"Not a directory"			},
		{ ENOTSUP,	"Operation not supported"		},
		{ ENOTTY,	"Inappropriate ioctl for device"	},
		{ ENXIO,	"Device not configured"			},
		{ EPERM,	"Permission denied"			},
		{ EPIPE,	"Broken pipe"				},
		{ ERANGE,	"Result too large or too small"		},
		{ EROFS,	"Read-only filesystem"			},
#ifdef ESRCH
		{ ESRCH,	"No such process"			},
#endif
		{ EXDEV,	"Cross-device link"			},
		{ -1,		NULL					}
	};
	unsigned int i;
	int j;

	for(i = 0; err[i].errmsg != NULL; i++)
		if(err[i].errnum == errnum)
		{
			strncpy(strerrbuf, err[i].errmsg, buflen - 1);
			strerrbuf[buflen - 1] = '\0';
			j = snprintf(strerrbuf, buflen, "%s", err[i].errmsg);
			if(j < 0 || (unsigned)j >= buflen)
				return ERANGE;
			return 0;
		}
	j = snprintf(strerrbuf, buflen, "%s%d", "Unknown error: ", errnum);
	if(j < 0 || (unsigned)j >= buflen)
		return ERANGE;
	return EINVAL;
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
	char * ret = dest;

	for(; *dest; dest++);
	while(n-- && *src)
		*(dest)++ = *(src++);
	*dest = '\0';
	return ret;
}


/* strncmp */
int strncmp(char const * s1, char const * s2, size_t n)
{
	unsigned char const * u1;
	unsigned char const * u2;

	u1 = (unsigned char const *)s1;
	u2 = (unsigned char const *)s2;
	while(--n && *u1 && *u2 && *u1 == *u2)
	{
		u1++;
		u2++;
	}
	return *u1 - *u2;
}


/* strncpy */
char * strncpy(char * dest, char const * src, size_t n)
{
	char * d;

	for(d = dest; n > 0; n--)
		if(*src != '\0')
			*(d++) = *(src++);
		else
			/* pad the remainder of dest */
			*(d++) = '\0';
	return dest;
}


/* strnlen */
size_t strnlen(char const * s, size_t max)
{
	size_t len = 0;

	while(*(s++) && len < max)
		len++;
	return len;
}


/* strpbrk */
char * strpbrk(char const * s1, char const * s2)
{
	char const * p;
	char const * q;

	for(p = s1; *p != '\0'; p++)
		for(q = s2; *q != '\0'; q++)
			if(*p == *q)
				return (char *)p;
	return NULL;
}


/* strrchr */
char * strrchr(char const * s, int c)
{
	unsigned char const * ret = NULL;
	unsigned char const * ls;
	unsigned char lc = c;

	for(ls = (unsigned char const *)s; *ls != '\0'; ls++)
		if(*ls == lc)
			ret = ls;
	return (char *)((lc == '\0') ? ls : ret);
}


/* strspn */
size_t strspn(char const * s1, char const * s2)
	/* FIXME not tested */
{
	size_t i;
	char const * p;

	for(i = 0;; i++)
	{
		for(p = s2; *p != '\0' && s1[i] != *p; p++);
		if(*p == '\0')
			break;
	}
	return i;
}


/* strstr */
char * strstr(char const * s1, char const * s2)
{
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	size_t i;

	if(len2 == 0)
		return (char *)s1; /* XXX */
	if(len1 < len2)
		return NULL;
	for(i = 0; i <= len1 - len2; i++)
		if(strncmp(&s1[i], s2, len2) == 0)
			return (char *)s1 + i; /* XXX */
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


/* strxfrm */
size_t strxfrm(char * s1, char const * s2, size_t n)
{
	int res;

	/* XXX return a copy of the original string */
	if((res = snprintf(s1, n, "%s", s2)) < 0)
		return n;
	return res;
}
