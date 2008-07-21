/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */
/* TODO
 * - unload libraries with atexit() */



#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#ifdef DEBUG
# include <stdio.h>
#endif
#include <string.h>
#ifdef _LP64
# define ELFSIZE 64
#else
# define ELFSIZE 32
#endif
#include <errno.h>
#include <elf.h>
#include "dlfcn.h"


/* FIXME properly detect endian
#if BYTE_ORDER == BIG_ENDIAN
# define ELFDATA	ELFDATA2MSB
#else */
# define ELFDATA	ELFDATA2LSB
/* #endif */


/* private */
/* types */
typedef struct _DL
{
	/* mandatory fields */
	char * base;
	char * path;
	char * dynamic; /* FIXME */
	struct _DL * next;
	struct _DL * prev;

	/* internals */
	size_t base_len;
} DL;


/* variables */
typedef enum _DLError
{
	DE_NO_ERROR = 0,
	/* from errno */
	DE_ISDIR,
	DE_NOENT,
	DE_NOMEM,
	DE_PERM,
	/* for dlfcn */
	DE_INVALID_FILE,
	DE_NOT_SUPPORTED,
	DE_READ_ERROR,
	DE_UNKNOWN_ERROR
} DLError;
#define DE_LAST DE_UNKNOWN_ERROR
#define DE_COUNT (DE_LAST + 1)
static int _dl_errno = DE_NO_ERROR;

static DL _dl = { NULL, NULL, NULL, NULL, NULL, 0 };


/* prototypes */
static void * _dl_new(char const * pathname);
static void _dl_delete(DL * dl);

/* accessors */
static int _dl_get_prot(Elf_Word flags);
static int _dl_set_errno(int ret);

/* useful */
static off_t _dl_lseek(int fd, off_t offset, int whence);
static int _dl_open(const char * pathname, int flags, mode_t mode);
static ssize_t _dl_read(int fd, void * buf, size_t len);
static void * _dl_read_area(int fd, size_t number, size_t size);

static int _dl_ehdr_check(Elf_Ehdr * ehdr);
static int _dl_phdr_check(Elf_Phdr * phdr, size_t cnt);
static int _dl_shdr_check(Elf_Shdr * shdr, size_t cnt);

static int _dl_map(DL * dl, int fd, Elf_Phdr * phdr, size_t cnt);


/* functions */
/* dl_new */
static void * _dl_new(char const * pathname)
{
	DL * dl;

	if((dl = malloc(sizeof(*dl))) == NULL)
	{
		_dl_errno = DE_NOMEM;
		return NULL;
	}
	dl->base = NULL;
	dl->path = strdup(pathname);
	dl->dynamic = NULL;
	dl->next = NULL; /* FIXME set correctly already? */
	dl->prev = NULL; /* FIXME set correctly already? */
	dl->base_len = 0;
	return dl;
}


/* dl_delete */
static void _dl_delete(DL * dl)
{
	/* FIXME implement */
	if(dl->next != NULL)
		dl->next->prev = dl->prev;
	if(dl->prev != NULL)
		dl->prev->next = dl->next;
	if(dl->base != NULL)
		munmap(dl->base, dl->base_len);
	free(dl->path);
	free(dl);
}


/* accessors */
/* dl_get_prot */
static int _dl_get_prot(Elf_Word flags)
{
	int ret = PROT_NONE;

	if(flags & PF_R)
		ret |= PROT_READ;
	if(flags & PF_W)
		ret |= PROT_WRITE;
	if(flags & PF_X)
		ret |= PROT_EXEC;
	return ret;
}


/* dl_set_errno */
static int _dl_set_errno(int ret)
{
	switch(errno)
	{
		case EISDIR:
			_dl_errno = DE_ISDIR;
			break;
		case ENOENT:
			_dl_errno = DE_NOENT;
			break;
		case ENOMEM:
			_dl_errno = DE_NOMEM;
			break;
		case EPERM:
			_dl_errno = DE_PERM;
			break;
		default:
			_dl_errno = DE_UNKNOWN_ERROR;
			break;
	}
	return ret;
}


