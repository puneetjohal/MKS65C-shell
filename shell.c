#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include "shell.h"

//reads through the line, separating the command from its arguments
char** parse_args(char * line){
  char ** args = malloc(sizeof(char *) * 6);
  char * str = line;
  for (int i = 0; i < 6; i++){
    args[i] = strsep( &str, " ");
  }
  return args;
}

//forks and execs command from line
void run_command(){
  char command[100];
  printf("~$ ");
  scanf("%s", command);
  printf("\n");
  char ** args = parse_args(command);
  execvp(args[0], args);
  free(args);
}

int main(){
  run_command();
  return 0;
}
