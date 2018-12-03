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

//counts how many tokens there are in a command
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

//checks if user is trying to exit or cd and runs those commands
void hardCoded(char ** args){
  if (strcmp(args[0],"exit") == 0) {
    printf("Exiting shell...\n");
    exit(1);
  }
  if (strcmp(args[0],"cd") == 0) {

  }
}

//forks and execs command from line
int main() {
  while(1) {
    char cwd[256];
    printf("%s$ ", getcwd(cwd, sizeof(cwd)));
    char buf[100];
    fgets(buf, 100, stdin);
    buf[strlen(buf)-1] = 0;
    printf("\n");
    //printf("command: %s\n", buf);
    int tokens = countTokens(buf);
    char ** args = malloc(sizeof(char *) * (tokens+1));
    args = parse_args(buf);
    //check for exit or cd
    hardCoded(args);
    //forking
    int f = fork();
    if (f) {
      int status;
      wait(&status);
    }
    else {
      execvp(args[0],args);
    }
    free(args);
  }
  return 0;
}