/* useful */
/* dl_lseek */
static off_t _dl_lseek(int fd, off_t offset, int whence)
{
	off_t ret;

	if((ret = lseek(fd, offset, whence)) != -1)
		return ret;
#ifdef DEBUG
	fprintf(stderr, "DEBUG: lseek(%d, %lld, %d) => %lld\n", fd, offset,
			whence, ret);
#endif
	return _dl_set_errno(ret);
}


/* dl_open */
static int _dl_open(const char * pathname, int flags, mode_t mode)
{
	int fd;

	if((fd = open(pathname, flags, mode)) >= 0)
		return fd;
	return _dl_set_errno(fd);
}

/* dl_read */
static ssize_t _dl_read(int fd, void * buf, size_t len)
{
	ssize_t ret;

	if((ret = read(fd, buf, len)) != -1)
		return ret;
	return _dl_set_errno(ret);
}


/* dl_read_area */
static void * _dl_read_area(int fd, size_t number, size_t size)
{
	void * ret;
	ssize_t len;

	len = number * size; /* FIXME integer overflow */
	if((ret = malloc(len)) == NULL)
	{
		_dl_errno = DE_NOMEM;
		return NULL;
	}
	if(_dl_read(fd, ret, len) == len)
		return ret;
	free(ret);
	return NULL;
}


static int _dl_ehdr_check(Elf_Ehdr * ehdr)
{
	if(memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0
			|| ehdr->e_ident[EI_CLASS] != ELFCLASS
			|| ehdr->e_ident[EI_DATA] != ELFDATA
			|| ehdr->e_type != ET_DYN
			|| ehdr->e_version != EV_CURRENT
			|| ehdr->e_phnum == 0
			|| ehdr->e_phoff < sizeof(ehdr)
			|| ehdr->e_phentsize != sizeof(Elf_Phdr)
			|| ehdr->e_shnum == 0
			|| ehdr->e_shoff < sizeof(ehdr)
			|| ehdr->e_shentsize != sizeof(Elf_Shdr))
	{
		_dl_errno = DE_INVALID_FILE;
		return -1;
	}
	return 0;
}


static int _dl_phdr_check(Elf_Phdr * phdr, size_t cnt)
{
	size_t i;

	for(i = 0; i < cnt; i++)
		if((phdr[i].p_type == PT_PHDR && i != 0)
				|| phdr[i].p_filesz > phdr[i].p_memsz)
		{
			_dl_errno = DE_INVALID_FILE;
			return -1;
		}
	return 0;
}


static int _dl_shdr_check(Elf_Shdr * shdr, size_t cnt)
{
	/* FIXME implement
	size_t i;

	for(i = 0; i < cnt; i++); */
	return 0;
}


static int _dl_map(DL * dl, int fd, Elf_Phdr * phdr, size_t cnt)
{
	size_t i;
	char * addr;
	size_t len;
	int prot;
	int flags;
	off_t offset;
	char * p;

	for(i = 0; i < cnt; i++)
	{
		if(phdr[i].p_type == PT_DYNAMIC)
			dl->dynamic = (char*)phdr[i].p_offset; /* FIXME check */
		else if(phdr[i].p_type != PT_LOAD)
			continue;
		addr = dl->base + dl->base_len;
		len = (phdr[i].p_memsz | 0xf) + 1;
		prot = _dl_get_prot(phdr[i].p_flags);
		flags = MAP_PRIVATE;
		flags |= (addr != NULL) ? MAP_FIXED : 0;
		offset = phdr[i].p_offset;
		p = mmap(addr, len, prot, flags, fd, offset);
#ifdef DEBUG
		fprintf(stderr, "DEBUG: mmap(%p, 0x%zx, 0x%x, 0x%x, %d, %llu)"
				" => %p\n", addr, len, prot, flags, fd, offset,
				p);
#endif
		if(p == MAP_FAILED)
		{
#ifdef DEBUG
			fprintf(stderr, "DEBUG: (%s)\n", strerror(errno));
#endif
			_dl_errno = DE_NOMEM;
			return -1;
		}
		memset(&p[phdr[i].p_filesz], 0, phdr[i].p_memsz - phdr[i].p_filesz);
		if(dl->base == NULL)
			dl->base = p;
		dl->base_len += len;
	}
	return 0;
}


