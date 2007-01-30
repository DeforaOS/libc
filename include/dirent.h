/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_DIRENT_H
# define LIBC_DIRENT_H

# include "compat/dirent.h"


/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef int ino_t;
# endif
typedef struct _DIR DIR;


/* functions */
int closedir(DIR * dir);
DIR * opendir(char const * name);
struct dirent *readdir(DIR * dir);
void rewinddir(DIR *);
void seekdir(DIR *, long);
long telldir(DIR *);

#endif /* !LIBC_DIRENT_H */
