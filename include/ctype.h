/* ctype.h */
/* character types */



#ifndef ___CTYPE_H
# define ___CTYPE_H


/* function prototypes */
#define isalnum(c) (isalpha(c) || isdigit(c))
#define isalpha(c) (islower(c) || isupper(c))
int isascii(int c);
int isblank(int c);
int isdigit(int c);
int islower(int c);
int isprint(int c);
#define ispunct(c) (isprint(c) && (!(isspace(c) || isalnum(c)))
int isspace(int c);
int isupper(int c);
int tolower(int c);
#define _tolower(c) (c + 'a' - 'A')
int toupper(int c);
#define _toupper(c) (c + 'A' - 'a')

#endif /* ___CTYPE_H */
