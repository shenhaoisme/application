#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include "configs.h"  

static app_t app1=APP1; 
void callback(void)
{
	get_msg(app1);
}

//msg 做成一个app1的一个线程
int main(int ac, char * av[])
{
	//get message from which one 
	thread_creat(app1,callback);
	run(app1,FALSE); //execve callback 
	test_log("hello");
	run(app1,FALSE);
	//test_log("get tid is %ld", get_tid(app1));
	
	return 0;
}



/*
//test msg receive/send


int main(int ac, char * av[])
{
	app_t app2=APP1;
	get_msg(app2);
	return 0;
}
*/
/*
//test thread
void callback(void)
{
	test_log("get pid %ld ",getpid());
}
int main1(int ac, char * av[])
{
	app_t app1=APP1;
	thread_creat(app1,callback);
	run(app1);
	test_log("get tid is %ld", get_tid(app1));

	return 0;
}
*/