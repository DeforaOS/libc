SUBDIRS	= src


all: subdirs

subdirs:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE)) || exit; done


clean:
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) clean) || exit; done

distclean: clean
	@for i in $(SUBDIRS); do (cd $$i && $(MAKE) distclean) || exit; done
