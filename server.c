#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "utils.h"

void diep(char *s)
{
  perror(s);
  exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
  pid_t pid;
  char **arg_list;

  socklen_t sin_size;
  int server_sock, new_sock;
  struct sockaddr_in my_addr, client_addr;
  char input[BUF_SIZE];

  if ((server_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
  {
    diep("socket");
  }

  memset(&my_addr, 0, sizeof(my_addr));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(3000);
  my_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
  {
    diep("bind");
  }

  if (listen(server_sock, 5) == -1)
  {
    diep("listen");
  }

  while (1)
  {
    sin_size = sizeof(struct sockaddr_in);
    if ((new_sock = accept(server_sock, (struct sockaddr *)&client_addr, &sin_size)) == -1)
    {
      perror("accept");
      continue;
    }

    read(new_sock, input, BUF_SIZE);

    arg_list = parse_command(input);

    pid = fork();
    if (pid == -1)
    {
      diep("fork");
    }
    else if (pid == 0)
    { // child
      execvp(arg_list[0], arg_list);
    }
    else
    {
      waitpid(pid, NULL, 0);
    }

    char *response = "Command executed\n";

    if (send(new_sock, response, strlen(response), 0) == -1)
    {
      perror("send");
    }

    close(new_sock);
  }
  return 0;
}
