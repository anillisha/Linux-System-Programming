/*-------------------------------------------------------------
  Two-way Communication Using Pipes

Following are the steps to achieve two-way communication −

Step 1 − Create two pipes. First one is for the parent to write and child to read, say as pipe1. Second one is for the child to write and parent to read, say as pipe2.

Step 2 − Create a child process.

Step 3 − Close unwanted ends as only one end is needed for each communication.

Step 4 − Close unwanted ends in the parent process, read end of pipe1 and write end of pipe2.

Step 5 − Close the unwanted ends in the child process, write end of pipe1 and read end of pipe2.

Step 6 − Perform the communication as required.


---------------------------------------------------------------
Sample Programs

Sample program 1 − Achieving two-way communication using pipes.
Algorithm

Step 1 − Create pipe1 for the parent process to write and the child process to read.

Step 2 − Create pipe2 for the child process to write and the parent process to read.

Step 3 − Close the unwanted ends of the pipe from the parent and child side.

Step 4 − Parent process to write a message and child process to read and display on the screen.

Step 5 − Child process to write a message and parent process to read and display on the screen.

*/

/*
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>


int main()
{
  int pipefd1[2],pipefd2[2];
  int returnflag1,returnflag2;
  int pid;
  char pip1_write[20]="hi";
  char pip2_write[20]="hello";
  char readmessage[20];

  returnflag1 = pipe(pipefd1);
  if(returnflag1==-1)
  {
   printf("Unable to create pipe 1\n");
   return 1;
  }

  if(returnflag2==-1)
  {
   printf("Unable to create pipe 1\n");
   return 1;
  }
  
  pid=fork();
  if(pid !=0)
  {
   // close(pipefd1[0]);// Close the unwanted pipe1 read side
   // close(pipefd2[1]);
    
    printf("write to parent side ->%s\n",pip1_write);
    write(pipefd1[1],pip1_write,sizeof(pip1_write));
    read(pipefd2[0],readmessage,sizeof(readmessage));
    printf("read to parentside side ->%s\n",readmessage);
  }else
  {
   // close(pipefd1[1]);// Close the unwanted pipe1 read side
    //close(pipefd2[0]);
  
    //printf("write to parent side ->%s\n",pip2_write);
    //write(pipefd2[1],pip2_write,sizeof(pip2_write));
  
    read(pipefd1[0],readmessage,sizeof(readmessage));
    printf("read to parentside side ->%s\n",readmessage);
    
   printf("write to parent side ->%s\n",pip2_write);
   write(pipefd2[1],pip2_write,sizeof(pip2_write));
  
  }
return 0;

}
*/

#include<stdio.h>
#include<unistd.h>

int main() {
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





