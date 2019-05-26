#include "config.h"


static pthread_mutex_t app_mutex;

static void app_thread_entry(void)
{
	//thread_set_tid()
	app_t app=APP1;
	msg_t msg={"shenhao syas hello"};
	//消息是发给 app1， app1 也只是一个数字
	if(!msgQ_send(app, msg))
	{
		printf("send OK !\n");
	}
	else
		printf("send KO ! \n");
	
}
void app_init(void)
{
	//thread的创建维护了一个数组，这个app的值是当做索引
	app_t app=APP1;
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
	//根据索引值去执行对应的函数
	app_t app=APP1;
	
	msg_init();
	
	app_init();
	run(app,FALSE);
	return 0;
}
