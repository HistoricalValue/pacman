SHELL = /bin/sh

.PHONY : all clean purge touch win32 runs

all : 
	$(MAKE) pac

win32 :
	$(MAKE) all __WIN32=yes_n00b
clean :
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	$(MAKE) -C client clean

touch :
	$(MAKE) --touch all

purge :
	find . -iregex '.*\.[od]' -exec rm '{}' \;

run :
	./client/pacman 2>&1 | tee ./resources/pacman.log

pac :
	$(MAKE) -C src default
	$(MAKE) ADD_CPPFLAGS='-Dmain_pac\(A,B\)=main\(A,B\)' ADD_bins=pacman -C client default
