/* string.c */



#include "stdlib.h"
#include "string.h"


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


/* strcmp */
int strcmp(char const * s1, char const * s2)
{
	unsigned char const * u1;
	unsigned char const * u2;

	u1 = s1;
	u2 = s2;
	while(*u1 && *u2 && *u1 == *u2)
	{
		*u1++;
		*u2++;
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


/* strdup */
char * strdup(char const * s)
{
	size_t len;
	char * str;

	/* FIXME needed? */
	if(s == NULL)
		return NULL;
	len = strlen(s) + 1;
	if((str = malloc(sizeof(char) * len)) == NULL)
		return NULL;
	strcpy(str, s);
	return str;
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
