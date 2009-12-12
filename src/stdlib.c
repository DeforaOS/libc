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



#include "sys/mman.h"
#include "sys/stat.h"
#include "sys/wait.h"
#include "assert.h"
#include "fcntl.h"
#include "unistd.h"
#include "string.h"
#include "signal.h"
#include "ctype.h"
#include "errno.h"
#include "limits.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))


/* types */
typedef struct _Alloc
{
	size_t size;
	struct _Alloc * prev;
	struct _Alloc * next;
} Alloc;


/* variables */
extern char ** environ;
static Alloc _alloc = { 0, NULL, NULL };
static unsigned int _seed = 1;


/* functions */
/* abort */
void abort(void)
{
	/* FIXME complete */
	raise(SIGABRT);
}


/* abs */
int abs(int x)
{
	return (x >= 0) ? x : -x;
}


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


/* atof */
double atof(char const * str)
{
	/* FIXME implement */
	return 0.0;
}


/* atoi */
int atoi(char const * str)
{
	int ret = 0;
	int pos = 1;

	for(; isspace(*str); str++);
	if(*str == '-')
	{
		pos = -1;
		str++;
	}
	while(*str >= '0' && *str <= '9')
	{
		ret *= 10;
		ret += pos * (*str++ - '0');
	}
	return ret;
}


/* atol */
long atol(char const * str)
{
	long ret = 0;
	int pos = 1;

	for(; isspace(*str); str++);
	if(*str == '-')
	{
		pos = -1;
		str++;
	}
	while(*str >= '0' && *str <= '9')
	{
		ret *= 10;
		ret += pos * (*str++ - '0');
	}
	return ret;
}


/* atol */
long long atoll(char const * nptr)
{
	long long ret = 0;
	int pos = 1;

	for(; isspace(*nptr); nptr++);
	if(*nptr == '-')
	{
		pos = -1;
		nptr++;
	}
	while(*nptr >= '0' && *nptr <= '9')
	{
		ret *= 10;
		ret += pos * (*nptr++ - '0');
	}
	return ret;
}


/* bsearch */
void * bsearch(const void * key, const void * base, size_t nel,
		size_t width, int (*compar)(const void *, const void *))
{
	/* XXX from dietlibc */
	size_t m;
	int tmp;
	void * p;

	while(nel)
	{
		m = nel / 2;
		p = (void *) (((const char *) base) + (m * width));
		if((tmp = compar(key, p)) < 0)
			nel = m;
		else if(tmp > 0)
		{
			base = p + width;
			nel -= m + 1;
		}
		else
			return p;
	}
	return 0;
}


