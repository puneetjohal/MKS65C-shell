#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//counts how many tokens there are in a command
int countTokens (char * line);

//reads through the line, separating the command from its arguments
char** parse_args(char * line);

//checks if user is trying to exit or cd and runs those commands without forking a child and execing
void hardCoded(char ** args);
