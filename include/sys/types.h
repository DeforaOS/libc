/* sys/types.h */



#ifndef ___SYS_TYPES_H
# define ___SYS_TYPES_H


/* types */
# ifndef blkcnt_t
#  define blkcnt_t blkcnt_t
typedef int blkcnt_t;
# endif
# ifndef blksize_t
#  define blksize_t blksize_t
typedef int blksize_t;
# endif
typedef int clock_t;
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
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif
# ifndef ssize_t
#  define ssize_t ssize_t
typedef int ssize_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
# endif

# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
# endif

#endif /* !___SYS_TYPES_H */
