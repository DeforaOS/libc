/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_DIRENT_H
# define LIBC_DIRENT_H

# include "compat/dirent.h"


/* types */
typedef struct _DIR DIR;


/* functions */
int closedir(DIR * dir);
DIR * opendir(char const * name);
struct dirent *readdir(DIR * dir);
void rewinddir(DIR *);
void seekdir(DIR *, long);
long telldir(DIR *);

#endif /* !LIBC_DIRENT_H */
