TARGETS	= libc
CFLAGSF	= -W -Wall -ansi -I../include
CFLAGS	= -g
CC	= cc
AR	= ar rc
RANLIB	= ranlib
LD	= ld -shared
RM	= rm -f


all: $(TARGETS)

libc: libc.a libc.so

libc.a: ctype.o libgen.o stdlib.o string.o
	$(AR) libc.a ctype.o libgen.o stdlib.o string.o
	$(RANLIB) libc.a

libc.so: ctype.o libgen.o stdlib.o string.o
	$(LD) -o libc.so ctype.o libgen.o stdlib.o string.o

ctype.o: ctype.c
	$(CC) $(CFLAGSF) $(CFLAGS) -c ctype.c

libgen.o: libgen.c
	$(CC) $(CFLAGSF) $(CFLAGS) -c libgen.c

stdlib.o: stdlib.c
	$(CC) $(CFLAGSF) $(CFLAGS) -c stdlib.c

string.o: string.c
	$(CC) $(CFLAGSF) $(CFLAGS) -c string.c

clean:
	$(RM) ctype.o libgen.o stdlib.o string.o

distclean: clean
	$(RM) libc.a libc.so
