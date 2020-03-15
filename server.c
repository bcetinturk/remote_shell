#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "wrappers.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
  pid_t pid;
  char **arg_list;

  socklen_t sin_size;
  int server_sock, new_sock;
  struct sockaddr_in my_addr, client_addr;
  char input[BUF_SIZE];

  server_sock = Socket();
  my_addr = SetupAddress(3000);

  Bind(server_sock, &my_addr);

  Listen(server_sock, 10);


  while (1)
  {
    sin_size = sizeof(struct sockaddr_in);
    if ((new_sock = accept(server_sock, (struct sockaddr *)&client_addr, &sin_size)) == -1)
    {
      perror("accept");
      continue;
    }

    read(new_sock, input, BUF_SIZE);
    printf("message: %s\n", input);

    arg_list = parse_command(input);

    pid = fork();
    if (pid == -1)
    {
      diep("fork");
    }
    else if (pid == 0)
    { // child
      dup2(new_sock, STDOUT_FILENO);
      execvp(arg_list[0], arg_list);
    }
    else
    {
      waitpid(pid, NULL, 0);
    }

    // char *response = "Command executed\n";

    // if (send(new_sock, response, strlen(response), 0) == -1)
    // {
    //   perror("send");
    // }

    close(new_sock);
  }
  return 0;
}
