/* sys/stat.h */



#ifndef ___SYS_STAT_H
# define ___SYS_STAT_H


/* types */
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef int gid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef int uid_t;
# endif
struct stat {
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	off_t st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
};


/* functions */
int chmod(const char *, mode_t);
int fchmod(int, mode_t);
int fstat(int, struct stat *);
int lstat(const char *, struct stat *);
int mkdir(const char *, mode_t);
int mkfifo(const char *, mode_t);
int mknod(const char *, mode_t, dev_t);
int stat(const char *, struct stat *);
mode_t umask(mode_t);

#endif /* !___SYS_STAT_H */
