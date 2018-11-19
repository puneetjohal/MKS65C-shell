#include <stdio.h>
#include <stdlib.h>
#include <unilib.h>
#include <string.h>

//reads through the line, separating the command from its arguments
char** parseargs(char * line);

//forks and execs command from line
void runCommand(char **);
