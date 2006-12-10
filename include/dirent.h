/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_DIRENT_H
# define LIBC_DIRENT_H

# include "limits.h"


/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef int ino_t;
# endif
typedef struct _DIR DIR;

struct dirent
{
	ino_t d_ino;
	char d_name[NAME_MAX];
};


/* functions */
int closedir(DIR * dir);
DIR * opendir(char const * name);
struct dirent *readdir(DIR * dir);
void rewinddir(DIR *);
void seekdir(DIR *, long);
long telldir(DIR *);

#endif /* !LIBC_DIRENT_H */
