TARGETS	= libc.a libc.so
CFLAGSF	= -W -Wall -ansi -I../include
CFLAGS	= -g
CC	= cc
AR	= ar rc
RANLIB	= ranlib
LD	= ld -shared
RM	= rm -f


all: $(TARGETS)

libc_OBJS= ctype.o libgen.o stdlib.o stdio.o string.o
libc_CFLAGS=$(CFLAGSF) $(CFLAGS)
libc.a: $(libc_OBJS)
	$(AR) libc.a $(libc_OBJS)
	$(RANLIB) libc.a

libc.so: $(libc_OBJS)
	$(LD) -o libc.so $(libc_OBJS)

ctype.o: ctype.c
	$(CC) $(libc_CFLAGS) -c ctype.c

libgen.o: libgen.c
	$(CC) $(libc_CFLAGS) -c libgen.c

stdlib.o: stdlib.c
	$(CC) $(libc_CFLAGS) -c stdlib.c

stdio.o: stdio.c
	$(CC) $(libc_CFLAGS) -c stdio.c

string.o: string.c
	$(CC) $(libc_CFLAGS) -c string.c


clean:
	$(RM) $(libc_OBJS)

distclean: clean
	$(RM) $(TARGETS)
