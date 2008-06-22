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
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 dirent.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/dirent.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 errno.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/errno.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 fcntl.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/fcntl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 limits.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/limits.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 signal.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/signal.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/ioctl.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/ioctl.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/mman.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/mman.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/resource.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/resource.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/select.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/select.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/stat.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/stat.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/time.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/times.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/times.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/types.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/types.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 sys/utsname.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/utsname.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 termios.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/termios.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/time.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 unistd.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/unistd.h
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)/kernel/linux
	$(INSTALL) -m 0644 utmpx.h $(DESTDIR)$(INCLUDEDIR)/kernel/linux/utmpx.h

uninstall:
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/dirent.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/errno.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/fcntl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/limits.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/signal.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/ioctl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/mman.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/resource.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/select.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/stat.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/times.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/types.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/sys/utsname.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/termios.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/unistd.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/kernel/linux/utmpx.h

.PHONY: all clean distclean install uninstall
