#include "config.h"


static pthread_mutex_t app_mutex;
app_t app1=APP1;
static void app_thread_entry(void)
{
	//thread_set_tid()
	msg_t msg={"shenhao syas hello"};
	if(!msgQ_send(app1, msg))
	{
		printf("send OK !\n");
	}
	else
		printf("send KO ! \n");
	
}
void app_init(void)
{
	if(0 != pthread_mutex_init(&app_mutex, NULL))
	{
		printf("app mutex fail\n");
	}
	
	if(0 != thread_creat(app1, app_thread_entry))
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
	run(app1,FALSE);
	return 0;
}
