/* $Id$ */
/* Copyright (c) 2007-2020 Pierre Pronchery <khorben@defora.org> */
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
#include <dl/elf.h>
#include "endian.h"
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
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
# define ELFDATA	ELFDATA2MSB
#else
# define ELFDATA	ELFDATA2LSB
#endif


/* variables */
static DLError _dl_errno = DE_E_NO_ERROR;

static long int _dl_page_size = -1;

static Elf_Phdr * _dl_phdr = NULL;
static uint16_t _dl_phentsize = 0;
static uint16_t _dl_phnum = 0;
static void * _dl_str = NULL;


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
static int _new_self(DL * dl);
static int _new_self_dynamic(DL * dl, Elf_Phdr * phdr);
static int _file_read_ehdr(int fd, Elf_Ehdr * ehdr);
static int _file_mmap(DL * dl, Elf_Phdr * phdr, int prot, char ** base,
		size_t * size, char ** addr);
static int _file_prot(unsigned int flags);
static int _file_symbols(DL * dl);
static int _file_relocations(DL * dl);
static void _file_relocations_arch(DL * dl, Elf_Rela * rela,
		char const * strtab, size_t strtab_cnt, Elf_Sym * sym);

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
	if((pathname == NULL && _new_self(dl) != 0)
			|| (pathname != NULL && _new_file(dl, pathname) != 0))
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
	int prot;
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
		prot = _file_prot(phdr[i].p_flags);
		/* enforce W^X */
		if((prot & (PROT_WRITE | PROT_EXEC))
				== (PROT_WRITE | PROT_EXEC))
		{
			free(phdr);
			return _dl_error_set(DE_INVALID_FORMAT, -1);
		}
		if(prot == (PROT_READ | PROT_EXEC))
		{
			if(dl->text_addr != NULL)
			{
				free(phdr);
				return _dl_error_set(DE_INVALID_FORMAT, -1);
			}
			if(_file_mmap(dl, &phdr[i], prot, &dl->text_base,
						&dl->text_size,
						&dl->text_addr) == 0)
				continue;
		}
		else if(phdr[i].p_memsz > 0)
		{
			if(dl->data_addr != NULL)
			{
				free(phdr);
				return _dl_error_set(DE_INVALID_FORMAT, -1);
			}
			if(_file_mmap(dl, &phdr[i], prot, &dl->data_base,
						&dl->data_size,
						&dl->data_addr) == 0)
				continue;
		}
		else
			_dl_error_set(DE_INVALID_FORMAT, -1);
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

static int _new_self(DL * dl)
{
	size_t i;

	if(_dl_phdr == NULL)
		return _dl_error_set(DE_UNKNOWN_ERROR, -1);
	if(_dl_phentsize != sizeof(Elf_Phdr))
		return _dl_error_set(DE_INVALID_FORMAT, -1);
	/* obtain the base address */
	for(i = 0; i < _dl_phnum; i++)
	{
		if(_dl_phdr[i].p_filesz > _dl_phdr[i].p_memsz)
			return _dl_error_set(DE_INVALID_FORMAT, -1);
		if(_dl_phdr[i].p_type != PT_PHDR)
			continue;
		dl->data_addr = (char *)_dl_phdr - _dl_phdr[i].p_vaddr;
		dl->text_addr = (char *)_dl_phdr - _dl_phdr[i].p_vaddr;
#ifdef DEBUG
		fprintf(stderr, "DEBUG: %s() addr=%p\n", __func__,
				dl->data_addr);
#endif
		break;
	}
	for(i = 0; i < _dl_phnum; i++)
	{
		switch(_dl_phdr[i].p_type)
		{
			case PT_DYNAMIC:
				if(_new_self_dynamic(dl, &_dl_phdr[i]) != 0)
					return -1;
				return 0;
		}
	}
	return _dl_error_set(DE_INVALID_FORMAT, -1);
}

