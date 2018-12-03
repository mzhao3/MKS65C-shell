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
shell.c <br />
handles all line parsing and executing command functions

char ** parse_args( char * line, const char * input);<br />
input: char * line, const char * input <br />
returns: an aray from the line using strsep<br />
strips leading white spaces parses line into array seperated by input<br />

void noSpaacepls(char * oboi);<br />
input: char * oboi<br />
returns:<br />
strips white spaces within and after a char array<br />

int checkfordirections(char * line); <br />
input: char * line<br />
returns: a number based on a special character<br />
">" returns 1<br />
">>" returns 2<br />
"<" returns 3<br />
"|" returns 4<br />

int main(int argc, char *argv[]) ;<br />
