/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_ELF_H
# define LIBC_ELF_H

# include <stdint.h>


/* types */
/* helpers */
# ifdef ELFSIZE
#  if ELFSIZE == 32
#   define ELFCLASS ELFCLASS32
#   define ELF_R_SYM(info) ELF32_R_SYM(info)
#   define ELF_R_TYPE(info) ELF32_R_TYPE(info)
#   define ELF_ST_TYPE(info) ELF32_ST_TYPE(info)
#   define Elf_Addr Elf32_Addr
#   define Elf_Dyn  Elf32_Dyn
#   define Elf_Ehdr Elf32_Ehdr
#   define Elf_Off  Elf32_Off
#   define Elf_Phdr Elf32_Phdr
#   define Elf_Shdr Elf32_Shdr
#   define Elf_Rel  Elf32_Rel
#   define Elf_Rela Elf32_Rela
#   define Elf_Sym  Elf32_Sym
#   define Elf_Word Elf32_Word
#  elif ELFSIZE == 64
#   define ELFCLASS ELFCLASS64
#   define ELF_R_SYM(info) ELF64_R_SYM(info)
#   define ELF_R_TYPE(info) ELF64_R_TYPE(info)
#   define ELF_ST_TYPE(info) ELF32_ST_TYPE(info)
#   define Elf_Addr Elf64_Addr
#   define Elf_Dyn  Elf64_Dyn
#   define Elf_Ehdr Elf64_Ehdr
#   define Elf_Off  Elf64_Off
#   define Elf_Phdr Elf64_Phdr
#   define Elf_Shdr Elf64_Shdr
#   define Elf_Rel  Elf64_Rel
#   define Elf_Rela Elf64_Rela
#   define Elf_Sym  Elf64_Sym
#   define Elf_Word Elf64_Word
#  endif /* ELFSIZE == 64 */
# endif /* ELFSIZE */

/* common */
typedef uint8_t Elf_Byte;

/* Elf32 */
typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf32_Word;

/* Elf64 */
typedef uint64_t Elf64_Addr;
typedef uint32_t Elf64_Half;
typedef uint64_t Elf64_Off;
typedef uint16_t Elf64_Quarter;
typedef int32_t Elf64_Shalf;
typedef int64_t Elf64_Sxword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;

/* Elf_Ehdr */
# define EI_MAG0	0
# define EI_MAG1	1
# define EI_MAG2	2
# define EI_MAG3	3
# define EI_CLASS	4
# define EI_DATA	5
# define EI_VERSION	6
# define EI_PAD		7
# define EI_NIDENT	16
/* mag */
# define ELFMAG0	0x7f
# define ELFMAG1	'E'
# define ELFMAG2	'L'
# define ELFMAG3	'F'
# define ELFMAG		"\177ELF"
# define SELFMAG	4
/* class */
# define ELFCLASSNONE	0
# define ELFCLASS32	1
# define ELFCLASS64	2
/* data */
# define ELFDATANONE	0
# define ELFDATA2LSB	1
# define ELFDATA2MSB	2
/* version */
# define EV_NONE	0
# define EV_CURRENT	1
/* type */
# define ET_NONE	0
# define ET_REL		1
# define ET_EXEC	2
# define ET_DYN		3
# define ET_CORE	4
# define ET_LOPROC	0xff00
# define ET_HIPROC	0xffff
/* machine */
# define EM_NONE	0
# define EM_M32		1
# define EM_SPARC	2
# define EM_386		3
# define EM_68K		4
# define EM_88K		5
# define EM_860		7
# define EM_MIPS	8
# define EM_ARM		40
# define EM_SPARCV9	43
# define EM_X86_64	62

typedef struct _Elf32_Ehdr
{
	unsigned char e_ident[EI_NIDENT];
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Addr e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
} Elf32_Ehdr;

typedef struct _Elf64_Ehdr
{
	unsigned char e_ident[EI_NIDENT];
	Elf64_Quarter e_type;
	Elf64_Quarter e_machine;
	Elf64_Half e_version;
	Elf64_Addr e_entry;
	Elf64_Off e_phoff;
	Elf64_Off e_shoff;
	Elf64_Half e_flags;
	Elf64_Quarter e_ehsize;
	Elf64_Quarter e_phentsize;
	Elf64_Quarter e_phnum;
	Elf64_Quarter e_shentsize;
	Elf64_Quarter e_shnum;
	Elf64_Quarter e_shstrndx;
} Elf64_Ehdr;

/* Elf_Shdr */
/* type */
# define SHT_NULL	0
# define SHT_PROGBIGS	1
# define SHT_SYMTAB	2
# define SHT_STRTAB	3
# define SHT_RELA	4
# define SHT_HASH	5
# define SHT_DYNAMIC	6
# define SHT_NOTE	7
# define SHT_NOBITS	8
# define SHT_REL	9
# define SHT_SHLIB	10
# define SHT_DYNSYM	11

typedef struct _Elf32_Shdr
{
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
} Elf32_Shdr;

