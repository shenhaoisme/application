# include <stdio.h>
#include <stdlib.h>
# include <string.h>

//for O_WRONLY
# include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//for access 判断文件是否存在
//#include <io.h>
# include <unistd.h>	
	
/*
pipefile created by two method:
1 shell commamd mkfifo name
2 c function
{
	#include <sys/types.h>
	#include <sys/stat.h>
	int mkfifo(const char *pathname, mode_t mode);
}
	
note: 
 rm file(if in c func--> unlink)
 {
	 #include<unistd.h>
	 int unlink(const char *pathname);
 }

 fifo file 权限  664 
 
*/

int main()
{
	char buf[200];
	int exist = -1;
	memset(buf, 0, sizeof(buf));//make buf be empty
	
	//如果fifo1 存在，
	exist = access("fifo1", 0); //0 -> F_OK 判断文件是否存在
	if(exist == 0)
		printf("file exist, need't to create\n");
	else//创建 fifo file 
	{
		umask(0); //
		if (mkfifo ("fifo1", S_IFIFO | 0666) == -1) { 
			perror("mkfifo error!");
			exit(1);
		}
	}
	
	int fd = open("fifo1", O_WRONLY); //以只读的方式去打开这个文件
	while(1)
	{
	 read(STDIN_FILENO, buf, sizeof(buf));//从标准出入读取内容
	 if (buf[0] == '0') //如果收到字符 0 ，表示输入结束
		 break;
	 write(fd, buf, sizeof(buf)); //把读取到的内容，写到fifo file
	 
	 //再次清空buf，以免影响下次输入
	 memset(buf, 0, sizeof(buf));
	}
	close(fd); //关闭文件描述符
	return 0;
}