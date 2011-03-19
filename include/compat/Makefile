SUBDIRS	= net sys
PREFIX	= /usr/local
DESTDIR	= 
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done

install:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- dirent.h $(DESTDIR)$(INCLUDEDIR)/compat/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- errno.h $(DESTDIR)$(INCLUDEDIR)/compat/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- fcntl.h $(DESTDIR)$(INCLUDEDIR)/compat/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- limits.h $(DESTDIR)$(INCLUDEDIR)/compat/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- poll.h $(DESTDIR)$(INCLUDEDIR)/compat/poll.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- signal.h $(DESTDIR)$(INCLUDEDIR)/compat/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- stdio.h $(DESTDIR)$(INCLUDEDIR)/compat/stdio.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- stropts.h $(DESTDIR)$(INCLUDEDIR)/compat/stropts.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- termios.h $(DESTDIR)$(INCLUDEDIR)/compat/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- time.h $(DESTDIR)$(INCLUDEDIR)/compat/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- ucontext.h $(DESTDIR)$(INCLUDEDIR)/compat/ucontext.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- unistd.h $(DESTDIR)$(INCLUDEDIR)/compat/unistd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 -- utmpx.h $(DESTDIR)$(INCLUDEDIR)/compat/utmpx.h

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/dirent.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/errno.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/fcntl.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/limits.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/poll.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/signal.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/stdio.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/stropts.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/termios.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/ucontext.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/unistd.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/compat/utmpx.h

.PHONY: all subdirs clean distclean install uninstall
