SHELL = /bin/sh

.PHONY : all clean purge touch win32 runs

all : 
	$(MAKE) pac
#	$(MAKE) saku

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

runs :
	./test/sakutest 2>&1 | tee ./resources/sakutest.log

saku :
	$(MAKE) -C src default
	$(MAKE) ADD_CPPFLAGS='-Dmain_wannabe=main' ADD_bins=sakutest -C test default
	$(MAKE) -C client default
	rm test/sakutest.o client/pacman.o

pac :
	$(MAKE) -C src default
	$(MAKE) -C test default
	$(MAKE) ADD_CPPFLAGS='-Dmain_pac\(A,B\)=main\(A,B\)' ADD_bins=pacman -C client default
#	rm test/sakutest.o client/pacman.o
