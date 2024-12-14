CC=gcc
CFLAGS= -ansi -Wall -pedantic -g3 -w

OBJECTS=main.o FileHandler.o NodeData.o StringUtils.o MacroSystem.o LineDetction.o

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

MacroSystem.o: source/MacroSystem.c
	$(CC) $(CFLAGS) -c source/MacroSystem.c

LineDetction.o: source/LineDetction.c
	$(CC) $(CFLAGS) -c source/LineDetction.c

clean:
	rm -rf *.o program