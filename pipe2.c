/*
Example program 2 − Program to write and read two messages through the pipe using the parent and the child processes.
Algorithm

Step 1 − Create a pipe.

Step 2 − Create a child process.

Step 3 − Parent process writes to the pipe.

Step 4 − Child process retrieves the message from the pipe and writes it to the standard output.

Step 5 − Repeat step 3 and step 4 once again.

Source Code: pipewithprocesses.c
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  int pipefds[2];
  int returnflag;
  int pid;
  char write_pipes[2][20]={"Hi","Hello"};
  char readmessage[20];
  returnflag = pipe(pipefds);
  if(returnflag == -1)
  {
   printf("unable to create pipe\n");
   return 1;
  } 
  pid=fork();
  if(pid==0)
  {
   read(pipefds[0],readmessage,sizeof(readmessage));
   printf("child process -Reading from pipe -Message 1 is %s\n",readmessage);
   read(pipefds[0], readmessage, sizeof(readmessage));
   printf("Child process -Reading from pipe -message 2 is %s\n", readmessage);
  }
else
 {
   printf("Parent Process - Writing to pipe - Message 1 is %s\n", write_pipes[0]);
  write(pipefds[1], write_pipes[0], sizeof(write_pipes[0]));
printf("Parent Process - Writing to pipe - Message 2 is %s\n", write_pipes[1]);
  write(pipefds[1], write_pipes[1], sizeof(write_pipes[1]));
  
}

}
