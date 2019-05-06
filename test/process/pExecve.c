/*
该程序为新程序创建参数列表和环境列表，接着call execve 来执行命令行参数， av[1] 指定程序的路径名
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int ac, char* av[])
{
	char * avec[10];
	char *env[] = {"S=shen", "H=hao",NULL}; //自己做了一个 环境变量值
	
	if(ac != 2 || strcmp(av[1], "--help") == 0 ) //必须带一个参数
		printf("%s pathname", av[0]);
	avec[0] = strrchr(av[1], '/'); //应该是定位到最后一个 / .
	
	if(avec[0] != NULL)
		avec[0]++;
	else
		avec[0] = av[1];
	
	avec[1] = "hello";  //将要传递给
	avec[2] = "world";
	avec[3] = NULL;
	
	execve(av[1], avec, env);
	return 0;
}

int main1(int arg, char **args)
{
    char *argv[]={"ls","-al","/home/sh/share", NULL};

    char *envp[]={0,NULL}; //传递给执行文件新的环境变量数组

    execve("/bin/ls",argv,envp);

}

