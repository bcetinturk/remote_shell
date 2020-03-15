CFLAGS = -Wall -O2
CC = gcc

all: server.out client.out

server.out: utils.o wrappers.o utils.c wrappers.c server.c
	$(CC) $(CFLAGS) server.c utils.o wrappers.o -o server.out

client.out: client.c
	$(CC) $(CFLAGS) client.c -o client.out

utils.o:
	$(CC) $(CFLAGS) -c utils.c

wrappers.o:
	$(CC) $(CFLAGS) -c wrappers.c

clean:
	rm *.o