/* sys/mman.h */



#ifndef ___SYS_MMAN_H
# define ___SYS_MMAN_H


/* types */


/* constants */
# define PROT_READ	0x1
# define PROT_WRITE	0x2
# define PROT_EXEC	0x4
# define PROT_NONE	0x0

# define MAP_SHARED	0x1
# define MAP_PRIVATE	0x2
# define MAP_FIXED	0x10
# define MAP_FAILED	((void*)-1)


/* functions */
void * mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);

#endif /* !___SYS_MMAN_H */
