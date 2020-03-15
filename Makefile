CFLAGS = -Wall -O2
CC = gcc

all: server.out client.out

server.out: utils.o utils.c server.c
	$(CC) $(CFLAGS) server.c utils.o -o server.out

client.out: client.c
	$(CC) $(CFLAGS) client.c -o client.out

utils.o:
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm *.o