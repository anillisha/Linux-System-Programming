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
  returnflag1 = pipe(pipefd2);
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
