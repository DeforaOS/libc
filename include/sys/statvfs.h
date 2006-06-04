/* sys/statvfs.h */



#ifndef ___SYS_STATVFS_H
# define ___SYS_STATVFS_H


/* types */
# ifndef fsblkcnt_t
#  define fsblkcnt_t fsblkcnt_t
typedef unsigned long fsblkcnt_t;
# endif
# ifndef fsfilcnt_t
#  define fsfilcnt_t fsfilcnt_t
typedef unsigned long fsfilcnt_t;
# endif

struct statvfs
{
	unsigned long f_bsize;
	unsigned long f_frsize;
	fsblkcnt_t f_blocks;
	fsblkcnt_t f_bfree;
	fsblkcnt_t f_bavail;
	fsfilcnt_t f_files;
	fsfilcnt_t f_ffree;
	fsfilcnt_t f_favail;
	unsigned long f_fsid;
	unsigned long f_flag;
	unsigned long f_namemax;
};

/* functions */
int statvfs(char const * path, struct statvfs * buf);
int fstatvfs(int fd, struct statvfs * buf);

#endif /* !___SYS_STATVFS_H */
