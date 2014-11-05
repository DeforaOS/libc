OBJDIR	=
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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys
	$(INSTALL) -m 0644 types.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/types.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/mman.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/types.h

.PHONY: all clean distclean install uninstall
