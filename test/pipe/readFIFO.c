# include <stdio.h>
# include <string.h>
# include <unistd.h>
//for O_WRONLY
# include <fcntl.h>

int main()
{	
	int len = 0;
	char buf[200];
	//我印象中buf 前面是要加 &
	memset(buf, 0, sizeof(buf));
	int fd = open("fifo1", O_RDONLY);

	while((len = read(fd, buf, sizeof(buf)))> 0)
	{//不清楚的是如果不加 '\n'，就会影响输出，当输入端输入0，应该输出的内容才会
//输出（闪一下就没了）
		printf("%s", buf);
		memset(buf, 0, sizeof(buf));
	}
		
	close(fd);
	return 0;
}