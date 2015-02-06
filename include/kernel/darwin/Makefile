SUBDIRS	= sys
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd "$$i" && \
		if [ -n "$(OBJDIR)" ]; then \
		([ -d "$(OBJDIR)$$i" ] || $(MKDIR) -- "$(OBJDIR)$$i") && \
		$(MAKE) OBJDIR="$(OBJDIR)$$i/"; \
		else $(MAKE); fi) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) distclean) || exit; done

install:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 fcntl.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 signal.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 stdio.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/stdio.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 unistd.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/unistd.h

uninstall:
	@for i in $(SUBDIRS); do (cd "$$i" && $(MAKE) uninstall) || exit; done
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/errno.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/fcntl.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/signal.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/stdio.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/unistd.h

.PHONY: all subdirs clean distclean install uninstall
