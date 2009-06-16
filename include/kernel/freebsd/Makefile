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

install: all
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 dirent.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 fcntl.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 limits.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 signal.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 stdio.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/stdio.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 termios.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 unistd.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/unistd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd
	$(INSTALL) -m 0644 utmpx.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/utmpx.h

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/dirent.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/errno.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/fcntl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/limits.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/signal.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/stdio.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/termios.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/unistd.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/utmpx.h

.PHONY: all subdirs clean distclean install uninstall
