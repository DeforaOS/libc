/* sys/types.h */



#ifndef ___SYS_TYPES_H
# define ___SYS_TYPES_H


typedef int blkcnt_t;
typedef int blksize_t;
typedef int clock_t;
typedef int id_t;
typedef int mode_t;
typedef int nlink_t;
typedef int off_t;
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif
typedef int ssize_t;
typedef int time_t;

typedef id_t gid_t;
typedef id_t pid_t;
typedef id_t uid_t;

#endif /* !___SYS_TYPES_H */
