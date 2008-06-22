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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 dirent.h $(DESTDIR)$(INCLUDEDIR)/compat/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 errno.h $(DESTDIR)$(INCLUDEDIR)/compat/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 fcntl.h $(DESTDIR)$(INCLUDEDIR)/compat/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 limits.h $(DESTDIR)$(INCLUDEDIR)/compat/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 signal.h $(DESTDIR)$(INCLUDEDIR)/compat/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/ioctl.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/ioctl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/mman.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/mman.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/mount.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/mount.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/reboot.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/reboot.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/resource.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/resource.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/select.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/select.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/stat.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/stat.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/time.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/times.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/times.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/types.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/types.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 sys/utsname.h $(DESTDIR)$(INCLUDEDIR)/compat/sys/utsname.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 termios.h $(DESTDIR)$(INCLUDEDIR)/compat/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/compat/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 unistd.h $(DESTDIR)$(INCLUDEDIR)/compat/unistd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/compat
	$(INSTALL) -m 0644 utmpx.h $(DESTDIR)$(INCLUDEDIR)/compat/utmpx.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/dirent.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/errno.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/fcntl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/limits.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/signal.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/ioctl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/mman.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/mount.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/reboot.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/resource.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/select.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/stat.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/times.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/types.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/sys/utsname.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/termios.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/unistd.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/compat/utmpx.h

.PHONY: all clean distclean install uninstall