static int _new_self_dynamic(DL * dl, Elf_Phdr * phdr)
{
	Elf_Dyn * dyn;

	/* FIXME also check for the size */
	for(dyn = (Elf_Dyn *)(dl->data_addr + phdr->p_vaddr);
			dyn->d_tag != DT_NULL; dyn++)
		switch(dyn->d_tag)
		{
			case DT_STRTAB:
#ifdef __linux__
				_dl_str = dyn->d_un.d_ptr;
#else
				_dl_str = dl->data_addr + dyn->d_un.d_ptr;
#endif
				break;
			case DT_STRSZ:
				dl->symtab_cnt = dyn->d_un.d_val;
				break;
			case DT_SYMENT:
				if(dyn->d_un.d_val != sizeof(Elf_Sym))
					return _dl_error_set(DE_INVALID_FORMAT,
							-1);
				break;
			case DT_SYMTAB:
#ifdef __linux__
				dl->symtab = (Elf_Sym *)dyn->d_un.d_ptr;
#else
				dl->symtab = (Elf_Sym *)(dl->data_addr
						+ dyn->d_un.d_ptr);
#endif
				break;
#ifdef DEBUG
			default:
				fprintf(stderr, "DEBUG: %s() %d (0x%x)\n",
						__func__, dyn->d_tag,
						dyn->d_un.d_val);
				break;
#endif
		}
	/* sanity checks */
	if(dl->symtab_cnt != 0 && _dl_str == NULL)
	{
		dl->symtab_cnt = 0;
		return _dl_error_set(DE_INVALID_FORMAT, -1);
	}
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

static int _file_mmap(DL * dl, Elf_Phdr * phdr, int prot, char ** base,
		size_t * size, char ** addr)
{
	int flags;
	size_t len;
	off_t offset;

	flags = (prot & PROT_WRITE) ? MAP_PRIVATE : MAP_SHARED;
	len = phdr->p_memsz;
	offset = phdr->p_offset;
#ifdef DEBUG
	fprintf(stderr, "DEBUG: mmap(%p, 0x%lx, %d, %d, %d, 0x%lx)\n", NULL,
			len, prot, flags, dl->fd, offset);
#endif
	if((*base = mmap(NULL, len, prot, flags, dl->fd, offset)) == MAP_FAILED)
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
	for(i = SHN_UNDEF + 1; i < dl->ehdr.e_shnum; i++)
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
	Elf_Rel * rel = NULL;
	size_t j;
	Elf_Rela rela;
	Elf_Sym * symtab;
	size_t symtab_cnt;
	char * strtab;
	size_t strtab_cnt;
	Elf_Sym * sym;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s()\n", __func__);
#endif
	for(i = SHN_UNDEF + 1; i < dl->ehdr.e_shnum; i++)
	{
		shdr = &dl->shdr[i];
		if((shdr->sh_type != SHT_REL
					|| shdr->sh_entsize != sizeof(*rel))
				&& (shdr->sh_type != SHT_RELA
					|| shdr->sh_entsize != sizeof(rela)))
			continue;
		if((rel = _dl_load(dl, shdr->sh_offset, shdr->sh_size))
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
		for(j = 0; j < shdr->sh_size; j += shdr->sh_entsize)
		{
			rela.r_addend = 0;
			memcpy(&rela, (char *)rel + j, shdr->sh_entsize);
			if(ELF_R_SYM(rela.r_info) >= symtab_cnt)
				break; /* XXX */
			sym = &symtab[ELF_R_SYM(rela.r_info)];
			_file_relocations_arch(dl, &rela, strtab, strtab_cnt,
					sym);
		}
		free(strtab);
		free(symtab);
	}
	free(rel);
	return 0;
}

static void _file_relocations_arch(DL * dl, Elf_Rela * rela,
		char const * strtab, size_t strtab_cnt, Elf_Sym * sym)
{
#ifndef DEBUG
	(void) strtab;
	(void) strtab_cnt;
	(void) sym;

#endif
#if defined(__amd64__)
	Elf_Addr * addr;

	switch(ELF_R_TYPE(rela->r_info))
	{
		case R_X86_64_NONE:
			break;
		case R_X86_64_RELATIVE:
		case R_X86_64_GLOB_DAT:
			/* FIXME implement */
			break;
		case R_X86_64_JUMP_SLOT:
# ifdef DEBUG
			fprintf(stderr, "DEBUG: %s() Relocating \"%s\""
					" (0x%lx 0x%lx 0x%lx)\n",
					__func__, _dl_strtab_string(strtab,
						strtab_cnt, sym->st_name),
					ELF_R_SYM(rela->r_info),
					rela->r_offset, rela->r_addend);
			fprintf(stderr, "DEBUG: name 0x%lx value 0x%lx\n",
					sym->st_name, sym->st_value);
			fprintf(stderr, "DEBUG: %s() base=0x%lx, addr=0x%lx"
					", offset=0x%lx\n", __func__,
					dl->data_base, dl->data_addr,
					rela->r_offset);
# endif
			addr = dl->data_addr + rela->r_offset;
# ifdef DEBUG
			fprintf(stderr, "*0x%lx = 0x%lx + 0x%lx\n", addr,
					dl->data_base, rela->r_addend);
# endif
			*addr = (intptr_t)dl->text_base + rela->r_addend;
			break;
	}
#elif defined(__i386__)
	Elf_Addr * addr;

	switch(ELF_R_TYPE(rela->r_info))
	{
		case R_386_NONE:
			break;
		case R_386_32:
		case R_386_PC32:
			/* FIXME implement */
			break;
		case R_386_RELATIVE:
			addr = (Elf_Addr *)(dl->data_addr + rela->r_offset);
			*addr += dl->data_addr;
			break;
	}
#endif
}


/* dl_delete */
static void _dl_delete(DL * dl)
{
	free(dl->path);
	free(dl->shdr);
	if(dl->fd >= 0)
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


/* useful */
/* dl_load */
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


/* protected */
/* start_dlfcn */
void __start_dlfcn(AuxInfo * auxv)
{
	for(;; auxv++)
		switch(auxv->a_type)
		{
			case AT_NULL:
				return;
			case AT_PAGESZ:
				_dl_page_size = auxv->a_v;
				break;
			case AT_PHDR:
				_dl_phdr = (Elf_Phdr *)auxv->a_v;
				break;
			case AT_PHENT:
				_dl_phentsize = auxv->a_v;
				break;
			case AT_PHNUM:
				_dl_phnum = auxv->a_v;
				break;
			case AT_IGNORE:
			default:
				break;
		}
}


/* public */
/* dlclose */
int __dlclose(void * handle)
{
	DL * dl = handle;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s(%p)\n", __func__, handle);
#endif
	_dl_delete(dl);
	return 0;
}


/* dlerror */
char * __dlerror(void)
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
void * __dlopen(char const * pathname, int mode)
{
	(void) mode;

	if(_dl_page_size < 0 && (_dl_page_size = sysconf(_SC_PAGESIZE)) < 0)
	{
		_dl_error_set_errno(0);
		return NULL;
	}
	return _dl_new(pathname);
}


/* dlsym */
static void * _sym_lookup(DL * dl, char const * name, char const * strings,
		size_t strings_cnt);

void * __dlsym(void * handle, char const * name)
{
	DL * dl = handle;
	void * ret;
	size_t i;
	size_t len;
	Elf_Shdr * shdr;
	char * strings = NULL;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: dlsym(%p, \"%s\")\n", handle, name);
#endif
	if(dl->fd == -1)
	{
		if(dl->symtab_cnt == 0)
		{
			errno = ENOSYS;
			_dl_error_set_errno(0);
			return NULL;
		}
#ifdef DEBUG
		fprintf(stderr, "DEBUG: %p %p\n", dl->text_addr, dl->data_addr);
		ret = _sym_lookup(dl, name, _dl_str, dl->symtab_cnt);
		fprintf(stderr, "DEBUG: %s(\"%s\") => %p\n", __func__, name,
				ret);
		return ret;
#else
		return _sym_lookup(dl, name, _dl_str, dl->symtab_cnt);
#endif
	}
	shdr = dl->shdr;
	for(i = SHN_UNDEF + 1; i < dl->ehdr.e_shnum; i++)
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
		ret = _sym_lookup(dl, name, strings, len);
		free(strings);
		if(ret != NULL)
			return ret;
	}
	return NULL;
}

static void * _sym_lookup(DL * dl, char const * name, char const * strtab,
		size_t strtab_cnt)
{
	void * ret = NULL;
	size_t i;
	Elf_Sym * sym;
	char const * p;

	for(i = STN_UNDEF + 1; i < dl->symtab_cnt; i++)
	{
		sym = &dl->symtab[i];
		if((p = _dl_strtab_string(strtab, strtab_cnt, sym->st_name))
				== NULL)
			return NULL;
#ifdef DEBUG
		if(dl->fd == -1)
			fprintf(stderr, "DEBUG: symbol \"%s\"\n", p);
#endif
		if(strcmp(p, name) != 0)
			continue;
		/* found the symbol */
		if(dl->fd != -1 && sym->st_shndx >= dl->ehdr.e_shnum)
		{
			_dl_error_set(DE_INVALID_FORMAT, 0);
			return NULL;
		}
#ifdef DEBUG
		fprintf(stderr, "DEBUG: %s() symbol: %s, section: %u, type=%x,"
				" bind=%d, value: 0x%x, size: 0x%x\n",
				__func__, &strtab[sym->st_name], sym->st_shndx,
				ELF_ST_TYPE(sym->st_info),
				ELF_ST_BIND(sym->st_info),
				sym->st_value, sym->st_size);
#endif
		/* FIXME handle only known types */
		if(ELF_ST_TYPE(sym->st_info) == STT_FUNC)
			ret = (void *)(sym->st_value + dl->text_addr);
		else
			ret = (void *)(sym->st_value + dl->data_addr);
		if(ELF_ST_BIND(sym->st_info) != STB_WEAK)
			return ret;
	}
	if(ret == NULL)
		_dl_error_set(DE_SYMBOL_NOT_FOUND, 0);
	return ret;
}
