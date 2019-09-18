/*
 ============================================================================
 Name    : client.c
 Author   : king
 Version   :
 Copyright  : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
int handle(int fd);
 
int main(void) {
 
  int nsd;
  char buf[1024];
 
  //char * myaddr = "47.104.29.114";
  //char* myaddr = "127.0.0.1";
  char * myaddr = "172.31.40.27"; 
  struct sockaddr_in addr;
 
  printf("welcome to echo client\n");
  nsd = socket(AF_INET, SOCK_STREAM, 0);
  //bzero(addr, sizeof(*addr));
  memset(&addr,0,sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(5000);
  addr.sin_addr.s_addr=inet_addr(myaddr);
 
  if (connect(nsd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
    printf("connect error \n");
    return -1;
  }
 
  sleep(5);
  handle(nsd);
  close(nsd);
  return EXIT_SUCCESS;
}
 
int handle(int fd) {
 
  char sendl[1024], rev[1024];
 
  int retn;
 
  for (;;) {
 
    memset(sendl,0,sizeof(sendl));
    memset(rev,0,sizeof(rev));
    if (fgets(sendl, 1024, stdin) == NULL) {
      break;
    }
    //
    write(fd, sendl, strlen(sendl));
    read(fd, rev,strlen(rev));
 
  }
 
  return 0;
}
