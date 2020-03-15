#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include "utils.h"

int main(int argc, char const *argv[])
{
  int sock, valread;
  struct sockaddr_in serv_addr, client_addr;
  char buffer[BUF_SIZE] = {0};
  char input[BUF_SIZE];

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(3000);
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
  {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed \n");
    return -1;
  }

  while (1)
  {
    printf("> ");
    fgets(input, sizeof(input), stdin);

    send(sock, input, strlen(input), 0);
    valread = read(sock, buffer, 1024);
    printf("%s\nsize: %ld\nstrlen: %ld\n", buffer, sizeof(buffer), strlen(buffer));
  }
  return 0;
}