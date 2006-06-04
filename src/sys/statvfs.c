/* sys/statvfs.c */



#include "../syscalls.h"
#include "sys/statvfs.h"
#include "string.h"


/* statvfs */
#ifdef SYS_statfs /* linux compatibility */
typedef long fsid_t;
struct statfs
{
	long f_type;
	long f_bsize;
	long f_blocks;
	long f_bfree;
	long f_bavail;
	long f_files;
	long f_ffree;
	fsid_t f_fsid;
	long f_namelen;
};
syscall2(int, statfs, char const *, path, struct statfs *, buf);
int statvfs(char const * path, struct statvfs * buf)
{
	struct statfs fs;

	if(statfs(path, &fs) != 0)
		return -1;
	memset(buf, sizeof(*buf), 0);
	buf->f_bsize = fs.f_bsize;
	buf->f_blocks = fs.f_blocks;
	buf->f_bfree = fs.f_bfree;
	buf->f_bavail = fs.f_bavail;
	buf->f_files = fs.f_files;
	buf->f_ffree = fs.f_ffree;
	buf->f_fsid = fs.f_fsid;
	buf->f_namemax = fs.f_namelen;
	return 0;
}
#else
syscall2(int, statvfs, char const *, path, struct vfs *, buf);
#endif
