SUBDIRS = src scripts
DIST_SUBDIRS = $(SUBDIRS) tests

EXTRA_DIST = autogen.sh doc config debian

check:
	$(MAKE) -C tests check

dist-hook:
	rm -rf `find $(distdir) -name CVS -o -name .svn`

mostlyclean-generic:
	if [ -f tests/Makefile ]; then $(MAKE) -C tests clean; fi
	-rm -f core `find . -name '#*' -o -name '.\#*'\
		-o -name '.*~' -o -name '*~' -o -name 'core*'`

maintainer-clean-generic:
	-rm -rf core `find . -name '.deps' -o -name 'autom4te*.cache'`
