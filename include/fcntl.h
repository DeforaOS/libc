/* fcntl.h */
/* file control options */



#ifndef ___FCNTL_H
# define ___FCNTL_H


/* constants */
/* for fcntl() */
# define F_DUPFD	0
# define F_GETFD	1
# define F_SETFD	2
# define F_GETFL	3
# define F_SETFL	4
# define F_GETLK	5
# define F_SETLK	6
# define F_SETLKW	7
# define F_GETOWN	9
# define F_SETOWN	8

/* file access modes for open() and fcntl() */
# define O_RDONLY	00
# define O_WRONLY	01
# define O_RDWR		02
# define O_CREAT	0100
# define O_EXCL		0200
# define O_NOCTTY	0400
# define O_TRUNC	01000
# define O_APPEND	02000
# define O_NONBLOCK	04000


/* types */
# ifndef id_t
#  define id_t id_t
typedef int id_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef int off_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef id_t pid_t;
# endif


/* functions */
int creat(const char *, mode_t);
int fcntl(int, int, ...);
int open(char const * filename, int flags, ...);

#endif /* !___FCNTL_H */
