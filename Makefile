CC=gcc
CFLAGS=-Wall -Wextra -Wno-error -g
OBJECTS=main.o FileHandler.o NodeData.o

program: $(OBJECTS)
	$(CC) $(CFLAGS) -o program $(OBJECTS)

main.o: source/main.c
	$(CC) $(CFLAGS) -c  source/main.c

FileHandler.o: source/FileHandler.c
	$(CC) $(CFLAGS) -c source/FileHandler.c

NodeData.o: source/NodeData.c header/NodeData.h
	$(CC) $(CFLAGS) -c source/NodeData.c

clean:
	rm -rf *.o program