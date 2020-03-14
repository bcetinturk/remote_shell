#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#define LINE_LENGTH 1024

int main(int argc, char const *argv[])
{
  pid_t pid;
  char input_buffer[LINE_LENGTH];
  char **arg_list;
  char *token, seperator[] = "\t\n ";
  int i = 0;

  arg_list = (char **)malloc(LINE_LENGTH * sizeof(char *));

  fgets(input_buffer, LINE_LENGTH, stdin);
  token = strtok(input_buffer, seperator);
  while (token != NULL)
  {
    arg_list[i] = (char *)malloc(LINE_LENGTH * sizeof(char));
    arg_list[i] = token;
    i++;

    token = strtok(NULL, seperator);
  }

  arg_list[i] = NULL;

  for(int j=0; j<i; j++){
    printf("%s\n", arg_list[j]);
  }

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
