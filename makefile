CC=gcc
CFLAGS= -Wall -ansi -O3
LDFLAGS = 
LDLIBS= -I./headers

SRC= main.c File.c Compression.c
OBJECTS= $(SRC:%.c=bin/%.o)

## Software generation
main: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS) -lm

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDLIBS) -lm

## Cleaner
clean:
	rm -f $(OBJECTS)
	rm -f main
	clear

## Tests generator and launch test
test:
	make clean
	make
	./main
