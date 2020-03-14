CFLAGS = -Wall -O2
CC = gcc

server.out: utils.o utils.c server.c
	$(CC) $(CFLAGS) server.c utils.o -o server.out

utils.o:
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm *.o