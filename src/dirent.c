/* dirent.c */



#include "sys/stat.h"
#include "fcntl.h"
#include "errno.h"
#include "stddef.h"
#include "dirent.h"


/* opendir */
DIR * opendir(char const * name)
{
	int fd;
	struct stat st;

	if((fd = open(name, O_RDONLY)) != 0)
		return NULL;
	if(fstat(fd, &st) != 0)
		return NULL;
	if(!S_ISDIR(st.st_mode))
	{
		errno = ENOTDIR;
		return NULL;
	}
	return NULL; /* FIXME */
}
