SHELL = /bin/sh

.PHONY : all clean purge touch win32 runs

all : 
	$(MAKE) -C src default
	$(MAKE) -C test default

win32 :
	$(MAKE) all __WIN32=yes_n00b
clean :
	$(MAKE) -C src clean
	$(MAKE) -C test clean

touch :
	$(MAKE) -C src --touch
	$(MAKE) -C test --touch

purge :
	find . -iregex '.*\.[od]' -exec rm '{}' \;

runs :
	./test/sakutest 2>&1 | tee ./resources/sakutest.log
