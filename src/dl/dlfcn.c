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
/* TODO:
   - call pending dlclose() on exit() */



#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#ifdef DEBUG
# include <stdio.h>
#endif
#include <string.h>
#include <limits.h>
#include <errno.h>
#ifdef _LP64
# define ELFSIZE 64
#else
# define ELFSIZE 32
#endif
#include <elf.h>
#include "dlfcn.h"


/* private */
/* types */
typedef struct _DL
{
	int fd;
	char * path;

	char * text_base;
	size_t text_size;
	char * text_addr;
	char * data_base;
	size_t data_size;
	char * data_addr;

	/* internals */
	Elf_Ehdr ehdr;
	Elf_Shdr * shdr;
} DL;

typedef enum _DLError
{
	DE_E_NO_ERROR = 0,
	/* from errno */
	DE_E_INVAL,
	DE_E_ISDIR,
	DE_E_NOENT,
	DE_E_NOMEM,
	DE_E_NOSYS,
	DE_E_PERM,
	/* for dlfcn */
	DE_INVALID_FORMAT,
	DE_UNKNOWN_ERROR
} DLError;
#define DE_E_FIRST	DE_NO_ERROR
#define DE_E_LAST	DE_E_PERM
#define DE_LAST		DE_UNKNOWN_ERROR
#define DE_COUNT	(DE_LAST + 1)


/* constants */
#ifndef _BYTE_ORDER
# warning Assuming big-endian
# define ELFDATA	ELFDATA2MSB
#elif _BYTE_ORDER == _LITTLE_ENDIAN
# define ELFDATA	ELFDATA2LSB
#elif _BYTE_ORDER == _BIG_ENDIAN
# define ELFDATA	ELFDATA2MSB
#endif


/* variables */
static DLError _dl_errno = DE_E_NO_ERROR;

static long int _dl_page_size = -1;


/* prototypes */
static void * _dl_new(char const * pathname);
static void _dl_delete(DL * dl);

/* accessors */
static int _dl_error_set(DLError error, int ret);
static int _dl_error_set_errno(int ret);


/* functions */
/* dl_new */
static int _new_file(DL * dl, char const * pathname);
static int _file_read_ehdr(int fd, Elf_Ehdr * ehdr);
static int _file_read_phdr(int fd, Elf_Phdr * phdr);
static int _file_mmap(DL * dl, Elf_Phdr * phdr);
static int _file_prot(unsigned int flags);

static void * _dl_new(char const * pathname)
{
	DL * dl;

	if((dl = malloc(sizeof(*dl))) == NULL)
	{
		_dl_error_set_errno(0);
		return NULL;
	}
	dl->fd = -1;
	dl->path = NULL;
	dl->text_base = NULL;
	dl->text_size = 0;
	dl->text_addr = NULL;
	dl->data_base = NULL;
	dl->data_size = 0;
	dl->data_addr = NULL;
	dl->shdr = NULL;
	if(pathname == NULL)
		return dl;
	if(_new_file(dl, pathname) != 0)
	{
		_dl_delete(dl);
		return NULL;
	}
	return dl;
}

static int _new_file(DL * dl, char const * pathname)
{
	Elf_Phdr phdr;
	size_t i;
	ssize_t len;

	dl->fd = open(pathname, O_RDONLY);
	dl->path = strdup(pathname);
	if(dl->fd < 0 || dl->path == NULL)
		return _dl_error_set_errno(-1);
	/* read the ELF header */
	if(_file_read_ehdr(dl->fd, &dl->ehdr) != 0)
		return -1;
	/* read the program headers */
	if(lseek(dl->fd, dl->ehdr.e_phoff, SEEK_SET) == -1)
		return _dl_error_set_errno(-1);
	for(i = 0; i < dl->ehdr.e_phnum; i++)
	{
		if(_file_read_phdr(dl->fd, &phdr) != 0)
			return -1;
		if(phdr.p_type != PT_LOAD)
			continue;
		if(_file_mmap(dl, &phdr) != 0)
			return -1;
	}
	/* read the section headers */
	if((len = dl->ehdr.e_shnum * sizeof(*dl->shdr)) < 0) /* XXX relevant? */
		return _dl_error_set(DE_INVALID_FORMAT, -1);
	if(lseek(dl->fd, dl->ehdr.e_shoff, SEEK_SET) == -1
			|| (dl->shdr = malloc(len)) == NULL
			|| read(dl->fd, dl->shdr, len) != len)
		return _dl_error_set_errno(-1);
	return 0;
}