#if 0
static int _do_phdr_read(int fd, unsigned int e_phnum, Elf_Phdr * phdr)
{
	size_t i;
	size_t cnt = 0;

	for(i = 0; i < e_phnum; i++)
	{
		if(_dl_read(fd, phdr, sizeof(*phdr)) != sizeof(*phdr))
		{
			_dl_errno = DE_READ_ERROR;
			return -1;
		}
		else if(phdr->p_type != PT_LOAD)
			continue;
		else if(phdr->p_filesz > phdr->p_memsz)
		{
			_dl_errno = DE_INVALID_FILE;
			return -1;
		}
#ifdef DEBUG
		fprintf(stderr, "DEBUG: PT_LOAD %zu p_filesz=%lld"
				", p_memsz=%lld\n", i, phdr->p_filesz,
				phdr->p_memsz);
#endif
		if(cnt++ != 0) /* FIXME handle only one at the moment */
		{
			_dl_errno = DE_NOT_SUPPORTED;
			return -1;
		}
		return 0;
	}
	return -1;
}
#endif

#if 0
	len = sizeof(*phdr) * ehdr.e_phnum;
	if((phdr = _dl_malloc(len)) == NULL)
		return NULL;
	if(read(fd, phdr, len) != len
			|| (p = _do_get_load(ehdr.e_phnum, phdr)) == NULL
			|| (dl = malloc(sizeof(*dl))) == NULL)
	{
		free(phdr);
		return NULL;
	}
	/* FIXME alignment is hard-coded, offset is not checked */
#ifdef DEBUG
	fprintf(stderr, "DEBUG: mmap(NULL, %d, %d, %d, %d, %d)\n",
			phdr->p_memsz, _do_get_prot(phdr->p_flags),
			MAP_PRIVATE, fd, phdr->p_offset);
#endif
	if((base = mmap(NULL, phdr->p_memsz, _dl_get_prot(phdr->p_flags),
					MAP_PRIVATE, fd, phdr->p_offset))
			== MAP_FAILED)
	{
		free(phdr);
		free(dl);
		return NULL;
	}
	memset(&base[phdr->p_filesz], 0, phdr->p_memsz - phdr->p_filesz);
	free(phdr);
	/* FIXME implement */
	dl->base = base;
	dl->path = strdup(pathname); /* XXX verify accuracy */
	dl->next = NULL;
	dl->prev = NULL;
	dl->length = phdr->p_memsz;
	return dl;
}

static void * _dl_get_load(Elf_Half e_phnum, Elf_Phdr * phdr)
{
	Elf_Half i;
	Elf_Phdr * p = NULL;

	for(i = 0; i < e_phnum; i++)
		if(phdr[i].p_type != PT_LOAD)
			continue;
		else if(phdr[i].p_filesz > phdr[i].p_memsz /* invalid */
				|| p != NULL) /* FIXME only one is supported */
		{
			_dl_errno = DE_INVALID_FILE;
			return NULL;
		}
		else
			p = &phdr[i];
	return p;
}
#endif


/* public */
/* dlclose */
int dlclose(void * handle)
{
	DL * dl;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: dlclose(%p)\n", handle);
#endif
	if(handle == &_dl)
		return 0;
	dl = handle;
	_dl_delete(dl);
	return 0;
}


/* dlerror */
char * dlerror(void)
{
	static char * msg[DE_COUNT] =
	{
		"No error",
		"Is a directory",
		"No such file or directory",
		"Cannot allocate memory",
		"Permission denied",
		"Invalid file format",
		"Not supported",
		"Read error",
		"Unknown error"
	};

	return msg[_dl_errno];
}


