#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <ctype.h>
#include <pwd.h>
#include <limits.h>

//looks through a pointer and slices by input
char ** parse_args( char * line, const char * input ) {
  while(*line == ' '){
    line++;
  }

  char ** cmds = (char **) malloc(10 * sizeof(char *));
  char * p = line;

  int i;
  for (i = 0; p ; i++ ) {
    cmds[i] = strsep( &p, input );
    //printf("[%s]\n", cmds[i]);
  }
  cmds[i] = NULL;
  return cmds;

}

//it takes a char pointer and deletes any extra white spaces does not return
void noSpaacepls(char * oboi){
  int i = 0;
  int c = 0;
  for(; oboi[i]; ++i)
    if(((i > 0 && !isspace(oboi[i-1])) || !isspace(oboi[i])))
      oboi[c++]= oboi[i];
  oboi[c] = '\0';

  int b = strlen(oboi)-1;
  for(;b > 1;b--){

    if(oboi[b] == ' '){
      oboi[b] = '\0';
    }
    if(oboi[b] != ' '){
      break;
    }

  }

}
//[what the heckk;what      ]
//[what the heckk;what]
int main(int argc, char *argv[]) {
  int x = getpid();
  char * user = getpwuid(getuid()) -> pw_name;
  char host[64];
  gethostname(host,64);
  char cwd[PATH_MAX];
  while(1) {
    char path[100];
    if(getcwd(cwd,sizeof(cwd))!=NULL){
      printf("%s@%s:%s$ ",user,host,cwd);
    }
    else{
      printf("error");
    }

    fgets(path,100,stdin );
    path[strlen(path)-1] = '\0';
    noSpaacepls(path);

    char *s1 = path;
    char **separgs = parse_args(s1, ";");


    int i;
    for(i = 0; separgs[i];i++){
      char ** args = parse_args(separgs[i], " " );


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
      if(!f && strcmp(args[0], "cd")){
        execvp(args[0], args);
        if(errno ==2){
          printf("%s: command not found \n",args[0]);
        }

      }
      free(args);
    }

  }

  //}
  return 0;
}
