/* dirent.h */



#ifndef ___DIRENT_H
# define ___DIRENT_H

# include "limits.h"


/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef int ino_t;
# endif
struct dirent {
	ino_t d_ino;
	char d_name[NAME_MAX];
};


/* functions */
int closedir(DIR *);
DIR * opendir(char const *);
struct dirent *readdir(DIR *);
void rewinddir(DIR *);
void seekdir(DIR *, long);
long telldir(DIR *);

#endif /* !___DIRENT_H */
