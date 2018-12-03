# MKS65C-shell
By Kevin Ly and Maggie Zhao

## Features
  Executes commands by forking
  Parses multiple commands with ;
  Change directories and exits  
  Works with any white space
  Simple Redirects with >, >>, >
  Simple Pipes

## Attempted
  Tab completion

## Bugs
  cd creates new processes, exit will not work after cd



## Functions
shell.c
handles all line parsing and executing command functions

char ** parse_args( char * line, const char * input);<br />
input: char * line, const char * input
returns: an aray from the line using strsep
strips leading white spaces parses line into array seperated by input

void noSpaacepls(char * oboi);<br />
input: char * oboi
returns:
strips white spaces within and after a char array

int checkfordirections(char * line); <br />
input: char * line
returns: a number based on a special character
">" returns 1
">>" returns 2
"<" returns 3
"|" returns 4

int main(int argc, char *argv[]) ;<br />