/* calloc */
void * calloc(size_t nmemb, size_t size)
{
	void * ptr;
	size_t sz = nmemb * size;

	assert(nmemb + size >= max(nmemb, size)); /* int overflow checks */
	assert(sz >= nmemb + size - 1);
	if((ptr = malloc(sz)) == NULL)
		return NULL;
	memset(ptr, 0, sz);
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
	Alloc * a = (Alloc*)((char*)ptr - sizeof(*a));
	Alloc * b;

	if(ptr == NULL)
		return;
	b = a->prev;
	b->next = a->next;
	if(a->next != NULL) /* return if memory is alloc'd past a */
	{
		a->next->prev = b;
		return;
	}
	sbrk(-(a->size + sizeof(*a)));
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


/* getloadavg */
int getloadavg(double loadavg[], int nelem)
{
#if defined(__NetBSD__)
# include "kernel/netbsd/sys/sysctl.h"
	int mib[2] = { CTL_VM, VM_LOADAVG };
	struct loadavg
	{
		uint32_t lo_avg[3];
		long lo_scale;
	} lo;
	size_t len = sizeof(lo);
	int i;

	if(sysctl(mib, 2, &lo, &len, NULL, 0) != 0)
		return -1;
	for(i = 0; i < nelem && i < 3; i++)
		loadavg[i] = lo.lo_avg[i];
	return i;
#elif defined(__linux__)
	FILE * fp;
	double lo[3];
	int i;

	if((fp = fopen("/proc/loadavg", "r")) == NULL)
		return -1;
	if(fscanf(fp, "%lf %lf %lf %d/%d %d", &lo[0], &lo[1], &lo[2], &i, &i,
				&i) != 6)
	{
		fclose(fp);
		return -1;
	}
	fclose(fp);
	for(i = 0; i < nelem && i < 3; i++)
		loadavg[i] = lo[i];
	return i;
#else
# warning Unsupported platform: getloadavg() is missing
	errno = ENOSYS;
	return -1;
#endif
}


/* grantpt */
int grantpt(int fildes)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* labs */
long labs(long x)
{
	return (x >= 0) ? x : -x;
}


/* llabs */
long long llabs(long long x)
{
	return (x >= 0) ? x : -x;
}


/* malloc */
void * malloc(size_t size)
{
	Alloc * a = &_alloc;
	Alloc * b;
	intptr_t inc;

	if(size >= INT_MAX - sizeof(*b) - 0x8)
	{
		errno = ENOMEM;
		return NULL;
	}
	size = (size | 0x7) + 1; /* round up to 64 bits */
	inc = size + sizeof(*b);
	if(_alloc.next != NULL) /* look for available space */
		for(a = _alloc.next; a->next != NULL; a = a->next)
			if(inc <= (char *)(a->next) - (char *)a - sizeof(*a)
					- a->size)
			{
				b = (Alloc*)((char*)a + sizeof(*a) + a->size);
				b->size = size;
				a->next->prev = b;
				break;
			}
	if(a->next == NULL) /* increase process size to allocate memory */
	{
		if((b = sbrk(inc)) == (void*)-1) /* XXX cast */
			return NULL;
		b->size = size;
	}
	b->prev = a;
	b->next = a->next;
	a->next = b;
	return (char*)b + sizeof(*b);
}


/* mktemp */
char * mktemp(char * template)
{
	size_t i;
	struct stat st;

	for(i = strlen(template); i-- > 0 && template[i] == 'X';)
		template[i] = (rand() % 0x47) + '0';
	if(lstat(template, &st) != 0)
		return errno == ENOENT ? template : NULL;
	errno = EEXIST;
	return NULL;
}


/* mkstemp */
int mkstemp(char * template)
{
	if(mktemp(template) == NULL)
		return -1;
	return open(template, O_WRONLY | O_CREAT | O_EXCL, 0666);
}


/* ptsname */
char * ptsname(int fildes)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* putenv */
int putenv(char * string)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* qsort */
static void _qsort_do(char * base, size_t width, size_t l, size_t r,
		int (*compar)(const void *, const void *));
static void _qsort_exch(char * base, size_t width, size_t a, size_t b);

void qsort(void * base, size_t nel, size_t width,
		int (*compar)(const void *, const void *))
{
	/* XXX from dietlibc */
	if(nel > 1)
		_qsort_do(base, width, 0, nel - 1, compar);
}

static void _qsort_do(char * base, size_t width, size_t l, size_t r,
		int (*compar)(const void *, const void *))
	/* If I put it correctly:
	 * l is the left cursor
	 * i is the current position "left-wise"
	 * j is the current position "right-wise"
	 * r is the right cursor
	 * p is the last element */
{
	size_t i = l - 1;
	size_t j = r;
	void * p = base + r * width;

	if(r <= l)
		return;
	for(;; _qsort_exch(base, width, i, j))
	{
		while(compar(base + (++i) * width, p) < 0);
		while(compar(p, base + (--j) * width) < 0)
			if(j == l)
				break;
		if(i >= j)
			break;
	}
	_qsort_exch(base, width, i, r);
	_qsort_do(base, width, l, i - 1, compar);
	_qsort_do(base, width, i + 1, r, compar);
}

static void _qsort_exch(char * base, size_t width, size_t a, size_t b)
{
	char * pa = base + a * width;
	char * pb = base + b * width;
	char tmp;

	for(; width; width--)
	{
		tmp = *(pa++);
		*pa = *pb;
		*(pb++) = tmp;
	}
}


/* rand */
int rand(void)
{
	_seed *= 0x23456789; /* FIXME totally poor randomness */
	return _seed % RAND_MAX;
}


/* realloc */
void * realloc(void * ptr, size_t size)
{
	Alloc * a = (Alloc*)((char*)ptr - sizeof(*a));
	void * p;

	if(ptr == NULL)
		return malloc(size);
	if(size == a->size)
		return ptr;
	size = (size | 0xf) + 1; /* round up to 64 bits */
	if(size < a->size || (a->next != NULL && (char*)a->next - (char*)a
				- sizeof(*a) >= size))
	{
		a->size = size;
		return ptr;
	}
	if((p = malloc(size)) == NULL)
		return NULL;
	memcpy(p, ptr, min(a->size, size));
	free(ptr);
	return p;
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
	sprintf(env[env_cnt++], "%s=%s", name, value);
	env[env_cnt] = NULL;
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


/* srand */
void srand(unsigned int seed)
{
	_seed = seed;
}


/* strtod */
double strtod(char const * str, char ** endptr)
{
	/* FIXME implement */
	return 0.0;
}


/* strtol */
static unsigned long long _strtoull(char const * str, char ** endptr, int base,
		int * neg);
static int _strtoull_base(char const ** p);

long strtol(char const * str, char ** endptr, int base)
{
	unsigned long ret;
	int neg = 0;

	ret = _strtoull(str, endptr, base, &neg);
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

static unsigned long long _strtoull(char const * str, char ** endptr, int base,
		int * neg)
{
	unsigned long long ret = 0;
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
			*endptr = (char*)p; /* XXX cast */
		errno = ERANGE;
		return 0;
	}
	if((*p == '+' || *p == '-') && *(p++) == '-' && neg != NULL)
		*neg = 1;
	if(base == 0)
		base = _strtoull_base(&p);
	if(base == 16 && *p == '0')
	{
		p++;
		if(*p == 'x' || *p == 'X')
			p++;
	}
	for(; *p != '\0'; p++)
	{
		if(*p >= '0' && *p - '0' < min(10, base))
			ret = (ret * base) + *p - '0';
		else if(base > 10 && (((r = (*p) - 'a') >= 0 && r < 26)
				|| ((r = (*p) - 'A') >= 0 && r < 26))
				&& r < base - 10)
			ret = (ret * base) + r + 10;
		else
			break;
		/* FIXME add integer overflow detection code */
	}
	if(endptr != NULL)
		*endptr = (char*)p; /* XXX cast */
	return ret;
}

static int _strtoull_base(char const ** p)
{
	if(**p == '0')
	{
		(*p)++;
		if(**p == 'x' || **p == 'X')
		{
			(*p)++;
			return 16;
		}
		return 8;
	}
	return 10;
}


/* strtoll */
long long strtoll(char const * str, char ** endptr, int base)
{
	unsigned long long ret;
	int neg = 0;

	ret = _strtoull(str, endptr, base, &neg);
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


/* strtoul */
unsigned long strtoul(char const * str, char ** endptr, int base)
{
	return _strtoull(str, endptr, base, NULL);
}


/* strtoull */
unsigned long long strtoull(char const * str, char ** endptr, int base)
{
	return _strtoull(str, endptr, base, NULL);
}


/* system */
int system(char const * command)
{
	pid_t pid;
	pid_t p;

	/* FIXME also block some signals etc */
	if((pid = fork()) == -1)
		return -1;
	if(pid == 0)
	{
		execl("/bin/sh", "sh", "-c", command, NULL);
		_exit(127);
	}
	for(;;)
		if((p = waitpid(pid, NULL, 0)) != -1 || errno != EINTR)
			break;
	return (p == pid) ? 0 : -1;
}


/* unlockpt */
int unlockpt(int fildes)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
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
