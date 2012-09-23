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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 -- sched.h $(DESTDIR)$(INCLUDEDIR)/sched.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/sched.h

.PHONY: all clean distclean install uninstall
