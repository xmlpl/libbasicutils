SUBDIRS = BasicSmartPointerTests BasicDynamicClassTests BasicPluginTests

EXTRA_DIST = testHarness
MOSTLYCLEANFILES = test.log

check: all
	./testHarness 2>&1 | tee test.log

TH_LINKS = runTest resetTest viewTest initTest

maintainer-clean-generic:
	rm -f $(TH_LINKS)

all: th_links

th_links: testHarness
	for i in $(TH_LINKS); do ln -sf $< $$i; done