static int _file_read_ehdr(int fd, Elf_Ehdr * ehdr)
{
	if(read(fd, ehdr, sizeof(*ehdr)) != sizeof(*ehdr))
		return _dl_error_set_errno(-1);
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
		return _dl_error_set(DE_INVALID_FORMAT, -1);
	return 0;
}

static int _file_read_phdr(int fd, Elf_Phdr * phdr)
{
	if(read(fd, phdr, sizeof(*phdr)) != sizeof(*phdr))
		return _dl_error_set_errno(-1);
	if(phdr->p_filesz > phdr->p_memsz)
		return _dl_error_set(DE_INVALID_FORMAT, -1);
	return 0;
}

static int _file_mmap(DL * dl, Elf_Phdr * phdr)
{
	int prot;
	char ** base;
	size_t * size;
	char ** addr;
	size_t len;
	off_t offset;

	prot = _file_prot(phdr->p_flags);
	/* FIXME assuming the order here */
	if(dl->text_addr == NULL)
	{
		base = &dl->text_base;
		size = &dl->text_size;
		addr = &dl->text_addr;
	}
	else if(dl->data_addr == NULL)
	{
		base = &dl->data_base;
		size = &dl->data_size;
		addr = &dl->data_addr;
	}
	else
		return _dl_error_set(DE_INVALID_FORMAT, -1);
	len = phdr->p_memsz;
	offset = phdr->p_offset;
#ifdef DEBUG
	fprintf(stderr, "DEBUG: mmap(%p, 0x%zx, %d, %d, %d, 0x%zx)\n", NULL,
			len, prot, MAP_PRIVATE, dl->fd, offset);
#endif
	if((*base = mmap(NULL, len, prot, MAP_PRIVATE, dl->fd, offset))
			== MAP_FAILED)
		return _dl_error_set_errno(-1);
	*size = len;
	*addr = *base - phdr->p_vaddr;
#ifdef DEBUG
	fprintf(stderr, "DEBUG: base=%p, size=0x%zx, addr=%p\n", *base, *size,
			*addr);
#endif
	/* FIXME will be wrong with page alignment handling */
	memset((*base) + phdr->p_filesz, 0, phdr->p_memsz - phdr->p_filesz);
	return 0;
}

static int _file_prot(unsigned int flags)
{
	int prot;

	prot = flags & PF_R ? PROT_READ : 0;
	prot |= flags & PF_W ? PROT_WRITE : 0;
	prot |= flags & PF_X ? PROT_EXEC : 0;
	return prot;
}


/* dl_delete */
static void _dl_delete(DL * dl)
{
	free(dl->path);
	free(dl->shdr);
	if(dl->text_base != NULL)
		munmap(dl->text_base, dl->text_size);
	if(dl->data_base != NULL)
		munmap(dl->data_base, dl->data_size);
	if(dl->fd >= 0)
		close(dl->fd);
	free(dl);
}


/* accessors */
/* dl_error_set */
static int _dl_error_set(DLError error, int ret)
{
	_dl_errno = error;
	return ret;
}


/* dl_error_set_errno */
static int _dl_error_set_errno(int ret)
{
	switch(errno)
	{
		case EINVAL:
			_dl_errno = DE_E_INVAL;
			break;
		case EISDIR:
			_dl_errno = DE_E_ISDIR;
			break;
		case ENOENT:
			_dl_errno = DE_E_NOENT;
			break;
		case ENOMEM:
			_dl_errno = DE_E_NOMEM;
			break;
		case ENOSYS:
			_dl_errno = DE_E_NOSYS;
			break;
		case EPERM:
			_dl_errno = DE_E_PERM;
			break;
		default:
			_dl_errno = DE_UNKNOWN_ERROR;
			break;
	}
	return ret;
}


/* public */
/* dlclose */
int dlclose(void * handle)
{
	DL * dl = handle;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: dlclose(%p)\n", handle);
#endif
	_dl_delete(dl);
	return 0;
}


