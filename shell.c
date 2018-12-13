#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
//#include "shell.h"

//------------------------------COUNTER METHODS---------------------------------

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


//------------------------------PARSING METHODS---------------------------------

//reads through the line, separating the command from its arguments
char** parse_args (char * line) {
  int tokens = countTokens(line);
  char ** args = malloc(sizeof(char *) * (tokens+1));
  for (int i = 0; i < tokens; i++) {
    args[i] = strsep(&line, " ");
  }
  return args;
}

//separates the line around semicolons
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

//separates the command around redirection indicators
char** parse_redir (char * line){
  char** retArr = malloc(sizeof(char *) * 3);
  int i = 0;
  while (line) {
    retArr[i] = strsep(&line, "<>|");
    i++;
  }
  i = 0;
  while(retArr[i]) {
    //removes space in the front
    if (strncmp(retArr[i]," ",1) == 0) {
      retArr[i] = &retArr[i][1];
    }
    //removes space in the back
    if (strncmp(&retArr[i][strlen(retArr[i])-1], " ", 1) == 0) {
      retArr[i][strlen(retArr[i])-1] = 0;
    }
    i++;
  }
  return retArr;
}


//------------------------------CHAR** PRINTER----------------------------------

//printer for debugging
void printer(char ** arr){
  int i = 0;
  while (arr[i]) {
    printf("'%s'\n", arr[i]);
    i++;
  }
}


//------------------------------EXECING METHODS---------------------------------

//checks if user is trying to exit or cd and runs those commands
//returns true if exit or cd was executed
int hardCoded(char * cmd){
  //seperating args based on spaces
  int tokens = countTokens(cmd);
  char ** args = malloc(sizeof(char *) * (tokens+1));
  args = parse_args(cmd);

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

//forks and execs any commands that aren't exit or cd
//handles redirection
void exec(char * cmd){
  /*//separating between < > or |
  char ** redir = malloc(sizeof(char *) * 3);
  redir = parse_redir(cmd);
  printer(redir);

  //counting # of elements in redir
  int redirLen = 0;
  while(redir[redirLen]){
    redirLen++;
  }

  //if there is more than one redir element, handle redirection
  if (redirLen > 1) {
    //stdout redirected into a file
    if ( strcmp(redir[1],">") == 0 ){
      //int fd = open()
    }
    //stdin redirected from a file to the command
    else if ( strcmp(redir[1],"<") == 0 ){

    }
    //stdout of first command redirected into the stdin of the next
    else if ( strcmp(redir[1],"|") == 0 ){

    }
  }*/

  //no redirection
  //else {
    //seperating args based on spaces
    int tokens = countTokens(cmd);
    char ** args = malloc(sizeof(char *) * (tokens+1));
    args = parse_args(cmd);
    //fork and exec
    int f = fork();
    if (f) {
      int status;
      wait(&status);
    }
    else {
      int catch = execvp(args[0],args);
      exit(catch);
    }
  //}
}


//-----------------------------------MAIN---------------------------------------

//forks and execs command from line
int main() {
  int isExiting = 0;
  while(!isExiting) {
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
    while (cmds[i] && !isExiting) {
      //printf("evaluating *%s*\n", cmds[i]);

      //check for exit or cd
      int checker = hardCoded(cmds[i]);
      if (checker == 2){
        free(cmds);
        isExiting = 1;
        break;
      }
      else if (checker == 1){
        i++;
        continue;
      }

      //forking and execing, moving on to next cmd
      else {
        printf("command %s\n", cmds[i]);
        exec(cmds[i]);
        i++;
      }
    }
    //freeing all cmds
    free(cmds);
  }
  return 0;
}
