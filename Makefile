CFLAGS = -Wall -O2
CC = gcc

server.out:
	$(CC) $(CFLAGS) server.c -o server.out