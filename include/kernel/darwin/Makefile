SUBDIRS	= sys
PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE)) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) distclean) || exit; done

install:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 unistd.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/unistd.h

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/errno.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/unistd.h

.PHONY: all subdirs clean distclean install uninstall
