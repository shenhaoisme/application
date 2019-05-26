#include "config.h"

static pthread_mutex_t app_mutex;



static void app_thread_entry(void)
{
	//thread_set_tid()
	msg_t msg;
	app_t app=APP1;
	while ( 0 == msgQ_recv(app, msg))
	{
	 test_log("receive %s\n",msg.text);
	}
}
void app_init(void)
{
	app_t app=APP2;
	if(0 != pthread_mutex_init(&app_mutex, NULL))
	{
		printf("app mutex fail\n");
	}
	
	if(0 != thread_creat(app, app_thread_entry))
	{
		printf("thread create fail\n");
	}
	else
		printf("thread start\n");
}

int main(int argc, char * argv[])
{
	app_t app=APP2;
	
	msg_init();
	app_init();
	run(app,FALSE);
	return 0;
}