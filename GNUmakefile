.PHONY : all clean purge touch win32

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
