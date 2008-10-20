SUBDIRS	= sys
PREFIX	= /usr/local
DESTDIR	= 
RM	= rm -f
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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 dirent.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 fcntl.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 limits.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 signal.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 stdio.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/stdio.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 termios.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd
	$(INSTALL) -m 0644 unistd.h $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/unistd.h

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/dirent.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/errno.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/fcntl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/limits.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/signal.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/stdio.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/termios.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/openbsd/unistd.h

.PHONY: all subdirs clean distclean install uninstall
