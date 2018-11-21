
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

char ** parse_args( char * line ) {
  char ** cmds = (char **) malloc(10 * sizeof(char *));
  char * p = line;
  int i;
  for (i = 0; p; i++ ) {
    cmds[i] = strsep( &p, " " );
    printf("[%s]\n", cmds[i]);
  }
  cmds[i] = NULL;
  return cmds;
}

int main(int argc, char *argv[]) {
  int status;
  int x = getpid();
  fork();
  while(1) {
    if (getpid() != x) {
      char path[100];

      printf("shell$ ");
      scanf("%99s", path);
      printf("\nthe thing u got:%s\n", path);

      char *s1 = path;
      char ** args = parse_args( s1 );
      printf("%s", *args);
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
