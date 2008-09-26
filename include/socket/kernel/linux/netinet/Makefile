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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/netinet
	$(INSTALL) -m 0644 in.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/netinet/in.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/netinet/in.h

.PHONY: all clean distclean install uninstall
