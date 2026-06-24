CC:=gcc
CFLAGS := -Wall -g $(shell pkg-config --libs sdl2)

LIBFLAGS := $(shell pkg-config --cflags --libs sdl2)

INP := CHIP8.c main.c gui.c

TARGET := output
$(TARGET): CHIP8.c
	$(CC) $(INP) -o $(TARGET) $(CFLAGS) $(LIBFLAGS)

clean:
	rm -f ./output
