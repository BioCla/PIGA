CC = g++
SOURCES = ./src/*.cpp
HEADERS = ./lib/
WARNINGS = -Wall -Wno-format-security
CFLAGS = -lncurses -lm -I $(HEADERS) $(WARNINGS)

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname)
endif


all: build run clean

build:
ifeq ($(detected_OS),Windows)
	$(CC) $(SOURCES) $(CFLAGS) -o main.exe
else
	$(CC) $(SOURCES) $(CFLAGS) -o main
endif

run:
ifeq ($(detected_OS),Windows)
	./main.exe
else
	./main
endif

clean:
ifeq ($(detected_OS),Windows)
	del main.exe
else
	rm main
endif