CC=gcc
CFLAGS= -Wall -ansi -O3
LDFLAGS = 
LDLIBS= -I./headers

SRC= main.c File.c Compression.c Utils.c
OBJECTS= $(SRC:%.c=bin/%.o)

OUTPUT=Compress

## Software generation
$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS) -lm

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDLIBS) -lm

## Cleaner
clean:
	rm -f $(OBJECTS)
	rm -f $(OUTPUT)
	clear

## Tests generator and launch test
test:
	make clean
	make
	./$(OUTPUT)