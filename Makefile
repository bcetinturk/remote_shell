CFLAGS = -Wall -O2
CC = gcc

all: server.out client.out

server.out: utils.o wrappers.o utils.c wrappers.c server.c
	$(CC) $(CFLAGS) server.c utils.o wrappers.o -o server.out

client.out: client.c utils.o utils.c
	$(CC) $(CFLAGS) client.c utils.o -o client.out

utils.o: utils.c 
	$(CC) $(CFLAGS) -c utils.c

wrappers.o: wrappers.c
	$(CC) $(CFLAGS) -c wrappers.c

clean:
	rm *.o