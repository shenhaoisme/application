#include <stdio.h>
#include <string.h>
#include <unistd.h>


//usage : ./pExecve /bin/echo
int main(int ac, char* av[])
{
	char python_path[]={"/usr/bin/python"};
	char * avec[]={"python","/home/pi/pad4pi/rpi_gpio_demo.py", NULL};
	char *env[] = {(char*)0}; //自己做了一个 环境变量值	
	execve(python_path, avec, env);
	return 0;
}