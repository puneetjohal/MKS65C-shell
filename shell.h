#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//reads through the line, separating the command from its arguments
char** parse_args(char * line);

//forks and execs command from line
void run_command();
