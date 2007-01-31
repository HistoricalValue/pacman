SHELL = /bin/sh

CXX = g++
CXXFLAGS += -pedantic -Wall -ansi -g -O3
CC = $(CXX)
CFLAGS += $(CXXFLAGS)
CPPFLAGS += -I../include
LD = ld
LDFLAGS += -lSDL -lSDL_image -lSDL_ttf 

sources = $(wildcard *.cpp)
objects = $(sources:.cpp=.o)
dependencies = $(sources:.cpp=.d)
includes = $(wildcard ../include/*.hpp)

clean_dependencies = $(foreach d,$(dependencies),clean_$(d))
clean_objects = $(foreach o,$(objects),clean_$(o))
clean_bins = $(foreach b,$(bins),clean_$(b))

%.d : %.cpp
	@printf ' * Making $@\n'
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM $< | sed -re 's/($*)\.o/\1.o \1.d /g' | tee $@ > /dev/null

$(clean_dependencies) $(clean_objects) $(clean_bins) : clean_% : %
	rm $<

.PHONY : clean default $(clean_dependencies) $(clean_objects) $(clean_bins)

default : $(objects) $(bins)
clean : $(clean_dependencies) $(clean_objects) $(clean_bins)

ifdef b
$(b) :
endif

include $(dependencies)


# .SILENT : $(bins)
