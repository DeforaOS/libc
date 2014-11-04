PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys
	$(INSTALL) -m 0644 mman.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/mman.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/mman.h

.PHONY: all clean distclean install uninstall
