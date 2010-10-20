/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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
 * - call pending dlclose() on exit() */



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
	Elf_Sym * symtab;
	size_t symtab_cnt;
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
	DE_SYMBOL_NOT_FOUND,
	DE_UNKNOWN_ERROR
} DLError;
#define DE_E_FIRST	DE_NO_ERROR
#define DE_E_LAST	DE_E_PERM
#define DE_LAST		DE_UNKNOWN_ERROR
#define DE_COUNT	(DE_LAST + 1)


/* constants */
/* XXX probably belongs somewhere else (some header file) */
#ifndef _BYTE_ORDER
# if defined(__amd64__)
#  define _BYTE_ORDER	_LITTLE_ENDIAN
# elif defined(__arm__)
#  warning Assuming ARM is little-endian
#  define _BYTE_ORDER	_LITTLE_ENDIAN
# elif defined(__i386__)
#  define _BYTE_ORDER	_LITTLE_ENDIAN
# elif defined(__sparc__)
#  define _BYTE_ORDER	_BIG_ENDIAN
# endif
#endif

#ifndef _BYTE_ORDER
# warning Assuming little-endian
# define ELFDATA	ELFDATA2LSB
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

/* useful */
static void * _dl_load(DL * dl, off_t offset, size_t size);
static int _dl_strtab(DL * dl, Elf_Word index, char ** strtab,
		size_t * strtab_cnt);
static char const * _dl_strtab_string(char const * strtab, size_t strtab_cnt,
		Elf64_Xword index);
static int _dl_symtab(DL * dl, Elf_Word index, Elf_Word type, Elf_Sym ** symtab,
		size_t * symtab_cnt);


