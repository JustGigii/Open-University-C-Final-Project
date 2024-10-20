CC=gcc
CFLAGS=-Wall -Wextra
OBJECTS=main.o FileHandler.o

program: $(OBJECTS)
	$(CC) $(CFLAGS) -o program $(OBJECTS)

main.o: source/main.c
	$(CC) $(CFLAGS) -c  source/main.c

FileHandler.o: source/FileHandler.c
	$(CC) $(CFLAGS) -c source/FileHandler.c

clean:
	rm -rf *.o program