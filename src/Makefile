TARGETS	= libc
CFLAGSF	= -W -Wall -ansi
CFLAGS	= -g
CC	= cc
AR	= ar rc
RANLIB	= ranlib
LD	= ld -shared
RM	= rm -f


all: $(TARGETS)

libc: libc.a libc.so

libc.a: libgen.o string.o
	$(AR) libc.a libgen.o string.o
	$(RANLIB) libc.a

libc.so: libgen.o string.o
	$(LD) -o libc.so libgen.o string.o

libgen.o: libgen.c
	$(CC) $(CFLAGSF) $(CFLAGS) -c libgen.c

string.o: string.c
	$(CC) $(CFLAGSF) $(CFLAGS) -c string.c

clean:
	$(RM) libgen.o string.o

distclean: clean
	$(RM) libc.a libc.so
