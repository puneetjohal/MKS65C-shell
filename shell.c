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

int countCommands (char * line) {
  int count = 1;
  while (*line) {
    if (strncmp(line,";",1) == 0) {
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

char** parse_commands (char * line) {
  int tokens = countCommands(line);
  char ** commands = malloc(sizeof(char *) * (tokens+1));
  for (int i = 0; i < tokens; i++) {
    commands[i] = strsep(&line, ";");
  }
  int i = 0;
  while(commands[i]) {
    if (strncmp(commands[i]," ",1) == 0) {
      commands[i] = &commands[i][1];
    }
    printf("%ld\n", strlen(commands[i]));
    printf("*%s*\n", &commands[i][strlen(commands[i])-1]);
    //program thinks that this points to the whole command until last command
    if (strncmp(&commands[i][(strlen(commands[i])-1], " ", 1) == 0) {
      printf("space was removed\n");
      commands[i][strlen(commands[i])-1] = 0;
    }
    i++;
  }
  return commands;
}

//checks if user is trying to exit or cd and runs those commands
//returns true if exit or cd was executed
int hardCoded(char ** args){
  if (strcmp(args[0],"exit") == 0) {
    printf("exiting shell...\n");
    exit(1);
    return 1;
  }
  else if (strcmp(args[0],"cd") == 0) {
    chdir(args[1]);
    return 1;
  }
  return 0;
}

//forks and execs command from line
int main() {
  while(1) {
    char cwd[256];
    printf("%s$ ", getcwd(cwd, sizeof(cwd)));
    char buf[100];
    fgets(buf, 100, stdin);
    buf[strlen(buf)-1] = 0;

    //separating commands based on semicolons
    int commands = countCommands(buf);
    char ** cmds = malloc(sizeof(char *) * (commands+1));
    cmds = parse_commands(buf);

    //iterate through each command
    int i = 0;
    while (cmds[i]) {
      printf("evaluating *%s*\n", cmds[i]);
      char * curcmd = cmds[i];
      int tokens = countTokens(curcmd);
      char ** args = malloc(sizeof(char *) * (tokens+1));
      args = parse_args(curcmd);
      //check for exit or cd
      if (hardCoded(args)){
        free(args);
        i++;
        continue;
      }
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
      i++;
    }
  }
  return 0;
}
