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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- dirent.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- fcntl.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- limits.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- poll.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/poll.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- signal.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- stdio.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/stdio.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- stropts.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/stropts.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- termios.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- time.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- unistd.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/unistd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 -- utmpx.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/utmpx.h

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/dirent.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/errno.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/fcntl.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/limits.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/poll.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/signal.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/stdio.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/stropts.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/termios.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/unistd.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/utmpx.h

.PHONY: all subdirs clean distclean install uninstall
