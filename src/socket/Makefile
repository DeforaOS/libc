TARGETS	= libsocket.a libsocket.so
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGS= -I ../../include -I ../../include/socket -nostdinc
CFLAGSF	= -W
CFLAGS	= -Wall -g -ansi -fno-builtin
AS	= $(CC)
ASFLAGS	= -W -Wall -g -ansi -c
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: $(TARGETS)

libsocket_OBJS = arpa/inet.o netdb.o sys/socket.o syscalls.o
libsocket_CFLAGS = $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libsocket_ASFLAGS = $(CPPFLAGS) $(ASFLAGS)

libsocket.a: $(libsocket_OBJS)
	$(AR) libsocket.a $(libsocket_OBJS)
	$(RANLIB) libsocket.a

libsocket.so: $(libsocket_OBJS)
	$(LD) -o libsocket.so $(libsocket_OBJS)

arpa/inet.o: arpa/inet.c
	$(CC) $(libsocket_CFLAGS) -o arpa/inet.o -c arpa/inet.c

netdb.o: netdb.c
	$(CC) $(libsocket_CFLAGS) -c netdb.c

sys/socket.o: sys/socket.c
	$(CC) $(libsocket_CFLAGS) -o sys/socket.o -c sys/socket.c

syscalls.o: syscalls.S kernel/linux/common.h kernel/linux/i386/syscalls.S kernel/netbsd/common.h kernel/netbsd/sparc/syscalls.S
	$(AS) $(libsocket_ASFLAGS) -o syscalls.o syscalls.S

clean:
	$(RM) $(libsocket_OBJS)

distclean: clean
	$(RM) $(TARGETS)

install: all

uninstall:

.PHONY: all clean distclean install uninstall
