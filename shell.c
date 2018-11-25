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
    //printf("[%s]\n", cmds[i]);
  }
  cmds[i] = NULL;


  return cmds;

}

char ** parsesemi_args(char * pine){
  while(*pine == ' '){
    pine++;
  }
  char ** pmds = (char **) malloc(10 * sizeof(char *));
  char * c = pine;

  int i;
  for (i = 0; c ; i++ ) {
    pmds[i] = strsep( &c, ";" );
  }
  pmds[i] = NULL;
  return pmds;
}

void noSpaacepls(char * oboi){
  int i = 0;
  int c = 0;
  for(; oboi[i]; ++i)
  if(((i > 0 && !isspace(oboi[i-1])) || !isspace(oboi[i])))
  oboi[c++]= oboi[i];
  oboi[c] = '\0';

}

int main(int argc, char *argv[]) {
  int x = getpid();

  //fork();
  while(1) {
    //if (getpid() != x) {
      char path[100];

      printf("shell@PC$ ");
      fgets(path,100,stdin );

      path[strlen(path)-1] = '\0';
      //printf("\nthe thing u got:%s\n", path);
      noSpaacepls(path);

      char *s1 = path;

      char **separgs = parsesemi_args(s1);

      int i;
      for(i = 0; separgs[i];i++){
        char ** args = parse_args( separgs[i] );

        if (!strcmp(args[0], "exit")) {
          printf("Exiting shell...\n");
          exit(0);
        }

        if (!strcmp(args[0], "cd")) {
          char * path2 = args[1];
          //printf("%s\n", path);
          //if (path2 == NULL)
            //path2 = ".";
          //printf("%s\n", path);
          int err = chdir(path2);
          //printf("%d\n", err);
          if (err == -1)
            printf("%s\n", strerror(errno));

        }
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

  //}
  return 0;
}
