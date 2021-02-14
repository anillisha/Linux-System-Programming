#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
  char write_pipe[2][20]={"hi","hello"};
  char read_pipe[20];
  int pipefds[2];
  int returnstatus;

  returnstatus = pipe(pipefds);
  if(returnstatus ==-1)
  {
    printf("unable to create pipes\n");
    return 1;
  }
  printf("write to pipe -message 1 is %s\n",write_pipe[0]);
  write(pipefds[1],write_pipe[0],sizeof(write_pipe[0]));
  read(pipefds[0],read_pipe,sizeof(read_pipe));
  printf("Reading from pipe – Message 1 is %s\n", read_pipe);
  write(pipefds[0], write_pipe[1], sizeof(write_pipe[0]));
   read(pipefds[1], read_pipe, sizeof(read_pipe));
   printf("Reading from pipe – Message 2 is %s\n", read_pipe);
   return 0;
}
