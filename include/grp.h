/* grp.h */



#ifndef ___GRP_H
# define ___GRP_H


/* types */
# ifndef id_t
#  define id_t id_t
typedef int id_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t
# endif
struct group
{
	char * gr_name;
	gid_t gr_gid;
	char ** gr_mem;
};


/* functions */
struct group * getgrgid(gid_t);
struct group * getgrnam(char const *);

#endif /* !___GRP_H */
