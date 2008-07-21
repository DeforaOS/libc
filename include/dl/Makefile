PREFIX	= /usr/local
DESTDIR	= 
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install: all
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 dlfcn.h $(DESTDIR)$(INCLUDEDIR)/dlfcn.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/dlfcn.h

.PHONY: all clean distclean install uninstall
