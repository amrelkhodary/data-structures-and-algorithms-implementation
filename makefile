#compile all src files to /bin, with .o extension removed from the resulting object file names
PROGS := $(addprefix ./bin/, $(basename $(wildcard *.c)))
PROGS_TARGET:= ./bin/%

all: ${PROGS}

${PROGS_TARGET}: %.c
	cc -g -Wall -Werror -fsanitize=address $< -lm -o $@

clean:
	rm ./bin/*

install:
	cp ./bin/* ~/bin
.PHONY: all clean install
