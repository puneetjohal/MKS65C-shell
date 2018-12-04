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
    //removes space in the front
    if (strncmp(commands[i]," ",1) == 0) {
      commands[i] = &commands[i][1];
    }
    //removes space in the back
    if (strncmp(&commands[i][strlen(commands[i])-1], " ", 1) == 0) {
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
    return 2;
  }
  else if (strcmp(args[0],"cd") == 0) {
    chdir(args[1]);
    return 1;
  }
  return 0;
}

int execRedir (char** args) {
  int j = 0;
  while (args[j]) {
    //redirecting stdout
    if (strcmp(args[j],">") == 0){
      char ** outputting = malloc(sizeof(char *) * 16); //left side cmd
      char ** inputting = malloc(sizeof(char *) * 16); //right side cmd
      int i = 0;
      while (i<j) {
        outputting[i] = args[i];
        i++;
      }
      i+=2;
      while (args[i]) {
        inputting[i] = args[i];
        i++;
      }

      /*
      int f = dup(1); //stdout is duplicated to fd f
      dup2(0,1); //stdout is redirected to stdin, stdout is closed
      execvp(outputting[0],outputting);
      int catch = execvp(inputting[0],inputting);
      dup2(f,1); //stdout revived
      exit(catch);
      */

      int fd = open(inputting, O_CREAT | O_WRONLY, 0777);
      int backup = dup(1);
			dup2(fd, 1);
			close(fd);
      dup2(1, backup);
			execvp(outputting[0], outputting);
			exit(0);
    }
    //redirecting stdin
    if (strcmp(args[j],"<") == 0){

    }
    //pipe
    if (strcmp(args[j],"|") == 0){

    }
    j++;
  }
  return execvp()
}

//forks and execs command from line
int main() {
  int isExisting = 0;
  while(!isExisting) {
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
    while (cmds[i] && !isExisting) {
      //printf("evaluating *%s*\n", cmds[i]);
      char * curcmd = cmds[i];
      int tokens = countTokens(curcmd);
      char ** args = malloc(sizeof(char *) * (tokens+1));
      args = parse_args(curcmd);
      //check for exit or cd
      int checker = hardCoded(args);
      if (checker == 2){
        free(args);
        free(cmds);
        isExisting = 1;
        break;
      }
      else if (checker == 1){
        free(args);
        i++;
        continue;
      }
      //forking
      else {
        int f = fork();
        if (f) {
          int status;
          wait(&status);
        }
        else {
          //check for redirection
          int j = 0;
          while (args[j]) {
            //redirecting stdout
            if (strcmp(args[j],">") == 0){

            }
            //redirecting stdin
            if (strcmp(args[j],"<") == 0){

            }
            //pipe
            if (strcmp(args[j],"|") == 0){

            }

          }
          int catch = execvp(args[0],args);
          exit(catch);
        }
        free(args);
        i++;
      }
    }
    free(cmds);
  }
  return 0;
}
