SUBDIRS	= compat kernel/linux kernel/netbsd kernel/openbsd kernel/solaris socket
PREFIX	= /usr/local
DESTDIR	= 
RM	= rm -f
MKDIR	= mkdir -p
INSTALL	= install
INCLUDEDIR= $(PREFIX)/include


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done

clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done

distclean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done

install: all
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) install) || exit; done
	$(MKDIR) $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 assert.h $(DESTDIR)$(INCLUDEDIR)/assert.h
	$(INSTALL) -m 0644 ctype.h $(DESTDIR)$(INCLUDEDIR)/ctype.h
	$(INSTALL) -m 0644 dirent.h $(DESTDIR)$(INCLUDEDIR)/dirent.h
	$(INSTALL) -m 0644 errno.h $(DESTDIR)$(INCLUDEDIR)/errno.h
	$(INSTALL) -m 0644 fcntl.h $(DESTDIR)$(INCLUDEDIR)/fcntl.h
	$(INSTALL) -m 0644 fnmatch.h $(DESTDIR)$(INCLUDEDIR)/fnmatch.h
	$(INSTALL) -m 0644 grp.h $(DESTDIR)$(INCLUDEDIR)/grp.h
	$(INSTALL) -m 0644 inttypes.h $(DESTDIR)$(INCLUDEDIR)/inttypes.h
	$(INSTALL) -m 0644 libgen.h $(DESTDIR)$(INCLUDEDIR)/libgen.h
	$(INSTALL) -m 0644 limits.h $(DESTDIR)$(INCLUDEDIR)/limits.h
	$(INSTALL) -m 0644 pwd.h $(DESTDIR)$(INCLUDEDIR)/pwd.h
	$(INSTALL) -m 0644 signal.h $(DESTDIR)$(INCLUDEDIR)/signal.h
	$(INSTALL) -m 0644 stdarg.h $(DESTDIR)$(INCLUDEDIR)/stdarg.h
	$(INSTALL) -m 0644 stddef.h $(DESTDIR)$(INCLUDEDIR)/stddef.h
	$(INSTALL) -m 0644 stdint.h $(DESTDIR)$(INCLUDEDIR)/stdint.h
	$(INSTALL) -m 0644 stdio.h $(DESTDIR)$(INCLUDEDIR)/stdio.h
	$(INSTALL) -m 0644 stdlib.h $(DESTDIR)$(INCLUDEDIR)/stdlib.h
	$(INSTALL) -m 0644 string.h $(DESTDIR)$(INCLUDEDIR)/string.h
	$(INSTALL) -m 0644 strings.h $(DESTDIR)$(INCLUDEDIR)/strings.h
	$(INSTALL) -m 0644 stropts.h $(DESTDIR)$(INCLUDEDIR)/stropts.h
	$(INSTALL) -m 0644 sys/ioctl.h $(DESTDIR)$(INCLUDEDIR)/sys/ioctl.h
	$(INSTALL) -m 0644 sys/mman.h $(DESTDIR)$(INCLUDEDIR)/sys/mman.h
	$(INSTALL) -m 0644 sys/mount.h $(DESTDIR)$(INCLUDEDIR)/sys/mount.h
	$(INSTALL) -m 0644 sys/reboot.h $(DESTDIR)$(INCLUDEDIR)/sys/reboot.h
	$(INSTALL) -m 0644 sys/resource.h $(DESTDIR)$(INCLUDEDIR)/sys/resource.h
	$(INSTALL) -m 0644 sys/select.h $(DESTDIR)$(INCLUDEDIR)/sys/select.h
	$(INSTALL) -m 0644 sys/stat.h $(DESTDIR)$(INCLUDEDIR)/sys/stat.h
	$(INSTALL) -m 0644 sys/statvfs.h $(DESTDIR)$(INCLUDEDIR)/sys/statvfs.h
	$(INSTALL) -m 0644 sys/time.h $(DESTDIR)$(INCLUDEDIR)/sys/time.h
	$(INSTALL) -m 0644 sys/times.h $(DESTDIR)$(INCLUDEDIR)/sys/times.h
	$(INSTALL) -m 0644 sys/types.h $(DESTDIR)$(INCLUDEDIR)/sys/types.h
	$(INSTALL) -m 0644 sys/utsname.h $(DESTDIR)$(INCLUDEDIR)/sys/utsname.h
	$(INSTALL) -m 0644 sys/wait.h $(DESTDIR)$(INCLUDEDIR)/sys/wait.h
	$(INSTALL) -m 0644 termios.h $(DESTDIR)$(INCLUDEDIR)/termios.h
	$(INSTALL) -m 0644 time.h $(DESTDIR)$(INCLUDEDIR)/time.h
	$(INSTALL) -m 0644 unistd.h $(DESTDIR)$(INCLUDEDIR)/unistd.h
	$(INSTALL) -m 0644 utime.h $(DESTDIR)$(INCLUDEDIR)/utime.h
	$(INSTALL) -m 0644 utmpx.h $(DESTDIR)$(INCLUDEDIR)/utmpx.h

uninstall:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) uninstall) || exit; done
	$(RM) $(DESTDIR)$(INCLUDEDIR)/assert.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/ctype.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/dirent.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/errno.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/fcntl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/fnmatch.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/grp.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/inttypes.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/libgen.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/limits.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/pwd.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/signal.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/stdarg.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/stddef.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/stdint.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/stdio.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/stdlib.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/string.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/strings.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/stropts.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/ioctl.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/mman.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/mount.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/reboot.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/resource.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/select.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/stat.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/statvfs.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/times.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/types.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/utsname.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/sys/wait.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/termios.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/time.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/unistd.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/utime.h
	$(RM) $(DESTDIR)$(INCLUDEDIR)/utmpx.h

.PHONY: all subdirs clean distclean install uninstall
