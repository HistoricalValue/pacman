SHELL = /bin/sh

# Porting options -- for building almost anywhere
ifdef __WIN32
LDFLAGS += -L/c/WINDOWS/ -L. -L/mingw/lib/ -lmingw32 -lSDLmain
CPPFLAGS += -I/mingw/include/
endif
# For CSD.UOC.gr machines
firiki_root = /net/firiki/spare/sipuli/usr/local/
PORT_LDFLAGS += -L$(firiki_root)/sdl/lib/ -Wl,--rpath -Wl,$(firiki_root)/sdl/lib/
PORT_CPPFLAGS += -I$(firiki_root)/sdl/include/
PORT_CXXFLAGS += 

# Normal flags
CXX = g++
CXXFLAGS += -pedantic -Wall -ansi -g -O0 $(ADD_CXXFLAGS) $(PORT_CXXFLAGS)
CPPFLAGS += -I../include $(ADD_CPPFLAGS) $(PORT_CPPFLAGS)
CC = $(CXX)
CFLAGS = $(CXXFLAGS)
LD = ld
LDFLAGS += -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer $(ADD_LDFLAGS) $(PORT_LDFLAGS)

bins += $(ADD_bins)

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
