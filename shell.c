#include <stdio.h>
#include <stdlib.h>
#include <unilib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fnctl.h>
#include "shell.h"

//reads through the line, separating the command from its arguments
char** parseargs(char * line){
  char ** str = malloc(sizeof(char *) * 6);
  char * s1 = line;
  for (int i = 0; i < 6; i++){
    str[i] = strsep( &s1, " ");
  }
  return str;
}

//forks and execs command from line
void runCommand(char **){
  char command[100];
  printf("~$ ");
  scanf("%s", command);
  printf("\n");
  char ** args = parse_args(command);
  execvp(args[0], args);
  free(args);
}

int main(){
  rumCommand();
  return 0;
}
