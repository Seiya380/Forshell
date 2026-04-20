#include <stdlib.h>
#include <stdio.h>
#define FS_RL_BUFSIZE 1024
char *fs_read_line(void)
{
  int bufsize = FS_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "fs: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF) {                                   
      exit(EXIT_SUCCESS);                           
    }
    if (c == '\n') {
      putchar('\n');                                  
      buffer[position] = '\0';                      
      return buffer;
    }
    if (c == '\t') {                                  
      fs_autocomplete(buffer, position);
      continue;
    }
    else {        
      buffer[position] = c;
      putchar(c);                         
    } 
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += FS_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "fs: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}