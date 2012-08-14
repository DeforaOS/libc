PREFIX	= /usr/local
DESTDIR	=
RM	?= rm -f
LN	?= ln -f
MKDIR	?= mkdir -p
INSTALL	?= install
INCLUDEDIR= $(PREFIX)/include


all:

clean:

distclean: clean

install:
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin
	$(INSTALL) -m 0644 -- errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/errno.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/errno.h

.PHONY: all clean distclean install uninstall
