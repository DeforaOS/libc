TARGETS	= libc.a libc.so
CFLAGSF	= -W -Wall -ansi -I../include
CFLAGS	= -g
CC	= cc
AR	= ar rc
RANLIB	= ranlib
LD	= ld -shared
RM	= rm -f


all: $(TARGETS)

libc_OBJS= ctype.o errno.o fcntl.o libgen.o start.o stdlib.o stdio.o string.o sys/stat.o syscalls.o unistd.o
libc_CFLAGS=$(CFLAGSF) $(CFLAGS)
libc.a: $(libc_OBJS)
	$(AR) libc.a $(libc_OBJS)
	$(RANLIB) libc.a

libc.so: $(libc_OBJS)
	$(LD) -o libc.so $(libc_OBJS)

ctype.o: ctype.c
	$(CC) $(libc_CFLAGS) -c ctype.c

errno.o: errno.c
	$(CC) $(libc_CFLAGS) -c errno.c

fcntl.o: fcntl.c
	$(CC) $(libc_CFLAGS) -c fcntl.c

libgen.o: libgen.c
	$(CC) $(libc_CFLAGS) -c libgen.c

start.o: start.S
	$(CC) $(libc_CFLAGS) -c start.S

stdlib.o: stdlib.c
	$(CC) $(libc_CFLAGS) -c stdlib.c

stdio.o: stdio.c
	$(CC) $(libc_CFLAGS) -c stdio.c

string.o: string.c
	$(CC) $(libc_CFLAGS) -c string.c

sys/stat.o: sys/stat.c
	$(CC) $(libc_CFLAGS) -c sys/stat.c -o sys/stat.o

syscalls.o: syscalls.S
	$(CC) $(libc_CFLAGS) -c syscalls.S

unistd.o: unistd.c
	$(CC) $(libc_CFLAGS) -c unistd.c


clean:
	$(RM) $(libc_OBJS)

distclean: clean
	$(RM) $(TARGETS)
