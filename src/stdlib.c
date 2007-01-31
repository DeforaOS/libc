/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "sys/mman.h"
#include "unistd.h"
#include "string.h"
#include "ctype.h"
#include "errno.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"

#define min(a, b) (((a) > (b)) ? (b) : (a))


/* variables */
extern char ** environ;


/* atexit */
typedef enum _AtexitFunction { AF_EXEC, AF_PURGE, AF_REGISTER } AtexitFunction;
typedef void (*AtexitCallback)(void);
static int _atexit_do(AtexitFunction function, void (*callback)(void));
int atexit(void (*function)(void))
{
	return _atexit_do(AF_REGISTER, function);
}

static int _atexit_do(AtexitFunction function, void (*callback)(void))
{
	static AtexitCallback * cb = NULL;
	static int cb_size = 0;
	static int cb_pos = 0;
	void * p;

	if(cb == NULL && cb_size == 0)
		cb = malloc(32 * sizeof(void*));
	switch(function)
	{
		case AF_EXEC:
			while(cb_pos-- > 0)
				cb[cb_pos]();
		case AF_PURGE:
			free(cb);
			cb = NULL;
			cb_size = 0;
			cb_pos = 0;
			break;
		case AF_REGISTER:
			if(cb_pos == cb_size)
			{
				if((p = realloc(cb, (cb_size+1)*sizeof(void*)))
						== NULL)
					return -1;
				cb = p;
			}
			cb[cb_pos++] = callback;
			break;
	}
	return 0;
}


/* atoi */
int atoi(char const * str)
{
	int res = 0;
	int pos = 1;

	if(*str == '-')
	{
		pos = -1;
		str++;
	}
	while(*str)
	{
		res *= 10;
		res += pos * (*str++ - '0');
	}
	return res;
}


/* atol */
long atol(char const * str)
{
	long res = 0;
	int pos = 1;

	if(*str == '-')
	{
		pos = -1;
		str++;
	}
	while(*str)
	{
		res *= 10;
		res += pos * (*str++ - '0');
	}
	return res;
}


/* atol */
long long atoll(char const * nptr)
{
	long long res = 0;
	int pos = 1;

	if(*nptr == '-')
	{
		pos = -1;
		nptr++;
	}
	while(*nptr)
	{
		res *= 10;
		res += pos * (*nptr++ - '0');
	}
	return res;
}


/* calloc */
void * calloc(size_t nmemb, size_t size)
{
	void * ptr;

	if((ptr = malloc(nmemb * size)) == NULL)
		return NULL;
	memset(ptr, 0, nmemb * size);
	return ptr;
}


/* exit */
void exit(int status)
{
	/* FIXME flush all opened files really */
	fflush(stdout);
	fflush(stderr);
	_atexit_do(AF_EXEC, NULL);
	_exit(status);
}


/* free */
void free(void * ptr)
{
	munmap(ptr, 4096);
}


/* getenv */
char * getenv(char const * name)
{
	int len = strlen(name);
	char ** p;

	for(p = environ; *p != NULL; p++)
	{
		if(strncmp(*p, name, len) != 0)
			continue;
		if((*p)[len] != '=')
			continue;
		return &((*p)[len+1]);
	}
	return NULL;
}


/* malloc */
void * malloc(size_t size)
{
	void * p;

	if(size == 0 || size > 4096)
	{
		errno = ENOSYS;
		return NULL;
	}
	size = 4096;
	if((p = mmap(NULL, size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))
			== MAP_FAILED)
		return NULL;
	return p;
}


/* realloc */
void * realloc(void * ptr, size_t size)
{
	if(ptr == NULL)
		return malloc(size);
	if(size == 0 || size > 4096)
	{
		errno = ENOSYS;
		return NULL;
	}
	return ptr;
}


/* setenv */
int setenv(char const * name, char const * value, int overwrite)
{
	if(getenv(name) != NULL)
	{
		if(overwrite == 0)
			return 0;
		unsetenv(name);
	}
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* strtol */
static unsigned long _strtoul(char const * str, char ** endptr, int base,
		int * neg);
long strtol(char const * str, char ** endptr, int base)
{
	unsigned long ret;
	int neg = 0;

	ret = _strtoul(str, endptr, base, &neg);
	if(neg != 0)
	{
		if(ret > (unsigned)LONG_MAX+1)
		{
			errno = ERANGE;
			return LONG_MIN;
		}
		return -ret;
	}
	if(ret > LONG_MAX)
	{
		errno = ERANGE;
		return LONG_MAX;
	}
	return ret;
}

static unsigned long _strtoul(char const * str, char ** endptr, int base,
		int * neg)
{
	unsigned long ret = 0;
	char const * p;
	int r;

	if(base > 36 || base < 0 || base == 1)
	{
		errno = EINVAL;
		return 0;
	}
	for(p = str; isspace(*p); p++);
	if(*p == '\0')
	{
		if(endptr != NULL)
			*endptr = p;
		errno = ERANGE;
		return 0;
	}
	if((*p == '+' || *p == '-') && *(p++) == '-' && neg != NULL)
		*neg = 1;
	if(base == 0)
	{
		if(*p == '0')
		{
			p++;
			if(*p == 'x' || *p == 'X')
			{
				p++;
				base = 16;
			}
			else
				base = 8;
		}
		else
			base = 10;
	}
	if(base == 16 && *p == '0')
	{
		p++;
		if(*p == 'x' || *p == 'X')
			p++;
	}
	for(; *p != '\0'; p++)
	{
		ret *= base;
		if(*p >= '0' && *p - '0' < min(10, base))
			ret += *p - '0';
		else if(base > 10 && (((r = (*p) - 'a') >= 0 && r < 26)
				|| ((r = (*p) - 'A') >= 0 && r < 26))
				&& r < base - 10)
			ret += r + 10;
		else
			break;
		/* FIXME add integer overflow detection code */
	}
	if(endptr != NULL)
		*endptr = p;
	return ret;
}


/* strtoul */
unsigned long strtoul(char const * str, char ** endptr, int base)
{
	return _strtoul(str, endptr, base, NULL);
}


/* unsetenv */
int unsetenv(char const * name)
{
	if(name == NULL || *name == '\0' || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return -1;
	}
	if(getenv(name) == NULL)
		return 0;
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}
