# MKS65C-shell
## PJSH
by Puneet Johal

## Features
* Forks and execs commands
* Hardcoded `cd` command changes directories
* Hardcoded `exit` command terminates the shell
* Execs multiple commands on the same line separated by `;`  
  * Note: space in front of or behind semicolon does not matter
* Redirects stdin and stdout using arrows (`>` and `<`)
* Redirection using pipes (`|`)

## Attempted
* Eliminating input restrictions for a more forgiving UI

## Bugs
* Redirecting output into a file that already exists will not overwrite all the contents of the file if the length of the contents is longer than what you are writting into it.
* Piping doesn't really work

## Files and Function Headers
