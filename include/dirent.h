/* dirent.h */



#ifndef ___DIRENT_H
# define ___DIRENT_H

# include "limits.h"


/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef int ino_t;
# endif
typedef struct _DIR {
	int fd;
} DIR;
struct dirent {
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

#endif /* !___DIRENT_H */
