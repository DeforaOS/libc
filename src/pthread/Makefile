TARGETS	= libpthread.a libpthread.so
PREFIX	= /usr/local
DESTDIR	= 
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -I ../../include -I ../../include/pthread
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -g -ansi -ffreestanding -fPIC
AR	= ar -rc
RANLIB	= ranlib
LD	= $(CC) -shared
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install


all: $(TARGETS)

libpthread_OBJS = pthread.o
libpthread_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libpthread_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

libpthread.a: $(libpthread_OBJS)
	$(AR) libpthread.a $(libpthread_OBJS)
	$(RANLIB) libpthread.a

libpthread.so: $(libpthread_OBJS)
	$(LD) -o libpthread.so $(libpthread_OBJS)

pthread.o: pthread.c
	$(CC) $(libpthread_CFLAGS) -c pthread.c

clean:
	$(RM) $(libpthread_OBJS)

distclean: clean
	$(RM) $(TARGETS)

install: all
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 libpthread.a $(DESTDIR)$(LIBDIR)/libpthread.a
	$(INSTALL) -m 0755 libpthread.so $(DESTDIR)$(LIBDIR)/libpthread.so

uninstall:
	$(RM) $(DESTDIR)$(LIBDIR)/libpthread.a
	$(RM) $(DESTDIR)$(LIBDIR)/libpthread.so

.PHONY: all clean distclean install uninstall
