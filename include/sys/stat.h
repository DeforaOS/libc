/* sys/stat.h */



#ifndef ___SYS_STAT_H
# define ___SYS_STAT_H


/* types */
# ifndef blkcnt_t
#  define blkcnt_t blkcnt_t
typedef int blkcnt_t;
# endif
# ifndef blksize_t
#  define blksize_t blksize_t
typedef int blksize_t;
# endif
# ifndef dev_t
#  define dev_t dev_t
typedef int dev_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef int id_t;
# endif
# ifndef ino_t
#  define ino_t ino_t
typedef int ino_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef int nlink_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef int off_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
# endif

# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
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


/* constants */
# define S_IFMT 0170000
# define S_IFBLK 0060000
# define S_IFCHR 0020000
# define S_IFIFO 0010000
# define S_IFREG 0100000
# define S_IFDIR 0040000
# define S_IFLNK 0120000
# define S_IFSOCK 0140000


/* macros */
# define S_ISBLK(m) (((m) & S_IFBLK) ? 1 : 0)
# define S_ISCHR(m) (((m) & S_IFCHR) ? 1 : 0)
# define S_ISDIR(m) (((m) & S_IFDIR) ? 1 : 0)
# define S_ISFIFO(m) (((m) & S_IFIFO) ? 1 : 0)
# define S_ISREG(m) (((m) & S_IFREG) ? 1 : 0)
# define S_ISLNK(m) (((m) & S_IFLNK) ? 1 : 0)
# define S_ISSOCK(m) (((m) & S_IFSOCK) ? 1 : 0)


/* functions */
int chmod(char const *, mode_t);
int fchmod(int, mode_t);
int fstat(int, struct stat *);
int lstat(char const *, struct stat *);
int mkdir(char const *, mode_t);
int mkfifo(char const *, mode_t);
int mknod(char const *, mode_t, dev_t);
int stat(char const *, struct stat *);
mode_t umask(mode_t);

#endif /* !___SYS_STAT_H */
