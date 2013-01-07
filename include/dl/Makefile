PREFIX	= /usr/local
DESTDIR	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- dlfcn.h $(DESTDIR)$(INCLUDEDIR)/dlfcn.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- elf.h $(DESTDIR)$(INCLUDEDIR)/elf.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/dlfcn.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/elf.h

.PHONY: all clean distclean install uninstall
