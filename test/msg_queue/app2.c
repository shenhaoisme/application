#include "config.h"

static pthread_mutex_t app_mutex;
app_t app1=APP1;
static void app_thread_entry(void)
{
	//thread_set_tid()
	msg_t msg;
	
	while ( 0 == msgQ_recv(app1, msg))
	{
	 test_log("receive %s\n",msg.text);
	}
}
void app_init(void)
{
	if(0 != pthread_mutex_init(&app_mutex, NULL))
	{
		printf("app mutex fail\n");
	}
	
	if(0 == thread_creat(app1, app_thread_entry))
	{
		printf("thread create fail\n");
	}
	else
		printf("thread start\n");
}

int main(int argc, char * argv[])
{
	app_t app1=APP1;
	
	msg_init();
	app_init();
	run(app1,TRUE);
	return 0;
}