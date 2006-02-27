/* stdlib.c */



#include "sys/mman.h"
#include "unistd.h"
#include "string.h"
#include "ctype.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"

#define min(a, b) (((a) > (b)) ? (b) : (a))


/* types */
typedef struct _Chunk
{
	void * ptr;
	size_t length;
} Chunk;


/* variables */
extern char ** environ;
static Chunk * _chunks = NULL;
static size_t _chunks_cnt = 0;


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
	fflush(stdout); /* FIXME flush all opened files really */
	_atexit_do(AF_EXEC, NULL);
	_exit(status);
}


/* free */
void free(void * ptr)
{
	size_t i;

	for(i = 0; i < _chunks_cnt; i++)
		if(_chunks[i].ptr == ptr)
			break;
	if(i == _chunks_cnt)
		return;
	munmap(ptr, _chunks[i].length);
	_chunks[i].ptr = NULL;
	_chunks[i].length = 0;
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
		if(*p[len] != '=')
			continue;
		return &(*p[len+1]);
	}
	return NULL;
}


/* malloc */
void * _realloc(void * ptr, size_t size);
void * malloc(size_t size)
{
	size_t i;
	void * p;

	if(size == 0)
		return NULL;
	for(i = 0; i < _chunks_cnt; i++)
		if(_chunks[i].ptr == NULL)
			break;
	if(i == _chunks_cnt)
	{
		if((p = _realloc(_chunks, (_chunks_cnt+1)*sizeof(Chunk)))
				== NULL)
			return NULL;
		_chunks = p;
		_chunks_cnt++;
		_chunks[i].ptr = NULL;
		_chunks[i].length = 0;
	}
	if((p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0))
			== MAP_FAILED)
		return NULL;
	_chunks[i].ptr = p;
	_chunks[i].length = size;
	return p;
}

void * _realloc(void * ptr, size_t size)
{
	if(mmap(ptr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_FIXED,
				-1, 0) == MAP_FAILED)
		return NULL;
	return ptr;
}


/* realloc */
void * realloc(void * ptr, size_t size)
{
	size_t i;

	if(ptr == NULL)
		return malloc(size);
	for(i = 0; i < _chunks_cnt; i++)
		if(_chunks[i].ptr == ptr)
			break;
	if(i == _chunks_cnt)
		return NULL; /* FIXME */
	if(mmap(_chunks[i].ptr, size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_FIXED, -1, 0) == MAP_FAILED)
		return NULL;
	_chunks[i].length = size;
	return ptr;
}


/* strtol */
long strtol(char const * str, char ** endptr, int base)
{
	long ret = 0;
	char const * p = str;
	int neg = 0;
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
	if(*p == '+' || *p == '-')
		if(*(p++) == '-')
			neg = 1;
	if(base == 0)
	{
		if(*p == '0')
		{
			p++;
			if(*p == 'x' || *p == 'X')
				base = 16;
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
		r = (*p) - '0';
		if(r >= 0 && r < min(10, base))
			r = *p - '0';
		else if(base > 10 && (((r = (*p) - 'a') >= 0 && r < 26)
				|| ((r = (*p) - 'A') >= 0 && r < 26)))
			r+=10;
		else
			break;
		ret+=r;
	}
	if(endptr != NULL)
		*endptr = p;
	return neg == 0 ? ret : -ret;
}
