#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>

char ** parse_args( char * line ) {
  while(*line == ' '){
    line++;
  }

  char ** cmds = (char **) malloc(10 * sizeof(char *));
  char * p = line;


  int i;
  for (i = 0; p ; i++ ) {
    cmds[i] = strsep( &p, " " );
    printf("[%s]\n", cmds[i]);
  }
  cmds[i] = NULL;


  return cmds;

}

void noSpaacepls(char * oboi){
  int i, c;
  for(i=c=0; oboi[i]; ++i)
    if(!isspace(oboi[i]) || (i > 0 && !isspace(oboi[i-1])))
      oboi[c++] = oboi[i];
    oboi[c] = '\0';
}

int main(int argc, char *argv[]) {
  int x = getpid();

  fork();
  while(1) {
    if (getpid() != x) {
      char path[100];

      printf("shell$ ");
      fgets(path,100,stdin );

      path[strlen(path)-1] = '\0';
      printf("\nthe thing u got:%s\n", path);
      noSpaacepls(path);

      char *s1 = path;
      char ** args = parse_args( s1 );


      int f = fork();
      if(f){
        wait(NULL);
      }
      if(!f){
        execvp(args[0], args);
      }
      free(args);



    }

  }
  return 0;
}
