#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include "utils.h"

int main(int argc, char const *argv[])
{
  pid_t pid;
  char **arg_list;

  char input[BUF_SIZE];
  fgets(input, BUF_SIZE, stdin);
  arg_list = parse_command(input);

  pid = fork();
  if(pid == -1){
    perror("Fork: ");
    exit(EXIT_FAILURE);
  } else if(pid == 0){  // child
    execvp(arg_list[0], arg_list);
  } else {
    waitpid(pid, NULL, 0);
  }
  return 0;
}
