/* dirent.h */



#ifndef ___DIRENT_H
# define ___DIRENT_H

# include "limits.h"


/* types */
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
