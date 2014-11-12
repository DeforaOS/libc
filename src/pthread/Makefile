TARGETS	= $(OBJDIR)libpthread.a $(OBJDIR)libpthread.so.0.0 $(OBJDIR)libpthread.so.0 $(OBJDIR)libpthread.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -nostdinc -isystem ../../include -isystem ../../include/pthread -isystem ../../include/rt -DPIC
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic -ffreestanding
LDFLAGSF= -nostdlib
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

libpthread_OBJS = $(OBJDIR)pthread.o
libpthread_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libpthread_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)libpthread.a: $(libpthread_OBJS)
	$(AR) -rc $(OBJDIR)libpthread.a $(libpthread_OBJS)
	$(RANLIB) $(OBJDIR)libpthread.a

$(OBJDIR)libpthread.so.0.0 $(OBJDIR)libpthread.so.0 $(OBJDIR)libpthread.so: $(libpthread_OBJS)
	$(CCSHARED) -o $(OBJDIR)libpthread.so.0.0 -Wl,-soname,libpthread.so.0 $(libpthread_OBJS) $(libpthread_LDFLAGS)
	$(LN) -s -- libpthread.so.0.0 $(OBJDIR)libpthread.so.0
	$(LN) -s -- libpthread.so.0.0 $(OBJDIR)libpthread.so

$(OBJDIR)pthread.o: pthread.c
	$(CC) $(libpthread_CFLAGS) -o $(OBJDIR)pthread.o -c pthread.c

clean:
	$(RM) -- $(libpthread_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)
	$(INSTALL) -m 0644 $(OBJDIR)libpthread.a $(DESTDIR)$(LIBDIR)/libpthread.a
	$(INSTALL) -m 0755 $(OBJDIR)libpthread.so.0.0 $(DESTDIR)$(LIBDIR)/libpthread.so.0.0
	$(LN) -s -- libpthread.so.0.0 $(DESTDIR)$(LIBDIR)/libpthread.so.0
	$(LN) -s -- libpthread.so.0.0 $(DESTDIR)$(LIBDIR)/libpthread.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.a
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.so.0.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.so.0
	$(RM) -- $(DESTDIR)$(LIBDIR)/libpthread.so

.PHONY: all clean distclean install uninstall
