#ifndef WRAPPER_HEADER
#define WRAPPER_HEADER

int Socket();
struct sockaddr_in SetupAddress(short port);
void Bind(int, struct sockaddr_in *sockaddr);
void Listen(int sock_fd, int backlog);

#endif