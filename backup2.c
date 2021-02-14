#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main() 
{
   int pipefd1[2],pipefd2[2];
   int returnstatus1, returnstatus2;
   int pid;
   char pip1_write[20]="hi";
   char pip2_write[20]="hello";
   char readmessage[20];

   returnstatus1 = pipe(pipefd1);
   
   if (returnstatus1 == -1) {
      printf("Unable to create pipe 1 \n");
      return 1;
   }
   returnstatus2 = pipe(pipefd2);
   
   if (returnstatus2 == -1) {
      printf("Unable to create pipe 2 \n");
      return 1;
   }
   pid = fork();
   
   if (pid != 0) // Parent process 
   {
      close(pipefd1[0]); // Close the unwanted pipe1 read side
      close(pipefd2[1]); // Close the unwanted pipe2 write side
      printf("In Parent: Writing to pipe 1 – Message is %s\n", pip1_write);
      write(pipefd1[1], pip1_write, sizeof(pip1_write));
      read(pipefd2[0], readmessage, sizeof(readmessage));
      printf("In Parent: Reading from pipe 2 – Message is %s\n", readmessage);
   } else { //child process
      close(pipefd1[1]); // Close the unwanted pipe1 write side
      close(pipefd2[0]); // Close the unwanted pipe2 read side
      read(pipefd1[0], readmessage, sizeof(readmessage));
      printf("In Child: Reading from pipe 1 – Message is %s\n", readmessage);
      printf("In Child: Writing to pipe 2 – Message is %s\n", pip2_write);
      write(pipefd2[1], pip2_write, sizeof(pip2_write));
   }
   return 0;
}
