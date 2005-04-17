/* stdlib.c */



#include "sys/mman.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"


/* types */
typedef struct _Chunk
{
	void * ptr;
	size_t length;
} Chunk;


/* variables */
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
long strtol(char const * nptr, char ** endptr, int base)
{
	char * p;

	if(base > 36 || base < 0 || base == 1)
		return 0;
	for(p = nptr; isspace(*p); p++);
	return 0; /* FIXME */
}
