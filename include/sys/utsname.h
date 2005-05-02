/* sys/utsname.h */



#ifndef ___SYS_UTSNAME_H
# define ___SYS_UTSNAME_H


/* types */
struct utsname
{
	/* FIXME these are of fixed size */
	char * sysname;
	char * nodename;
	char * release;
	char * version;
	char * machine;
};


/* functions */
int uname(struct utsname * name);

#endif /* ___SYS_UTSNAME_H */
