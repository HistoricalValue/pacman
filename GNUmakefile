SHELL = /bin/sh
MAKEFLAGS += -S

.PHONY : all clean purge touch win32 runs pac tags

all : 
	$(MAKE) -S pac

nosound :
	$(MAKE) ADD_CPPFLAGS=-DPACMAN_NO_SOUND

win32 :
	$(MAKE) all __WIN32=yes_n00b
clean :
	$(MAKE) -S -C src clean
#	$(MAKE) -C test clean
	$(MAKE) -S -C client clean

touch :
	$(MAKE) -S --touch all

purge :
	find . -iregex '.*\.[od]' -exec rm '{}' \; -printf 'rm %p\n'

run :
	./client/pacman 2>&1 | tee ./resources/pacman.log | tail

pac :
	$(MAKE) -C src default
	$(MAKE) ADD_CPPFLAGS='-Dmain_pac\(A,B\)=main\(A,B\) $(ADD_CPPFLAGS)' ADD_bins=pacman -C client default

tags :
	ctags -R