/* functions */
/* dl_new */
static int _new_file(DL * dl, char const * pathname);
static int _file_read_ehdr(int fd, Elf_Ehdr * ehdr);
static int _file_mmap(DL * dl, Elf_Phdr * phdr);
static int _file_prot(unsigned int flags);
static int _file_symbols(DL * dl);
static int _file_relocations(DL * dl);

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
	dl->symtab = NULL;
	dl->symtab_cnt = 0;
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
	Elf_Phdr * phdr;
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
	if((phdr = _dl_load(dl, dl->ehdr.e_phoff, sizeof(*phdr)
					* dl->ehdr.e_phnum)) == NULL)
		return -1;
	for(i = 0; i < dl->ehdr.e_phnum; i++)
	{
		if(phdr[i].p_type != PT_LOAD)
			continue;
		if(phdr[i].p_filesz > phdr[i].p_memsz)
		{
			free(phdr);
			return _dl_error_set(DE_INVALID_FORMAT, -1);
		}
		if(_file_mmap(dl, &phdr[i]) == 0)
			continue;
		free(phdr);
		return -1;
	}
	free(phdr);
	/* read the section headers */
	if((len = dl->ehdr.e_shnum * sizeof(*dl->shdr)) < 0) /* XXX relevant? */
		return _dl_error_set(DE_INVALID_FORMAT, -1);
	if((dl->shdr = _dl_load(dl, dl->ehdr.e_shoff, len)) == NULL)
		return -1;
	if(_file_symbols(dl) != 0 || _file_relocations(dl) != 0)
		return -1;
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
	fprintf(stderr, "DEBUG: mmap(%p, 0x%lx, %d, %d, %d, 0x%lx)\n", NULL,
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

static int _file_symbols(DL * dl)
{
	size_t i;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	for(i = 0; i < dl->ehdr.e_shnum; i++)
		if(dl->shdr[i].sh_type == SHT_SYMTAB)
			break;
	if(i == dl->ehdr.e_shnum)
		return 0; /* XXX is this an error? */
	/* FIXME check that there is only one symbol table */
	return _dl_symtab(dl, i, SHT_SYMTAB, &dl->symtab, &dl->symtab_cnt);
}

static int _file_relocations(DL * dl)
{
	size_t i;
	Elf_Shdr * shdr;
	size_t j;
	Elf_Rela * rela = NULL;
	Elf_Rel * rel;
	Elf_Sym * symtab;
	size_t symtab_cnt;
	char * strtab;
	size_t strtab_cnt;
	Elf_Sym * sym;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	for(i = 0; i < dl->ehdr.e_shnum; i++)
	{
		shdr = &dl->shdr[i];
		if((shdr->sh_type != SHT_RELA
					|| shdr->sh_entsize != sizeof(*rela))
				&& (shdr->sh_type != SHT_REL
					|| shdr->sh_entsize != sizeof(*rel)))
			continue;
		if((rela = _dl_load(dl, shdr->sh_offset, shdr->sh_size))
				== NULL)
			break;
		if(_dl_symtab(dl, shdr->sh_link, SHT_DYNSYM, &symtab,
					&symtab_cnt) != 0)
			break;
		if(_dl_strtab(dl, dl->shdr[shdr->sh_link].sh_link, &strtab,
					&strtab_cnt) != 0)
		{
			free(symtab);
			break;
		}
		for(j = 0; j < shdr->sh_size; j+=shdr->sh_entsize)
		{
			rel = (Elf_Rel*)(((char*)rela) + j);
			if(ELF_R_SYM(rel->r_info) >= symtab_cnt)
				break; /* XXX */
			sym = &symtab[ELF_R_SYM(rel->r_info)];
#ifdef DEBUG
			fprintf(stderr, "DEBUG: %s() Relocating \"%s\"\n",
					__func__, _dl_strtab_string(strtab,
						strtab_cnt, sym->st_name));
#endif
			switch(ELF_R_TYPE(rel->r_info))
			{
#if defined(__amd64__)
				case R_X86_64_RELATIVE:
				case R_X86_64_GLOB_DAT:
					/* FIXME implement */
					break;
				case R_X86_64_JUMP_SLOT:
					/* FIXME implement */
					break;
#elif defined(__i386__)
				case R_386_32:
				case R_386_PC32:
					/* FIXME implement */
					break;
#endif
			}
		}
		free(strtab);
		free(symtab);
	}
	free(rela);
	return 0;
}


/* dl_delete */
static void _dl_delete(DL * dl)
{
	free(dl->path);
	free(dl->shdr);
	free(dl->symtab);
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


/* dl_section */
static void * _dl_load(DL * dl, off_t offset, size_t size)
{
	void * ret;
	ssize_t ssize;

	if(lseek(dl->fd, offset, SEEK_SET) != offset
			|| (ret = malloc(size)) == NULL)
	{
		_dl_error_set_errno(1);
		return NULL;
	}
	if((ssize = read(dl->fd, ret, size)) <= 0
			|| (size_t)ssize != size)
	{
		free(ret);
		_dl_error_set_errno(1);
		return NULL;
	}
	return ret;
}


/* dl_strtab */
static int _dl_strtab(DL * dl, Elf_Word index, char ** strtab,
		size_t * strtab_cnt)
{
	Elf_Shdr * shdr;

	if(index >= dl->ehdr.e_shnum || dl->shdr[index].sh_type != SHT_STRTAB)
		return -_dl_error_set(DE_INVALID_FORMAT, 1);
	shdr = &dl->shdr[index];
	if((*strtab = _dl_load(dl, shdr->sh_offset, shdr->sh_size)) == NULL)
		return -1;
	if((*strtab)[shdr->sh_size - 1] != '\0')
	{
		free(*strtab);
		return -_dl_error_set(DE_INVALID_FORMAT, 1);
	}
	*strtab_cnt = shdr->sh_size;
	return 0;
}


/* dl_strtab_string */
static char const * _dl_strtab_string(char const * strtab, size_t strtab_cnt,
		Elf64_Xword index)
{
	if(index >= strtab_cnt || strtab == NULL || strtab_cnt == 0)
	{
		_dl_error_set(DE_INVALID_FORMAT, 1);
		return NULL;
	}
	if(index == STN_UNDEF)
		return "";
	return &strtab[index];
}


/* dl_symtab */
static int _dl_symtab(DL * dl, Elf_Word index, Elf_Word type, Elf_Sym ** symtab,
		size_t * symtab_cnt)
{
	Elf_Shdr * shdr;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s(%p, %u, %u, symtab, symtab_cnt)\n", __func__,
			dl, index, type);
#endif
	if(index >= dl->ehdr.e_shnum)
		return -_dl_error_set(DE_INVALID_FORMAT, 1);
	shdr = &dl->shdr[index];
	if(shdr->sh_type != type || shdr->sh_entsize != sizeof(**symtab))
		return -_dl_error_set(DE_INVALID_FORMAT, 1);
	if((*symtab = _dl_load(dl, shdr->sh_offset, shdr->sh_size)) == NULL)
		return -1;
	*symtab_cnt = shdr->sh_size / shdr->sh_entsize;
	return 0;
}


/* public */
/* dlclose */
int dlclose(void * handle)
{
	DL * dl = handle;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s(%p)\n", __func__, handle);
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
		{ DE_SYMBOL_NOT_FOUND,	"Symbol not found"	},
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
static void * _sym_lookup(DL * dl, Elf_Shdr * shdr, char const * name,
		char const * strings, size_t strings_cnt);

void * dlsym(void * handle, char const * name)
{
	DL * dl = handle;
	void * ret;
	size_t i;
	size_t len;
	Elf_Shdr * shdr = dl->shdr;
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
		if(shdr[i].sh_entsize != sizeof(Elf_Sym))
		{
			_dl_error_set(DE_INVALID_FORMAT, 0);
			break;
		}
		/* read the complete string section */
		if(_dl_strtab(dl, shdr[i].sh_link, &strings, &len) != 0)
			break;
		ret = _sym_lookup(dl, &shdr[i], name, strings, len);
		free(strings);
		if(ret != NULL)
			return ret;
	}
	return NULL;
}

static void * _sym_lookup(DL * dl, Elf_Shdr * shdr, char const * name,
		char const * strtab, size_t strtab_cnt)
{
	size_t i;
	Elf_Sym * sym;
	char const * p;

	for(i = 0; i < dl->symtab_cnt; i++)
	{
		sym = &dl->symtab[i];
		if((p = _dl_strtab_string(strtab, strtab_cnt, sym->st_name))
				== NULL)
			break;
		if(strcmp(p, name) != 0)
			continue;
		/* found the symbol */
		if(sym->st_shndx >= dl->ehdr.e_shnum)
		{
			_dl_error_set(DE_INVALID_FORMAT, 0);
			break;
		}
#ifdef DEBUG
		fprintf(stderr, "DEBUG: %s() symbol: %s, section: %u, type=%x"
				", value: 0x%x, size: 0x%x\n", __func__,
				&strtab[sym->st_name],
				sym->st_shndx, ELF_ST_TYPE(sym->st_info),
				sym->st_value, sym->st_size);
#endif
		/* FIXME handle only known types */
		if(ELF_ST_TYPE(sym->st_info) == STT_FUNC)
			return (void*)(sym->st_value + dl->text_addr);
		return (void*)(sym->st_value + dl->data_addr);
	}
	_dl_error_set(DE_SYMBOL_NOT_FOUND, 0);
	return NULL;
}
