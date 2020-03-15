#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "utils.h"

int Socket()
{
  int n;
  if ((n = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    diep("socket");

  return n;
}

struct sockaddr_in SetupAddress(short port)
{
  struct sockaddr_in sock_addr;

  memset(&sock_addr, 0, sizeof(sock_addr));
  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(port);
  sock_addr.sin_addr.s_addr = INADDR_ANY;

  return sock_addr;
}

void Bind(int sock_fd, struct sockaddr_in *sockaddr)
{
  if (bind(sock_fd, (struct sockaddr *)sockaddr, sizeof(struct sockaddr)) == -1)
    diep("bind");
}

void Listen(int sock_fd, int backlog)
{
  if (listen(sock_fd, backlog) == -1)
    diep("listen");
}