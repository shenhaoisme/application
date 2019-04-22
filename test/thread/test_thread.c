#include <stdio.h>
#include<pthread.h>
#include <stdlib.h>

//int pthread_create(pthread_t *restrict tidp,const pthread_attr_t *restrict_attr,void*（*start_rtn)(void*),void *restrict arg);
/**
　 第一个参数为指向线程标识符的指针。

　　第二个参数用来设置线程属性。

　　第三个参数是线程运行函数的地址。

　　最后一个参数是运行函数的参数。
*/

struct member
{
	int num;
	char *name;
};

// callback
static void * callback(void* arg)  //can input one arg
{
	struct member *temp;
	
	printf("thread start !!");
	
	sleep(1);
	temp= (struct member*) arg;
	printf("num is %d", temp->num);
	printf("name is %s", temp->name);
	
	return NULL;
}

int test(void)
{
	pthread_t tid_p;
	struct member *m;
	m=(struct member*) malloc(sizeof(struct member)); //create a var
	
	m->num=25;
	m->name="shenhao";
	
	if(pthread_create(&tid_p, NULL, callback, (void*)m) == -1)
	{
		printf("creat fail\n");
		return -1;
	}
	sleep(1);
	
	if(pthread_join(tid_p, NULL)) //wait the thread exit 
	{
		printf("thread is not exit...\n");
		return -2;
	}
	return 0;
}

int main()
{
	test();
}