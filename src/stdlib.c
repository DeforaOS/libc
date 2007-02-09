/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
	static size_t cb_size = 0;
	static size_t cb_pos = 0;
	void * p;

	if(cb == NULL && cb_size == 0)
	{
		if((cb = malloc(32 * sizeof(*cb))) == NULL)
			return -1;
		cb_size = 32;
	}
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
				if((p = realloc(cb, (cb_size+4) * sizeof(*cb)))
						== NULL)
					return -1;
				cb = p;
				cb_size+=4;
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
	munmap(ptr, 8192);
}


/* getenv */
char * getenv(char const * name)
{
	size_t len = strlen(name);
	char ** p;

	if(strchr(name, '=') != NULL) /* XXX not required in the standard */
	{
		errno = EINVAL;
		return NULL;
	}
	for(p = environ; *p != NULL; p++)
	{
		if(strncmp(*p, name, len) != 0 || (*p)[len] != '=')
			continue;
		return &((*p)[len+1]);
	}
	return NULL;
}


/* malloc */
void * malloc(size_t size)
{
	void * p;

	if(size == 0 || size > 8192)
	{
		errno = ENOMEM;
		return NULL;
	}
	size = 8192;
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
	if(size == 0 || size > 8192)
	{
		errno = ENOMEM;
		return NULL;
	}
	return ptr;
}


/* setenv */
static int _setenv_do(char const * name, char const * value, int overwrite);

int setenv(char const * name, char const * value, int overwrite)
{
	if(name == NULL || name[0] == '\0' || strchr(name, '=') != NULL
			|| value == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	return _setenv_do(name, value, overwrite);
}

/* _setenv_do
 * sets or unsets variables in the environment
 * PRE	name is a valid name for an environment variable
 * POST the environ global variable is allocated on the heap if not already
 * 	0  if value is NULL the name variable is unset
 * 	0  if value is not NULL the variable was updated if overwrite > 0
 * 	-1 an error occured */
static char ** _setenv_init(size_t * cnt);

static int _setenv_do(char const * name, char const * value, int overwrite)
{
	static char ** env = NULL;
	static size_t env_cnt;
	size_t nlen = strlen(name);
	size_t vlen = (value == NULL) ? 0 : strlen(value);
	char ** p;
	char * pos;

	if(env == NULL && (env = _setenv_init(&env_cnt)) == NULL)
		return -1;
	for(p = env; (pos = *p) != NULL; p++)
	{
		if(strncmp(pos, name, nlen) != 0 || pos[nlen] != '=')
			continue;
		if(overwrite == 0)
			return 0;
		if(value == NULL) /* unset variable */
		{
			for(free(pos); *p != NULL; p++)
				*p = *(p + 1);
			env_cnt--; /* may want to realloc(env) here */
			return 0;
		}
		if(strlen(pos + nlen + 1) >= vlen) /* if we can avoid realloc */
		{
			strcpy(pos + nlen + 1, value);
			return 0;
		}
		if((pos = realloc(pos, nlen + vlen + 2)) == NULL)
			return -1;
		strcpy(&pos[nlen+1], value);
		return 0;
	}
	if(value == NULL) /* variable is already unset */
		return 0;
	if((p = realloc(env, (env_cnt + 2) * sizeof(*env))) == NULL)
		return -1;
	env = p;
	environ = env;
	if((env[env_cnt] = malloc(nlen + vlen + 2)) == NULL)
		return -1;
	sprintf(env[env_cnt++], "%s=%s", name, value); /* strcpy instead? */
	return 0;
}

static void _init_atexit(void);
static char ** _setenv_init(size_t * cnt)
{
	char ** env;
	size_t i;

	for(*cnt = 0; environ[*cnt] != NULL; (*cnt)++);
	if((env = malloc((*cnt + 1) * sizeof(*env))) == NULL)
		return NULL;
	for(i = 0; i < *cnt; i++)
		if((env[i] = strdup(environ[i])) == NULL)
		{
			while(i != 0)
				free(env[--i]);
			free(env);
			return NULL;
		}
	env[i] = NULL;
	environ = env;
	_atexit_do(AF_REGISTER, _init_atexit);
	return env;
}

static void _init_atexit(void)
{
	char ** p;

	for(p = environ; *p != NULL; p++)
		free(*p);
	free(environ);
	environ = NULL;
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
	if(name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return -1;
	}
	return _setenv_do(name, NULL, 1);
}
