.PHONY : all clean purge touch

all : 
	make -C src default
	make -C test default

clean :
	make -C src clean
	make -C test clean

touch :
	make -C src --touch
	make -C test --touch

purge :
	find . -iregex '.*\.[od]' -execdir rm '{}' \;