typedef struct _Elf64_Shdr
{
	Elf64_Half sh_name;
	Elf64_Half sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	Elf64_Xword sh_size;
	Elf64_Half sh_link;
	Elf64_Half sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
} Elf64_Shdr;

/* Elf_Phdr */
/* type */
# define PT_NULL	0
# define PT_LOAD	1
# define PT_DYNAMIC	2
# define PT_INTERP	3
# define PT_NOTE	4
# define PT_SHLIB	5
# define PT_PHDR	6
# define PT_LOPROC	0x70000000
# define PT_HIPROC	0x7fffffff
/* flags */
# define PF_R		0x4
# define PF_W		0x2
# define PF_X		0x1

typedef struct _Elf32_Phdr
{
	Elf32_Word p_type;
	Elf32_Off p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_memsz;
	Elf32_Word p_flags;
	Elf32_Word p_align;
} Elf32_Phdr;

typedef struct _Elf64_Phdr
{
	Elf64_Half p_type;
	Elf64_Half p_flags;
	Elf64_Off p_offset;
	Elf64_Addr p_vaddr;
	Elf64_Addr p_paddr;
	Elf64_Xword p_filesz;
	Elf64_Xword p_memsz;
	Elf64_Xword p_align;
} Elf64_Phdr;

/* Elf_Rel */
# define ELF32_R_SYM(info) ((info) >> 8)
# define ELF32_R_TYPE(info) ((info) & 0xf)
# define R_386_NONE		0
# define R_386_32		1
# define R_386_PC32		2
# define R_386_GOT32		3
# define R_386_PLT32		4
# define R_386_COPY		5
# define R_386_GLOB_DAT		6
# define R_386_JMP_SLOT		7
# define R_386_RELATIVE		8
# define R_386_GOTOFF		9
# define R_386_GOTPC		10
typedef struct _Elf32_Rel
{
	Elf32_Addr r_offset;
	Elf32_Word r_info;
} Elf32_Rel;

# define ELF64_R_SYM(info) ((info) >> 32)
# define ELF64_R_TYPE(info) ((info) & 0xffffffff)
# define R_X86_64_GLOB_DAT	6
# define R_X86_64_JUMP_SLOT	7
# define R_X86_64_RELATIVE	8
typedef struct _Elf64_Rel
{
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
} Elf64_Rel;


/* Elf_Rela */
typedef struct _Elf32_Rela
{
	Elf32_Addr r_offset;
	Elf32_Word r_info;
	Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct _Elf64_Rela
{
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
	Elf64_Sxword r_addend;
} Elf64_Rela;

/* Elf_Sym */
/* info */
# define ELF32_ST_TYPE(info) (info & 0xf)
/* type */
# define STT_NOTYPE	0
# define STT_OBJECT	1
# define STT_FUNC	2
# define STT_SECTION	3
# define STT_FILE	4
# define STT_NUM	5
# define STT_LOOS	10
# define STT_HIOS	12
# define STT_LOPROC	13
# define STT_HIPROC	15
/* index */
# define STN_UNDEF	0
typedef struct _Elf32_Sym
{
	Elf32_Word st_name;
	Elf32_Word st_value;
	Elf32_Word st_size;
	Elf_Byte st_info;
	Elf_Byte st_other;
	Elf32_Half st_shndx;
} Elf32_Sym;

typedef struct _Elf64_Sym
{
	Elf64_Half st_name;
	Elf_Byte st_info;
	Elf_Byte st_other;
	Elf64_Quarter st_shndx;
	Elf64_Addr st_value;
	Elf64_Xword st_size;
} Elf64_Sym;

/* Elf_Dyn */
/* tag */
# define DT_NULL		0
# define DT_NEEDED		1
# define DT_PLTRELSZ		2
# define DT_PLTGOT		3
# define DT_HASH		4
# define DT_STRTAB		5
# define DT_SYMTAB		6
# define DT_RELA		7
# define DT_RELASZ		8
# define DT_RELAENT		9
# define DT_STRSZ		10
# define DT_SYMENT		11
# define DT_INIT		12
# define DT_FINI		13
# define DT_SONAME		14
# define DT_RPATH		15
# define DT_SYMBOLIC		16
# define DT_REL			17
# define DT_RELSZ		18
# define DT_RELENT		19
# define DT_PLTREL		20
# define DT_DEBUG		21
# define DT_TEXTREL		22
# define DT_JMPREL		23
# define DT_BIND_NOW		24
# define DT_INIT_ARRAY		25
# define DT_FINI_ARRAY		26
# define DT_FINI_ARRAYSZ	27
# define DT_INIT_ARRAYSZ	28
# define DT_NUM			29
typedef struct _Elf32_Dyn
{
	Elf32_Word d_tag;
	union
	{
		Elf32_Addr d_ptr;
		Elf32_Word d_val;
	} d_un;
} Elf32_Dyn;

typedef struct _Elf64_Dyn {
	Elf64_Xword d_tag;
	union
	{
		Elf64_Addr d_ptr;
		Elf64_Xword d_val;
	} d_un;
} Elf64_Dyn;

#endif /* !LIBC_ELF_H */
