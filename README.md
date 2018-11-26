# MKS65C-shell

## Features
It can execute commands separated by semi colons and any number of extra white spaces

## Bugs
extra white spaces proceeded by nothing will not run the functions, i.e. <br />
ls          -l <br />
will work<br />
ls  <br />
with empty spaces will not<br />

On some machines(OSX), 'cd'-ing into a known directory will print out 'No such file or directory' but change directories anyways.

## Functions
char ** parse_args( char * line );<br />
char ** parsesemi_args(char * pine);<br />
void noSpaacepls(char * oboi);<br />
int main(int argc, char *argv[]);<br />
