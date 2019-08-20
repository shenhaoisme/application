#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <sys/types.h>
#include <sys/wait.h>

#include <string.h> // for strlen

int main()
{
  int fd[2];
  pid_t pid;
  char buf[100];
  if(pipe(fd) < 0)
  {
    return -1;
  }

  pid = fork();
  if(pid > 0) //parent process write some message to clild process
  {
    sprintf(buf, "%s", "hello, my son");
    close(fd[0]); //for write, need to close read pipe(because only one channel is open)
    write(fd[1], buf, strlen(buf));
    close(fd[1]);
    wait(NULL);// why? what the meaning!
    return 0;
  }
  else
  {
    close(fd[1]);// for read
    while(read(fd[0], &buf, 1) > 0)//read a byte once
      printf("%s", buf); 
      
    printf("\n"); 
    close(fd[0]);
    return 0;
  }

}