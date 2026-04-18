#include "builtin.c"
#include "pipe.c"
#include "parse.c"
#include "launch.c"
#include "fs_exec.c"
#include "fs_read_line.c"
#include <stdio.h>
void fs_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = fs_read_line();
    args = fs_split_line(line);
    status = fs_execute(args);

    free(line);
    free(args);
  } while (status);
}