CC = gcc
CFLAGS = -Wall -Iinclude/chelp -std=c23 -fdiagnostics-color=always -O3

SRC = $(wildcard src/chelp/*.c)
OBJ = $(patsubst src/chelp/%.c, lib/%.o, $(SRC))
OUT = lib/libchelp.a

all: always $(OBJ) clean

always:
	mkdir -p lib

lib/%.o: src/chelp/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
	ar -rv $(OUT) $@

clean:
	rm lib/*.o
