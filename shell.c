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

int countTokens (char * line){
  int count = 1;
  while (*line) {
    if (line[0] == ' ') {
      count++;
    }
    line++;
  }
  return count;
}

//reads through the line, separating the command from its arguments
char** parse_args(char * line){
  int tokens = countTokens(line);
  char ** args = malloc(sizeof(char *) * tokens);
  for (int i = 0; i < tokens; i++){
    args[i] = strsep(&line, " ");
    //printf("%s", *(args[i])); segfault-causing error was that i was trying to print a pointer and not deliminating it
  }
  return args;
}

//forks and execs command from line
void run_command(){
  char buf[100];
  printf("$ ");
  fgets(buf, 100, stdin);
  printf("\n");
  //printf("string is: %s\n", buf);
  char ** args = parse_args(buf);
  printf("args parsed");
  execvp(args[0], args);
  free(args);
}

int main(){
  run_command();
  return 0;
}
