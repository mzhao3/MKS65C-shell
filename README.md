# MKS65C-shell

## Features
It can execute commands separated by semi colons and any number of extra white spaces

## Bugs
extra white spaces proceeded by nothing will not run the functions, i.e. <br />
ls________ -l <br />
will work<br />
ls  <br />
with empty spaces will not<br />

## Functions
char ** parse_args( char * line );<br />
char ** parsesemi_args(char * pine);<br />
void noSpaacepls(char * oboi);<br />
int main(int argc, char *argv[]);<br />
