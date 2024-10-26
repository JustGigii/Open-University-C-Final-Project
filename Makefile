CC=gcc
CFLAGS=-Wall -Wextra -Wno-error

OBJECTS=main.o FileHandler.o NodeData.o StringUtils.o

program: $(OBJECTS)
	$(CC) $(CFLAGS) -o program $(OBJECTS)

main.o: source/main.c
	$(CC) $(CFLAGS) -c source/main.c

FileHandler.o: source/FileHandler.c
	$(CC) $(CFLAGS) -c source/FileHandler.c

NodeData.o: source/NodeData.c
	$(CC) $(CFLAGS) -c source/NodeData.c

StringUtils.o: source/StringUtils.c
	$(CC) $(CFLAGS) -c source/StringUtils.c

clean:
	rm -rf *.o program