/* dlerror */
char * dlerror(void)
{
	static struct
	{
		DLError error;
		char * string;
	} es[] = {
		{ DE_INVALID_FORMAT,	"Invalid file format"	},
		{ 0,			"Unknown error"		}
	};
	size_t i;

#if DE_E_FIRST == 0
	if(_dl_errno <= DE_E_LAST)
#else
	if(_dl_errno >= DE_E_FIRST && _dl_errno <= DE_E_LAST)
#endif
		return strerror(errno);
	for(i = 0; es[i].error != 0; i++)
		if(es[i].error == _dl_errno)
			break;
	return es[i].string;
}


/* dlopen */
void * dlopen(char const * pathname, int mode)
{
	DL * dl;

	if(_dl_page_size < 0 && (_dl_page_size = sysconf(_SC_PAGESIZE)) < 0)
	{
		_dl_error_set_errno(0);
		return NULL;
	}
	if((dl = _dl_new(pathname)) == NULL)
		return NULL;
	return dl;
}


/* dlsym */
static char * _sym_read_strtab(int fd, off_t offset, size_t len);
static void * _sym_lookup(DL * dl, Elf_Shdr * shdr, char const * name,
		char const * strings, size_t strings_cnt);

void * dlsym(void * handle, char const * name)
{
	void * ret = NULL;
	DL * dl = handle;
	size_t i;
	size_t len;
	Elf_Shdr * shdr = dl->shdr;
	unsigned int strtab;
	char * strings = NULL;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: dlsym(%p, \"%s\")\n", handle, name);
#endif
	if(dl->fd == -1)
	{
		/* FIXME implement dlopen(NULL) */
		errno = ENOSYS;
		_dl_error_set_errno(0);
		return NULL;
	}
	for(i = 0; i < dl->ehdr.e_shnum; i++)
	{
		if(shdr[i].sh_type != SHT_SYMTAB)
			continue;
		/* sanity checks */
		strtab = shdr[i].sh_link;
		if(shdr[i].sh_entsize != sizeof(Elf_Sym)
				|| shdr[i].sh_link >= dl->ehdr.e_shnum
				|| shdr[strtab].sh_type != SHT_STRTAB)
		{
			_dl_error_set(DE_INVALID_FORMAT, 0);
			break;
		}
		/* read the complete string section */
		len = shdr[strtab].sh_size;
		if((strings = _sym_read_strtab(dl->fd, shdr[strtab].sh_offset,
						len)) == NULL)
			break;
		if((ret = _sym_lookup(dl, &shdr[i], name, strings, len))
				== NULL)
			break;
		free(strings);
		strings = NULL;
	}
	free(strings);
	return ret;
}

static char * _sym_read_strtab(int fd, off_t offset, size_t len)
{
	ssize_t slen = len;
	char * strings;

	if(len >= INT_MAX - 1)
	{
		_dl_error_set(DE_INVALID_FORMAT, 0);
		return NULL;
	}
	if(lseek(fd, offset, SEEK_SET) == -1
			|| (strings = malloc(slen + 1)) == NULL
			|| read(fd, strings, slen) != slen)
	{
		_dl_error_set_errno(0);
		return NULL;
	}
	strings[slen] = '\0';
	return strings;
}

static void * _sym_lookup(DL * dl, Elf_Shdr * shdr, char const * name,
		char const * strings, size_t strings_cnt)
{
	size_t i;
	Elf_Sym sym;

	if(lseek(dl->fd, shdr->sh_offset, SEEK_SET) == -1)
	{
		_dl_error_set_errno(0);
		return NULL;
	}
	for(i = 0; i < shdr->sh_size / sizeof(sym); i++)
	{
		if(read(dl->fd, &sym, sizeof(sym)) != sizeof(sym))
		{
			_dl_error_set_errno(0);
			break;
		}
		if(sym.st_name >= strings_cnt)
		{
			_dl_error_set(DE_INVALID_FORMAT, 0);
			break;
		}
		if(strcmp(&strings[sym.st_name], name) != 0)
			continue;
		/* found the symbol */
		if(sym.st_shndx >= dl->ehdr.e_shnum)
		{
			_dl_error_set(DE_INVALID_FORMAT, 0);
			break;
		}
#ifdef DEBUG
		printf("symbol: %s, section: %u, value: 0x%x, size: 0x%x\n",
				&strings[sym.st_name], sym.st_shndx,
				sym.st_value, sym.st_size);
#endif
		/* FIXME it is relative to the section */
		return (void*)(sym.st_value + dl->data_addr);
	}
	return NULL;
}