/* dlopen */
static DL * _dlopen_do(char const * pathname, int fd, int mode);

void * dlopen(char const * pathname, int mode)
{
	int fd;
	DL * dl;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: dlopen(\"%s\", %d)\n", pathname, mode);
#endif
	if(pathname == NULL)
		return &_dl;
	/* FIXME pathname may be relative to different places */
	if((fd = _dl_open(pathname, O_RDONLY, 0444)) < 0)
		return NULL;
#ifdef DEBUG
	fprintf(stderr, "DEBUG: open(\"%s\", %o) => %d\n", pathname, O_RDONLY,
			fd);
#endif
	dl = _dlopen_do(pathname, fd, mode);
	close(fd);
#ifdef DEBUG
	fprintf(stderr, "DEBUG: dlopen() => %p\n", dl);
#endif
	return dl;
}

static DL * _dlopen_do(char const * pathname, int fd, int mode)
{
	Elf_Ehdr ehdr;
	Elf_Phdr * phdr;
	Elf_Shdr * shdr = NULL;
	DL * dl = NULL;

	if(_dl_read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)
			|| _dl_ehdr_check(&ehdr) != 0)
		return NULL;
	if(ehdr.e_phoff != sizeof(ehdr)
			&& _dl_lseek(fd, ehdr.e_phoff, SEEK_SET) == -1)
		return NULL;
	if((phdr = _dl_read_area(fd, ehdr.e_phnum, ehdr.e_phentsize)) == NULL
			|| _dl_phdr_check(phdr, ehdr.e_phnum) != 0
			|| _dl_lseek(fd, ehdr.e_shoff, SEEK_SET) == -1
			|| (shdr = _dl_read_area(fd, ehdr.e_shnum,
					ehdr.e_shentsize)) == NULL
			|| _dl_shdr_check(shdr, ehdr.e_shnum) != 0
			|| (dl = _dl_new(pathname)) == NULL
			|| _dl_map(dl, fd, phdr, ehdr.e_phnum) != 0)
	{
		if(dl != NULL)
			_dl_delete(dl);
		free(shdr);
		free(phdr);
		return NULL;
	}
	/* FIXME implement */
	free(shdr);
	free(phdr);
	return dl;
#if 0
	if((dl = _dl_malloc(sizeof(*dl))) == NULL)
		return NULL;
	/* FIXME alignment is hard-coded, offset is not checked */
	if((dl->base = mmap(NULL, phdr.p_memsz, _dl_prot(phdr.p_flags),
					MAP_PRIVATE, fd, phdr.p_offset))
			== MAP_FAILED)
	{
		_dl_errno = DE_NOMEM;
		free(dl);
		return NULL;
	}
#ifdef DEBUG
	fprintf(stderr, "DEBUG: mmap(NULL, %llu, %d, %d, %d, %lld) => %p\n",
			phdr.p_memsz, _dl_prot(phdr.p_flags), MAP_PRIVATE, fd,
			phdr.p_offset, dl->base);
#endif
	memset(&dl->base[phdr.p_filesz], 0, phdr.p_memsz - phdr.p_filesz);
	dl->path = strdup(pathname); /* XXX verify accuracy */
	if(_dl.next != NULL)
	{
		_dl.next->prev = dl;
		dl->next = _dl.next;
	}
	else
		dl->next = NULL;
	_dl.next = dl;
	dl->prev = &_dl;
	dl->length = phdr.p_memsz;
	return dl;
#endif
}


/* dlsym */
void * dlsym(void * handle, char const * name)
{
#ifdef DEBUG
	fprintf(stderr, "DEBUG: dlsym(%p, \"%s\")\n", handle, name);
#endif
	/* FIXME implement */
	_dl_errno = DE_NOT_SUPPORTED;
	return NULL;
}
