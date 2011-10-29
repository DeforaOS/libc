TARGETS	= libpthread.a libpthread.so.0.0 libpthread.so.0 libpthread.so
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	?= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/pthread -DPIC
CPPFLAGS?=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -pedantic -ffreestanding
AR	?= ar
RANLIB	?= ranlib
CCSHARED= $(CC) -nostdlib -shared
RM	?= rm -f
LN	?= ln -f
MKDIR	?= mkdir -p
INSTALL	?= install


all: $(TARGETS)

libpthread_OBJS = pthread.o
libpthread_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libpthread_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

libpthread.a: $(libpthread_OBJS)
	$(AR) -rc libpthread.a $(libpthread_OBJS)
	$(RANLIB) libpthread.a

libpthread.so.0.0 libpthread.so.0 libpthread.so: $(libpthread_OBJS)
	$(CCSHARED) -o libpthread.so.0.0 -Wl,-soname,libpthread.so.0 $(libpthread_OBJS) $(libpthread_LDFLAGS)
	$(LN) -s -- libpthread.so.0.0 libpthread.so.0
	$(LN) -s -- libpthread.so.0.0 libpthread.so

pthread.o: pthread.c
	$(CC) $(libpthread_CFLAGS) -c pthread.c

clean:
	$(RM) -- $(libpthread_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 -- libpthread.a $(DESTDIR)$(LIBDIR)/libpthread.a
	$(INSTALL) -m 0755 -- libpthread.so.0.0 $(DESTDIR)$(LIBDIR)/libpthread.so.0.0
	$(LN) -s -- libpthread.so.0.0 $(DESTDIR)$(LIBDIR)/libpthread.so.0
	$(LN) -s -- libpthread.so.0.0 $(DESTDIR)$(LIBDIR)/libpthread.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.so

.PHONY: all clean distclean install uninstall
