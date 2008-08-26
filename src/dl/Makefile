TARGETS	= libdl.a libdl.so
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -I ../../include -I ../../include/dl
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -g -ansi -ffreestanding
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: $(TARGETS)

libdl_OBJS = dlfcn.o
libdl_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)

libdl.a: $(libdl_OBJS)
	$(AR) libdl.a $(libdl_OBJS)
	$(RANLIB) libdl.a

libdl.so: $(libdl_OBJS)
	$(LD) -o libdl.so $(libdl_OBJS)

dlfcn.o: dlfcn.c ../../include/dl/dlfcn.h
	$(CC) $(libdl_CFLAGS) -c dlfcn.c

clean:
	$(RM) $(libdl_OBJS)

distclean: clean
	$(RM) $(TARGETS)

install: all

uninstall:

.PHONY: all clean distclean install uninstall
