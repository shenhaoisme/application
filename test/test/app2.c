#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include "configs.h" 

int main(int ac, char * av[])
{
	app_t app1=APP1;
	const char context[] = {"shenhao says hello"};
	send_msg(app1,context);
	return 0;
}