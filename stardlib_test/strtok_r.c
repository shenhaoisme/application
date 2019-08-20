#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
使用了嵌套循环，用strtok_r 将字符串分为两级结构

 An example of the output produced by this program is the following:

           $ ./a.out 'a/bbb///cc;xxx:yyy:' ':;' '/'
           1: a/bbb///cc
                    --> a
                    --> bbb
                    --> cc
           2: xxx
                    --> xxx
           3: yyy
                    --> yyy
					
					
@param1	要分割字符串
@param2 第一层分割的条件是 :;
@param3 第二层分割的条件是  /   （从例子中可以发现。重复/ 当作一个，也肯呢个分割出的是 null 没法显示）

过程：
step1 a/bbb///cc;xxx:yyy:  ==> 返回值是:"a/bbb///cc". saveptr1 是 xxx:yyy: （字符串的后半段）
	然后进入内圈循环
		a/bbb///cc (对该字符串进行 “/” 分割)
		返回值分别是  	a 			bbb 		cc
		saveptr2 分别是 bbb///cc 	cc 			为空
		
step2 返回值 xxx saveptr1 yyy: (1 指的是第一层循环)
	然后进入内圈循环
		返回值分别是  	xxx
		saveptr2		为空

step3 yyy参考xxx

char *strtok_r(char *str, const char *delim, char **saveptr);


*/
int
main(int argc, char *argv[])
{
	char *str1, *str2, *token, *subtoken;
	char *saveptr1, *saveptr2;
	int j;

	if (argc != 4) {
	   fprintf(stderr, "Usage: %s string delim subdelim\n",
			   argv[0]);
	   exit(EXIT_FAILURE);
	}

	for (j = 1, str1 = argv[1]; ; j++, str1 = NULL) {
	   token = strtok_r(str1, argv[2], &saveptr1);
	   if (token == NULL)
		   break;
	   printf("%d: %s\n", j, token);
	   printf("saveptr1 %s\n", saveptr1);

	   for (str2 = token; ; str2 = NULL) {
		   subtoken = strtok_r(str2, argv[3], &saveptr2);
		   if (subtoken == NULL)
			   break;
		   printf(" --> %s\n", subtoken);
		   printf("saveptr2 %s\n", saveptr2);
		   
	   }
	}

	exit(EXIT_SUCCESS);
}
