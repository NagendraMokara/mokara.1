#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//Convert the argument to int
int arg_to_int(char * arg){
  //check if its not null
  if(arg == NULL){
    fprintf(stderr, "Error: Null argument\n");
    exit(-1);
  }

  int value = atoi(arg);  //convert to int
  if(arg <= 0){ //check for negative value
    fprintf(stderr, "Error: Invalid argument value\n");
    exit(-1);
  }

  return value; //return argument value
}

int main(int argc, char * argv[]){
  char msg[10]; // buffer message

  if(argc != (2+1)){  //check number of arguments
    //show help menu
    fprintf(stderr, "Usage: testsim sleep_sec num_sleeps\n");
    fprintf(stderr, "sleep_sec - Seconds to sleep\n");
    fprintf(stderr, "num_sleeps - Repeat factor\n");
    return -1;
  }

  //get our arguments
  const int sleep_sec = arg_to_int(argv[1]);
  int num_sleeps = arg_to_int(argv[2]);

  //create the message to print
  snprintf(msg, sizeof(msg), "%i", getpid());

  //loop until we have no more repeats
  while(num_sleeps-- > 0){
    sleep(sleep_sec);
    fprintf(stderr, "%s\n", msg); //show the message
  }

  return 0;
}
