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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys
	$(INSTALL) -m 0644 -- socket.h $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/socket.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/freebsd/sys/socket.h

.PHONY: all clean distclean install uninstall
