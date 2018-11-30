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
  char ** args = malloc(sizeof(char *) * (tokens+1));
  int i = 0;
  for (i; i < tokens; i++){
    args[i] = strsep(&line, " ");
  }
  //args[i+1] = NULL;
  return args;
}

//forks and execs command from line
void run_command(){
  char buf[100] = "ls -l -a";
  printf("$ ");
  fgets(buf, 100, stdin);
  printf("\n");
  printf("%s\n", buf);
  char ** args = parse_args(buf);
  execvp(args[0], args);
  free(args);
}

int main(){
  run_command();
  return 0;
}

//https://stackoverflow.com/questions/21896000/c-execvp-and-command-line-arguments
//http://www.cs.ecu.edu/karl/4630/sum01/example1.html
