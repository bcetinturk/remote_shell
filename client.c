#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

int main(int argc, char const *argv[])
{
  int sock, valread;
  struct sockaddr_in serv_addr;
  char buffer[BUF_SIZE] = {0};
  char input[BUF_SIZE];

  fgets(input, BUF_SIZE, stdin);

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(3000);

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed \n");
    return -1;
  }

  send(sock, input, strlen(input), 0);
  valread = read(sock, buffer, 1024);
  printf("%s\n", buffer);
  return 0;
}