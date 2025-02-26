
CC=gcc
CFLAGS= -ansi -Wall -pedantic -g

OBJECTS=main.o FileHandler.o NodeData.o StringUtils.o MacroSystem.o LineDetction.o prosseLabel.o print_error.o cheackSentece.o ValditionLine.o PrintForFile.o

program: $(OBJECTS)
	$(CC) $(CFLAGS) -o program $(OBJECTS)

main.o: source/main.c
	$(CC) $(CFLAGS) -c source/main.c

StringUtils.o: source/StringUtils.c
	$(CC) $(CFLAGS) -c source/StringUtils.c
	
FileHandler.o: source/FileHandler.c
	$(CC) $(CFLAGS) -c source/FileHandler.c

NodeData.o: source/NodeData.c
	$(CC) $(CFLAGS) -c source/NodeData.c	


MacroSystem.o: source/MacroSystem.c
	$(CC) $(CFLAGS) -c source/MacroSystem.c


prosseLabel.o: source/prosseLabel.c
	$(CC) $(CFLAGS) -c source/prosseLabel.c

LineDetction.o: source/LineDetction.c
	$(CC) $(CFLAGS) -c source/LineDetction.c

print_error.o: source/print_error.c
	$(CC) $(CFLAGS) -c source/print_error.c

cheackSentece.o: source/cheackSentece.c
	$(CC) $(CFLAGS) -c source/cheackSentece.c

ValditionLine.o: source/ValditionLine.c
	$(CC) $(CFLAGS) -c source/ValditionLine.c

PrintForFile.o: source/PrintForFile.c
	$(CC) $(CFLAGS) -c source/PrintForFile.c

clean:
	rm -rf *.o program