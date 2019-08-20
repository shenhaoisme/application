# include <string.h>
#include <stdio.h>


/**
网上的例子都是错误， core dump， 既然linux都推荐用 strtok_r 代替 strtok。先不管这个啦


char *strtok(char s[], const char *delim);
该函数返回被分解的第一个子字符串，如果没有可检索的字符串，则返回一个空指针。3


（1）当strtok()在参数s的字符串中发现参数delim中包含的分割字符时,则会将该字符改为\0 字符。
在第一次调用时，strtok()必需给予参数s字符串，往后的调用则将参数s设置成NULL。每次调用成功则返回指向被分割出片段的指针。
（2）返回值
从s开头开始的一个个被分割的串。当s中的字符查找到末尾时，返回NULL。
如果查找不到delim中的字符时，返回当前strtok的字符串的指针。所有delim中包含的字符都会被滤掉，并将被滤掉的地方设为一处分割的节点。



*/
void test_strtok(void)
{
	int in=0;
	int i = 0;
	char buf[] = "Fred，John，Ann";
	char *tmp;
	char *p[3];

	char * pBuf = buf;
	
	// while ((p[in] = strtok(pBuf, ",")) != NULL)
	// {
		// //pBuf = p[in];
		// //p[in] = pBuf;
		// /*while (p[in] = strtok(pBuf, " ") != NULL)
		// {
			// in ++;
			// pBuf = NULL;
		// } */

		// //p[in++] = "***";
		// pBuf = NULL;
		// in++;
	// }
	
	tmp = strtok(pBuf, ",");
	p[in] = tmp;
	if(tmp != NULL)
	{
		tmp = strtok(NULL, ",");
		in++;
		printf("我们分了%d 个字符串\n", in);
	}
	
	p[in] = tmp;
	

	printf("我们分了%d 个字符串\n", in);
	for(i = 0 ; i <= in ; i++)
	{
		if(p[i] != NULL)
			printf("%d, %s\n",i, p[i]);
	}
}






int main()
{
//strtok可以根据用户所提供的分割符(同时分隔符也可以为复数比如",。")
	//将一段字符串分割直到遇到"\0".
//比如，分隔符=“，” 字符串 “Fred，John，Ann”
//通过strtok 就可以把3个字符串 “Fred”      “John”       “Ann”提取出来。

	
	test_strtok();
	return 0;
}
