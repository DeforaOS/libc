SUBDIRS	= src
MAKE	= make


all clean distclean:
	@for i in $(SUBDIRS); do $(MAKE) -C $$i $@ || exit $$?; done
