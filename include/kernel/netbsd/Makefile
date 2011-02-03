SUBDIRS	= sys
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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- dirent.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- fcntl.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- limits.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- poll.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/poll.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- signal.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- stdio.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/stdio.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- stropts.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/stropts.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- termios.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- time.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- ucontext.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/ucontext.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- unistd.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/unistd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd
	$(INSTALL) -m 0644 -- utmpx.h $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/utmpx.h

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/dirent.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/errno.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/fcntl.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/limits.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/poll.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/signal.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/stdio.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/stropts.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/termios.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/ucontext.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/unistd.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/netbsd/utmpx.h

.PHONY: all subdirs clean distclean install uninstall
