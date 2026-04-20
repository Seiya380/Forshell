#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "history.c"
#include "builtin.c"
#include "parse.c"
#include "pipe.c"
#include "launch.c"
#include "fs_exec.c"
#include "fs_read_line.c"
#include "signals.c"

void fs_loop(void)
{
  char *line;
  char **args;
  int status;
  char cwd[1024];


  
  signal(SIGINT, handle_sigint); //Traite les signals unix pour le terminal

  do {
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    printf("Forshell> ");
    line = fs_read_line();
    args = fs_split_line(line);
    status = fs_execute(args);
    fs_history(strdup(line));

    free(line);
    free(args);
  } while (status);
}