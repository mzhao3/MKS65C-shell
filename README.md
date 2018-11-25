# MKS65C-shell

## Features
It can execute commands separated by semi colons and any number of extra white spaces

## Bugs
extra white spaces proceeded by nothing will not run the functions, i.e.
ls      -l
will work
ls  
with empty spaces will not

## Functions
char ** parse_args( char * line );
char ** parsesemi_args(char * pine);
void noSpaacepls(char * oboi);
int main(int argc, char *argv[]);
