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
	$(INSTALL) -m 0644 select.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/select.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys
	$(INSTALL) -m 0644 stat.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/stat.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys
	$(INSTALL) -m 0644 times.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/times.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys
	$(INSTALL) -m 0644 types.h $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/types.h

uninstall:
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/mman.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/select.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/stat.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/time.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/times.h
	$(RM) -- $(DESTDIR)$(INCLUDEDIR)/kernel/darwin/sys/types.h

.PHONY: all clean distclean install uninstall
