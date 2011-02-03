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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 -- socket.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/socket.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys
	$(INSTALL) -m 0644 -- un.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/un.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/socket.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/un.h

.PHONY: all clean distclean install uninstall
