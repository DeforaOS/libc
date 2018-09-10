/* $Id$ */
/* Copyright (c) 2004-2018 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/mman.h"
#include "sys/stat.h"
#include "sys/sysctl.h"
#include "sys/wait.h"
#include "assert.h"
#include "fcntl.h"
#include "unistd.h"
#include "string.h"
#include "strings.h"
#include "signal.h"
#include "ctype.h"
#include "errno.h"
#include "limits.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#define ECRYPT_ENCRYPTS_BYTES
#include "chacha/chacha.c"

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))


/* private */
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


/* prototypes */
static void _mktemp_template(char * template);
static long double _strtold(char const * str, char ** endptr);
static unsigned long long _strtoull(char const * str, char ** endptr, int base,
		int * neg);


/* public */
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


/* arc4random */
uint32_t arc4random(void)
{
	static int initialized = 0;
	int fd;
	static ECRYPT_ctx ctx;
	struct
	{
		unsigned char key[64];
		unsigned char iv[8];
	} ki;
	const unsigned char input[4] = { 0 };
	union
	{
		uint8_t u8[4];
		uint32_t u32;
	} ret;

	if(!initialized)
	{
		if((fd = open("/dev/urandom", O_RDONLY)) < 0
				|| read(fd, &ki, sizeof(ki)) != sizeof(ki))
			abort();
		close(fd);
		ECRYPT_init();
		ECRYPT_keysetup(&ctx, (unsigned char *)&ki.key,
				sizeof(ki.key) * 8, sizeof(ki.iv) * 8);
		ECRYPT_ivsetup(&ctx, (unsigned char *)&ki.iv);
		initialized = 1;
	}
	ECRYPT_encrypt_bytes(&ctx, (unsigned char *)&input, ret.u8,
			sizeof(input));
	return ret.u32;
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
			/* fallthrough */
		case AF_PURGE:
			free(cb);
			cb = NULL;
			cb_size = 0;
			cb_pos = 0;
			break;
		case AF_REGISTER:
			if(cb_pos == cb_size)
			{
				if((p = realloc(cb, (cb_size + 4)
								* sizeof(*cb)))
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
	return strtod(str, NULL);
}


/* atoi */
int atoi(char const * str)
{
	int ret = 0;
	int pos = 1;

	for(; isspace((int)(unsigned char)*str); str++);
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

	for(; isspace((int)(unsigned char)*str); str++);
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

	for(; isspace((int)(unsigned char)*nptr); nptr++);
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
		size_t size, int (*compar)(const void *, const void *))
{
	/* XXX from dietlibc */
	size_t m;
	int tmp;
	void * p;

	while(nel)
	{
		m = nel / 2;
		p = (void *) (((const char *) base) + (m * size));
		if((tmp = compar(key, p)) < 0)
			nel = m;
		else if(tmp > 0)
		{
			base = (char *)p + size;
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
	size_t sz;

	if(nmemb != 0 && size != 0 && SIZE_MAX / nmemb < size)
	{
		errno = ENOMEM;
		return NULL;
	}
	sz = nmemb * size;
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
static void _free_abort(void);

void free(void * ptr)
{
	Alloc * a;
	Alloc * b;

	if(ptr == NULL)
		return;
	if(ptr < (void *)sizeof(*a))
	{
		_free_abort();
		return;
	}
	a = (Alloc *)ptr - 1;
	b = a->prev;
	if(b->next != a)
	{
		_free_abort();
		return;
	}
	b->next = a->next;
	if(a->next != NULL) /* memory is allocated past a */
		a->next->prev = b;
	else if(b != &_alloc)
		/* decrease to lowest possible value */
		sbrk(-((uintptr_t)a + a->size - (uintptr_t)b - b->size));
	else
		/* remove the last object */
		sbrk(-sizeof(*a) - a->size);
}

static void _free_abort(void)
{
	const char buf[] = "invalid free detected: terminated\n";

	write(2, buf, sizeof(buf) - 1);
	abort();
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
#if defined(CTL_VM) && defined(VM_LOADAVG)
	int mib[2] = { CTL_VM, VM_LOADAVG };
	struct loadavg
	{
		uint32_t lo_avg[3];
		long lo_scale;
	} lo;
	size_t len = sizeof(lo);
	int i;

	if(sysctl(mib, sizeof(mib) / sizeof(*mib), &lo, &len, NULL, 0) != 0)
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
	if(fscanf(fp, "%f %f %f %d/%d %d", &lo[0], &lo[1], &lo[2], &i, &i, &i)
			!= 6)
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
	Alloc * b = NULL;
	uintptr_t inc;

	if(size >= SSIZE_MAX - sizeof(*b) - 0x8)
	{
		errno = ENOMEM;
		return NULL;
	}
	if((size & 0x7) != 0x0)
		size = (size | 0x7) + 1; /* round up to 64 bits */
	inc = size + sizeof(*b);
	if(_alloc.next != NULL) /* look for available space */
		for(a = _alloc.next; a->next != NULL; a = a->next)
			if(inc <= (uintptr_t)a->next - (uintptr_t)a - sizeof(*a)
					- a->size)
			{
				b = (Alloc *)((uintptr_t)a + sizeof(*a)
						+ a->size);
				a->next->prev = b;
				break;
			}
	if(b == NULL) /* increase process size to allocate memory */
		if((b = sbrk(inc)) == (void *)-1)
			return NULL;
	b->size = size;
	b->prev = a;
	b->next = a->next;
	a->next = b;
	return b + 1;
}


/* mktemp */
char * mktemp(char * template)
{
	size_t i;
	struct stat st;

	for(i = 0; i < 20; i++)
	{
		_mktemp_template(template);
		if(lstat(template, &st) != 0)
		{
			if(errno == ENOENT)
				return template;
		}
		else
			errno = EEXIST;
	}
	return NULL;
}


/* mkstemp */
int mkstemp(char * template)
{
	size_t i;
	int fd;
	const int flags = O_WRONLY | O_CREAT | O_EXCL;

	for(i = 0; i < 20; i++)
	{
		_mktemp_template(template);
		if((fd = open(template, flags, 0600)) >= 0)
			return fd;
	}
	return -1;
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
static void _qsort_do(char * base, size_t size, size_t l, size_t r,
		int (*compar)(const void *, const void *));
static void _qsort_exch(char * base, size_t size, size_t a, size_t b);

void qsort(void * base, size_t nel, size_t size,
		int (*compar)(const void *, const void *))
{
	/* XXX from dietlibc */
	if(nel > 1)
		_qsort_do(base, size, 0, nel - 1, compar);
}

static void _qsort_do(char * base, size_t size, size_t l, size_t r,
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
	void * p = base + r * size;

	if(r <= l)
		return;
	for(;; _qsort_exch(base, size, i, j))
	{
		while(compar(base + (++i) * size, p) < 0);
		while(compar(p, base + (--j) * size) < 0)
			if(j == l)
				break;
		if(i >= j)
			break;
	}
	_qsort_exch(base, size, i, r);
	_qsort_do(base, size, l, i - 1, compar);
	_qsort_do(base, size, i + 1, r, compar);
}

static void _qsort_exch(char * base, size_t size, size_t a, size_t b)
{
	char * pa = base + a * size;
	char * pb = base + b * size;
	char tmp;

	for(; size; size--)
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
	Alloc * a = (Alloc *)ptr - 1;
	void * p;

	if(ptr == NULL)
		return malloc(size);
	if((size & 0x7) != 0x0)
		size = (size | 0x7) + 1; /* round up to 64 bits */
	if(size == a->size)
		return ptr;
	if(a->next == NULL)
	{
		/* reallocate the space */
		if(sbrk(size - a->size) == (void *)-1)
			return NULL;
		a->size = size;
		return ptr;
	}
	if(size < a->size || (uintptr_t)a->next - (uintptr_t)a - sizeof(*a)
			>= size)
	{
		/* update the size */
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
	const size_t nlen = strlen(name);
	const size_t vlen = (value == NULL) ? 0 : strlen(value);
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
			free(pos);
			for(; *p != NULL; p++)
				*p = *(p + 1);
			env_cnt--; /* may want to realloc(env) here */
			return 0;
		}
		if(strlen(pos + nlen + 1) >= vlen) /* if we can avoid realloc */
		{
			strcpy(pos + nlen + 1, value);
			return 0;
		}
		if((pos = realloc(*p, nlen + vlen + 2)) == NULL)
			return -1;
		*p = pos;
		strcpy(&pos[nlen + 1], value);
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
	return _strtold(str, endptr);
}


/* strtof */
float strtof(char const * str, char ** endptr)
{
	return _strtold(str, endptr);
}


/* strtol */
long strtol(char const * str, char ** endptr, int base)
{
	unsigned long ret;
	int neg = 0;

	ret = _strtoull(str, endptr, base, &neg);
	if(neg != 0)
	{
		if(ret > (unsigned long)LONG_MAX + 1)
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


/* strtold */
long double strtold(char const * str, char ** endptr)
{
	return _strtold(str, endptr);
}


/* strtoll */
long long strtoll(char const * str, char ** endptr, int base)
{
	unsigned long long ret;
	int neg = 0;

	ret = _strtoull(str, endptr, base, &neg);
	if(neg != 0)
	{
		if(ret > (unsigned long long)LLONG_MAX + 1)
		{
			errno = ERANGE;
			return LLONG_MIN;
		}
		return -ret;
	}
	if(ret > LLONG_MAX)
	{
		errno = ERANGE;
		return LLONG_MAX;
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


/* private */
/* functions */
/* mktemp_template */
static void _mktemp_template(char * template)
{
	static char const tab[62] = "0123456789abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size_t i;

	for(i = strlen(template); i > 0 && template[i - 1] == 'X'; i--)
		template[i - 1] = tab[rand() % sizeof(tab)];
}


/* strtold */
static long double _strtold(char const * str, char ** endptr)
{
	/* FIXME support additional notations */
	long double ret;
	char const * e;
	int neg = 0;
	unsigned long u = 0;
	unsigned long cnt;
	long double f;

	/* skip initial spaces */
	for(e = str; *e != '\0'; e++)
		if(!isspace((unsigned char)*e))
			break;
	/* skip optional '-' or '+' sign */
	if(*e == '-')
	{
		neg = 1;
		e++;
	}
	else if(*e == '+')
		e++;
	for(cnt = 0; isdigit((unsigned char)e[cnt]); cnt++)
		u = u * 10 + (e[cnt] - '0');
	if(cnt == 0)
		return 0.0 / 0.0;
	e += cnt;
	ret = u;
	if(*e == '.')
	{
		e++;
		u = 0;
		for(cnt = 0; isdigit((unsigned char)e[cnt]); cnt++)
			u = u * 10 + (e[cnt] - '0');
		if(cnt == 0)
			return 0.0 / 0.0;
		e += cnt;
		f = u;
		for(; cnt > 0; cnt--)
			f = f / 10;
		ret += f;
	}
	if(endptr != NULL)
		*endptr = (char *)e;
	return neg ? -ret : ret;
}


/* strtoull */
static int _strtoull_base(char const ** p);

static unsigned long long _strtoull(char const * str, char ** endptr, int base,
		int * neg)
{
	unsigned long long ret = 0;
	char const * p;
	int r;
	size_t i;

	if(base > 36 || base < 0 || base == 1)
	{
		errno = EINVAL;
		return 0;
	}
	for(p = str; isspace((int)(unsigned char)*p); p++);
	if(*p == '\0')
	{
		if(endptr != NULL)
			*endptr = (char *)str; /* XXX cast */
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
	for(i = 0; p[i] != '\0'; i++)
	{
		if(p[i] >= '0' && p[i] - '0' < min(10, base))
			r = p[i] - '0';
		else if(base > 10 && (((r = p[i] - 'a') >= 0 && r < 26)
				|| ((r = p[i] - 'A') >= 0 && r < 26))
				&& r < base - 10)
			r += 10;
		else
			break;
		/* FIXME add integer overflow detection code */
		ret = (ret * base) + r;
	}
	if(i == 0)
	{
		errno = EINVAL;
		return 0;
	}
	if(endptr != NULL)
		*endptr = (char *)&p[i]; /* XXX cast */
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
