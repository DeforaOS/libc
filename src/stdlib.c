/* stdlib.c */



#include "errno.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#ifdef DEBUG
# include "stdio.h"
#endif


/* types */
#define CHUNK_ALLOCED	1
#define CHUNK_FOLLOWED	2
typedef struct _Chunk {
	size_t len;
	int flags;
} Chunk;


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
static void _free_merge(Chunk * chnk);
void free(void * ptr)
{
	Chunk * chnk;

	chnk = ptr - sizeof(Chunk);
	if(chnk->flags & CHUNK_ALLOCED)
	{
#ifdef DEBUG
		fprintf(stderr, "%s", "libc: double free: %p\n", ptr);
#endif
		return;
	}
	chnk->flags--;
	_free_merge(chnk);
}

static void _free_merge(Chunk * chnk)
{
	Chunk * p;
	Chunk * p2;

	for(p = chnk; p->flags & CHUNK_FOLLOWED; p+=p->len)
		if(p->flags & CHUNK_ALLOCED)
			chnk = p + p->len;
		else
		{
			do {
				p2 = p + p->len;
				if(p2->flags & CHUNK_ALLOCED)
					break;
				p->len += p2->len + sizeof(Chunk);
			}
			while(p2->flags & CHUNK_FOLLOWED);
			p = p2;
		}
	if(p->flags & CHUNK_ALLOCED)
		return;
#ifdef DEBUG
	if(brk(chnk) != 0)
	{
		fprintf(stderr, "%s", "libc: ");
		perror("free");
	}
#else
	brk(chnk);
#endif
}


/* malloc */
void * malloc(size_t size)
{
	Chunk * chnk;
	Chunk * p;

	if(size == 0)
		return NULL;
	for(chnk = sbrk(0); chnk->flags & CHUNK_FOLLOWED; chnk+=chnk->len)
	{
		if(!(chnk->flags & CHUNK_ALLOCED)
				&& chnk->len >= size + sizeof(Chunk))
		{
			chnk->flags |= CHUNK_ALLOCED;
			p = chnk + size + sizeof(Chunk);
			p->len = chnk->len - size - sizeof(Chunk);
			p->flags = CHUNK_FOLLOWED;
			chnk->len = size;
			return chnk + sizeof(Chunk);
		}
	}
	chnk->flags |= CHUNK_FOLLOWED;
	if((chnk = sbrk(size + sizeof(Chunk))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	}
	chnk->len = size;
	chnk->flags = CHUNK_ALLOCED;
	return chnk + sizeof(Chunk);
}
