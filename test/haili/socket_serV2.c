/*
============================================================================
Name : server.c
Author : king
Version :
Copyright : Your copyright notice
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
 
#include "threadAPI.h"
int ID = 0;

int handle(int point);
 
void fun(void)
{
	switch(thread_get_status(ID))
	{
		case THREAD_IS_CLOSED:
			test_log("THREAD_IS_CLOSED");
			break;
		case THREAD_IS_RUNNING:
			test_log("THREAD_IS_RUNNING");
			break;

	}
	test_log("%d",get_name(ID));
	test_log("run OK");

}
int main()
{
	int i;
	for(i = 0 ; i < 10; i++)
	{
		thread_creat(i, fun);
		ID++;
		sleep(1);
	}
	

	return 0;
}

int main1(void) 
{
	int sfd, ind;
	struct sockaddr_in addr;
	struct sockaddr_in clent;
	char resv[1024], sendbuf[1024];
	char buf[1024];
	//char * myaddr = "47.104.29.114"; //这个不能绑定
	char * myaddr = "172.31.40.27";
	//char * myaddr = "127.0.0.1";
	int ret; // 返回值设置
	socklen_t lent;
	int pid;
	
	addr.sin_family = AF_INET; //IPv4 Internet protocols
	 
	addr.sin_port = htons(5000); //这里输入服务器端口号
 
	addr.sin_addr.s_addr = inet_addr(myaddr);
	//addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//INADDR_ANY表示本机IP
	 
	//获取socket描述符，IPV4asd
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd < 0) 
	{
		printf("socket error \n");
		return -1;
	}
	//将套接子与指定端口链接
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
		printf("bind error \n");
		return -1;
	}
	 
	//监听套接子
	printf("listen start \n");
	if (listen(sfd, 1024) < 0) 
	{
		printf("listen error \n");
		return -1;
	}
	 
	for (;;) {
		//接受来自客户端的信息
		printf("accept start \n");
		memset(&clent, 0, sizeof(clent));
		lent = sizeof(clent);
		ind = accept(sfd, (struct sockaddr *) &clent, &lent);
		if (ind < 0) {
			printf("accept error %d \n", ind);
			return -1;
		}
 
		printf("infor \n");
		//inet_ntop 函数 , ntohs 函数
		printf("clent addr%s porit %d\n", inet_ntop(AF_INET, &clent.sin_addr, buf, sizeof(buf)),ntohs(clent.sin_port));
		 
		// pid = fork();
		 
		// if (pid == 0) 
		// {
		// 	//子进程
		// 	close(sfd);
		// 	handle(ind);
		// }
		//  else if (pid < 0) 
		// {
		// 	//error
		// 	close(ind);
		// } else {} //nothing to do on father

		thread_creat(ID, fun);
		ID++;
	}
	 

}
 
int handle(int point) {
 
	int retn;
	char buf[1024];
	 
	for (;;) {
		retn = read(point, buf, sizeof(buf));
		if (retn < 0) {
			printf("read error \n");
			close(point);
			break;
		} else if (retn == 0) {
			printf("client exit \n");
			close(point);
		break;
		}
	 
		printf("client:%s\n", buf);
		 
		if (strcmp("exit", buf) == 0) {
			printf("exit \n");
			close(point);
			return 0;
		}
	}
	return 0;
}
 
