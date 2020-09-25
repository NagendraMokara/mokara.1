#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//Convert the argument to int
int arg_to_int(char * arg){
  //check if its not null
  if(arg == NULL){
    fprintf(stderr, "Error: Null argument\n");
    exit(-1);
  }

  int value = atoi(arg);  //convert to int
  if(arg <= 0){ //checking for negative value
    fprintf(stderr, "Error: Invalid argument value\n");
    exit(-1);
  }

  return value; //return argument value
}

int main(int argc, char * argv[]){

  int i, pr_limit, pr_count, status;
  char buf[MAX_CANON+1];
  char *eargv[3+1];  //our testsim takes only 3 arguments + 1 for NULL

  if(argc != (1+1)){
    fprintf(stderr, "Usage: runsim processes\n");
    return -1;
  }

  pr_limit = arg_to_int(argv[1]);

  while(feof(stdin) == 0){  //while we haven't reached the end of file

    if(pr_count == pr_limit){
      wait(&status);
      pr_count = pr_count - 1;
    }

    //clear the buffer
    memset(buf, 0, MAX_CANON+1);

    //get line from input
    if(fgets(buf, MAX_CANON, stdin) == NULL){
      break;
    }

    if(buf[0] == '\n'){ // empty line
      continue;
    }

    //make the eargv for exec
    eargv[0] = strtok(buf, " \t\r\n");
    eargv[1] = strtok(NULL, " \t\r\n");
    eargv[2] = strtok(NULL, " \t\r\n");
    eargv[3] = NULL;

    //create a child process
    switch(fork()){
      case -1:
        perror("fork");
        break;

      case 0:

        close(0);
        execvp(eargv[0], eargv);
        perror("execvp");
        exit(0);
        break;
      default:
        pr_count = pr_count + 1;
        break;
    }

    //clear finished processes, without blocking
    for(i=pr_count; i > 0; i--){
      if(waitpid(-1, &status, WNOHANG) > 0){
        pr_count = pr_count - 1;
      }
    }

  } //end while

  //wait for all children to finish
  for(i=pr_count; i > 0; i--){
    if(waitpid(-1, &status, 0) > 0){
      pr_count = pr_count - 1;
    }
  }

  return 0;
}
