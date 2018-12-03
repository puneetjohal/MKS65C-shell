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

int countTokens (char * line) {
  int count = 1;
  while (*line) {
    if (strncmp(line," ",1) == 0) {
      count++;
    }
    line++;
  }
  return count;
}

//reads through the line, separating the command from its arguments
char** parse_args (char * line) {
  int tokens = countTokens(line);
  char ** args = malloc(sizeof(char *) * (tokens+1));
  for (int i = 0; i < tokens; i++) {
    args[i] = strsep(&line, " ");
  }
  return args;
}

//forks and execs command from line
void run_command(){

}

int main() {
    printf("$ ");
    char buf[100];
    fgets(buf, 100, stdin);
    buf[strlen(buf)-1] = 0;
    printf("\n");
    //printf("command: %s\n", buf);
    int tokens = countTokens(buf);
    char ** args = malloc(sizeof(char *) * (tokens+1));
    args = parse_args(buf);
    //forking
    int f = fork();
    if (f) {
      int status;
      wait(&status);
    }
    else {
      execvp(args[0], args);
    }
    free(args);
  return 0;
}

//https://stackoverflow.com/questions/21896000/c-execvp-and-command-line-arguments
//http://www.cs.ecu.edu/karl/4630/sum01/example1.html
