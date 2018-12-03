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

//check for >, >>, <, | return an int based on which one
int checkfordirections(char * line){
  int i = 0;
  for(;i < strlen(line);i++){
    if(line[i] == '>' && line[i+=1] == '>'){
      return 2;
    }
  }
  for(int i = 0;line[i];i++){
    if(line[i] == '>'){
      return 1;
    }
    if(line[i] == '<'){
      return 3;
    }
    if(line[i] == '|'){
      return 4;
    }
  }
  return 0;
}

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

    char *s1 = path;
    char **separgs = parse_args(s1, ";");


    int i;
    for(i = 0; separgs[i];i++){
      noSpaacepls(separgs[i]);
      int s;
      s = checkfordirections(separgs[i]);


      // >
      if(s == 1){
        char * tempsplit = separgs[i];
        //printf("basic redirect \n");
        char * firstcmd;
        char * secondfile;
        firstcmd = (char*)malloc(100*sizeof(char));
        secondfile = (char*)malloc(100*sizeof(char));

        char ** direct = parse_args(tempsplit,">");
        firstcmd = direct[0];
        noSpaacepls(firstcmd);
        char ** firstcmdboi = parse_args(firstcmd," ");
        char ** secondfileboi = parse_args(direct[1]," ");
        secondfile = secondfileboi[0];
        noSpaacepls(secondfile);


        int f = fork();

        if(f){
          wait(NULL);
        }
        if(!f){
          int file = open(secondfile, O_WRONLY | O_TRUNC | O_CREAT);
          if(file == -1){
            printf("error \n");
            return 0;
          }
          int copy = dup(1);
          dup2(file,1);
          execvp(firstcmdboi[0],firstcmdboi);
          dup2(copy,1);
          close(file);
          return 0;
        }


      }
      // >>
      if(s == 2){
        char * tempsplit = separgs[i];
        char ** thing = parse_args(tempsplit,">>");

        //printf("append redirect \n");
        char ** firstcmd;
        char ** secondfile;
        firstcmd = (char**)malloc(100*sizeof(char));
        secondfile = (char**)malloc(100*sizeof(char));

        //char ** direct = parse_args(tempsplit,">>");
        //firstcmd = direct[0];
        noSpaacepls(thing[0]);
        noSpaacepls(thing[2]);
        firstcmd = parse_args(thing[0], " ");
        secondfile = parse_args(thing [2], " ");

        //secondfile = direct[1];
        // printf("first half\n");
        // print_arr(firstcmd);
        // printf("second half\n");
        // print_arr(secondfile);
        char * path = secondfile[0];

        int f = fork();

        if(f){
          wait(NULL);
        }
        if(!f){
          int file = open(path, O_CREAT| O_WRONLY| O_APPEND , 0777);
          if(file == -1){
            printf("%s", strerror(errno));
            return 0;
          }
          int copy = dup(1);
          dup2(file,1);
          execvp(firstcmd[0],firstcmd);
          dup2(copy,1);
          close(file);
          return 0;
        }


      }
      //<
      if(s == 3){
        char * tempsplit = separgs[i];
        //printf("back redirect \n");

        char * firstcmd;
        char * secondfile;
        firstcmd = (char*)malloc(100*sizeof(char));
        secondfile = (char*)malloc(100*sizeof(char));

        char ** direct = parse_args(tempsplit,"<");
        firstcmd = direct[0];
        noSpaacepls(firstcmd);
        char ** firstcmdboi = parse_args(firstcmd," ");
        char ** secondfileboi = parse_args(direct[1]," ");
        secondfile = secondfileboi[0];
        noSpaacepls(secondfile);

        int f = fork();

        if(f){
          wait(NULL);
        }
        if(!f){

          int file = open(secondfile, O_RDONLY);
          if(file == -1){
            printf("error \n");
            return 0;
          }
          int copy = dup(0);
          dup2(file,0);
          execvp(firstcmdboi[0],firstcmdboi);
          dup2(copy,0);
          close(file);
          return 0;
        }

      }
      // |
      if(s == 4){
        //char * tempsplit = separgs[i];
        //printf("pipes \n");
        char ** thing = parse_args(separgs[i],"|");
        noSpaacepls(thing[0]);
        noSpaacepls(thing[1]);
        char ** firstcmd= parse_args(thing[0], " ");
        char ** secondcmd= parse_args(thing [1], " ");


        int p[2];
        pipe(p);
        int in = dup(0);
        int out = dup(1);
        int f = fork();
        if(!f){
          int g = fork();
          if (!g) {
            close( STDOUT_FILENO );
            close(p[0]);
            dup2( p[1], STDOUT_FILENO );
            execvp(firstcmd[0], firstcmd);

          }
          else {
            wait(NULL);
            close(STDIN_FILENO);
            close(p[1]);
            dup2( p[0], STDIN_FILENO );
            execvp(secondcmd[0], secondcmd);

          }

        }
        else {
          int status = 0;
          close(p[0]);
          close(p[1]);
          wait(&status);
          dup2(in,0);
          dup2(out,1);
        }

      }

      //execute regular commands
      if(s == 0){
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
  }


  return 0;
}
