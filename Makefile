CC    ?= gcc
AR    ?= ar
PREFIX = /usr/local
FLAGS  = -O3 -std=c99 -Wall -g -pedantic
SRC    = src/point.c src/bounds.c src/node.c src/quadtree.c
OBJ    = $(SRC:.c=.o)

all: test benchmark

build/libquadtree.a: $(OBJ)
	@mkdir -p build
	@$(AR) rcs $@ $^

install: build/libquadtree.a
	@cp build/libquadtree.a /usr/local/lib/libquadtree.a
	@cp src/quadtree.h /usr/local/include/quadtree.h

clean:
	@rm -fr bin build *.o src/*.o

%.o: %.c
	@$(CC) $< $(FLAGS) -c -o $@

test: test/*.c $(OBJ)
	@mkdir -p bin
	@$(CC) $^ -o bin/$@
	@bin/$@

benchmark: benchmark/*.c $(OBJ)
	@mkdir -p bin
	@$(CC) $^ -o bin/$@
	@bin/$@

.PHONY: test clean benchmark
