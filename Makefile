CXX := g++

ifeq ($(OS),Windows_NT)
	detected_OS := Windows
	RM := rmdir /Q /S
	FixPath = $(subst /,\,$1)
	ext := .exe
else
	detected_OS := $(shell uname)
	RM := rm -f
	FLAGS := -p
	FixPath = $1
endif	

MD := mkdir $(FLAGS)

CXXFLAGS += -MMD -MP

CXXFLAGS += -std=c++14 -pedantic-errors
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -g3 -Ofast

CPPFLAGS += -Iinclude

LDFLAGS += -lncurses

DIRS := $(patsubst src/%, %, $(wildcard src/*))
PROG_SOURCES :=  $(wildcard src/*/*.cpp)
OBJECTS := $(patsubst src/%.cpp, build/%.o, $(PROG_SOURCES))
DEPENDENCIES := $(patsubst src/%.cpp, build/%.d, $(PROG_SOURCES))


all: prepare dirs main run clean
	
-include $(call FixPath,$(DEPENDENCIES))

build/%.o: src/%.cpp
	@echo Compiling $<
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(call FixPath,$<) -o $(call FixPath,$@)

main: $(OBJECTS)
	@echo Linking $@
	$(CXX) $(CXXFLAGS) -o $@ $(call FixPath,$^) $(LDFLAGS)

prepare:
	@echo Preparing build directories
	-@$(RM) build

run: main$(ext)
	@echo Running main
	./main

clean: 
	-del $(call FixPath,./main$(ext))

dirs:
	@$(MD) $(call FixPath,$(patsubst %, build/%, $(DIRS)))
	@echo Created directories: $(DIRS)

.PHONY: show dirs