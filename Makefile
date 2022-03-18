# executable filename
EXE := game

# headers include directories (.h .hpp .hxx ...)
INCDIRS := . include src

# project's external libs
PLIBS := sdl2 SDL2_image SDL2_mixer SDL2_ttf gl

# debug defaults
DEBUG :=

# compilers config
CC := gcc
CXX := g++

# C/C++ common flags
CWARNS := all extra pedantic
CFLAGS := $(addprefix -W, $(CWARNS)) $(addprefix -I, $(INCDIRS))
CFLAGS += $(if $(PLIBS), $(shell pkg-config --cflags $(PLIBS)))

# C++ specific flags
CXXFLAGS :=
CXXFLAGS := -pedantic-errors -std=c++14
CXXFLAGS := $(strip $(CXXFLAGS) $(CFLAGS))

# C specific flags
CEXTRA :=
CEXTRA := -pedantic-errors -std=c99
CFLAGS := $(strip $(CEXTRA) $(CFLAGS))

# Lib flags
LDFLAGS :=
LDLIBS := $(if $(PLIBS), $(shell pkg-config --libs $(PLIBS)))

# math.h lib support
LDLIBS += -lm

# files
SOURCES := $(wildcard **/*.[cC]* *.[cC]*)
C_SOURCES := $(filter %.c, $(SOURCES))
CXX_SOURCES := $(filter %.C %.cc %.cp %.cpp %.cxx %.c++, $(SOURCES))
OBJECTS := $(addsuffix .o, $(basename $(C_SOURCES) $(CXX_SOURCES)))
DEPENDS := $(patsubst %.o, %.d, $(OBJECTS))

# compiler's choice
COMPILER := $(if $(CXX_SOURCES), $(CXX), $(CC))

# rules
.PHONY: all
all: $(OBJECTS)
	$(COMPILER) -o $(EXE) $(OBJECTS) $(LDFLAGS) $(LDLIBS) $(DEBUG)

# rules for C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(DEBUG)

%.d: %.c
	$(CC) $(CFLAGS) -MM $< -MT $(@:.d=.o) -MT $@ -MF $@

# rules for C++ files
%.o: %.[cC]*
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(DEBUG)

%.d: %.[cC]*
	$(CXX) $(CXXFLAGS) -MM $< -MT $(@:.d=.o) -MT $@ -MF $@

# extra tools
.PHONY: clean
clean:
	rm -f $(EXE)
	for P in "*.o" "*.d" "*.gch" ; do find . -name "$$P" -delete ; done

.PHONY: run
.SILENT: run
run:
	$(MAKE) all
	echo "\nRunning $(EXE)...\n"
	./$(EXE)
	echo

.PHONY: dev
.SILENT: dev
dev:
	$(MAKE) clean
	$(MAKE) run
	$(MAKE) clean

.PHONY: debug
debug:
	$(MAKE) clean
	$(MAKE) all DEBUG:="-g -DDEBUG"

.PHONY: memleak
memleak:
	$(MAKE) clean
	$(MAKE) all DEBUG:="-g -rdynamic -DMTRACE"

# dependencies (*.d files)
ifneq ($(firstword $(MAKECMDGOALS)), clean)
-include $(DEPENDS)
endif
