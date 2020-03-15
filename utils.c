#include <stdlib.h>
#include <string.h>
#include "utils.h"

char **parse_command(char *input_buffer)
{
  char **arg_list = (char **)malloc(sizeof(char *) * BUF_SIZE);
  char *seperator = "\n\t ";

  char *token = strtok(input_buffer, seperator);
  int position = 0;
  while (token != NULL)
  {
    arg_list[position] = (char *)malloc(BUF_SIZE * sizeof(char));
    arg_list[position] = token;
    position++;

    token = strtok(NULL, seperator);
  }

  arg_list[position] = NULL;

  return arg_list;
}

void diep(char *s)
{
  perror(s);
  exit(EXIT_FAILURE);
}