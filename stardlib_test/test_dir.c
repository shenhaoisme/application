# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h> //for malloc function

/*
@note
 struct dirent {
               ino_t          d_ino;       // Inode number 
               off_t          d_off;       // Not an offset; see below 
               unsigned short d_reclen;    // Length of this record 
               unsigned char  d_type;      // Type of file; not supported
                                              by all filesystem types 
               char           d_name[256]; // Null-terminated filename 
           };
		   定义：strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。
		   如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。
char *strstr (const char *s1, const char *s2);

Parameters:
s1: This is the main string to be examined.
s2: This is the sub-string to be searched in s1 string.
 */

#define FILENAME "shenhao"
#define SUFFIX ".c"




void* get(const char * dir)
{
	DIR * fdir;
	struct dirent *entry;
	int count;
	if (! (fdir = opendir(dir)))
		return NULL;
	//成功则返回下个目录进入点. 有错误发生或读取到目录文件尾则返回NULL.
	//以我的感觉就是把所有的文件罗列出来
	while (NULL != (entry = readdir(fdir))){
		if((entry->d_type != DT_DIR) && (entry->d_type != DT_FIFO) && entry->d_type != DT_SOCK){
			//以文件为单位，每次都输出一个文件名
			//以会缀为过滤方式
			char *p = strstr(entry->d_name, SUFFIX);
			//if OK, such as .c 		
			if((p) && (strlen(p) == strlen(SUFFIX))){
				int len = p - entry->d_name;//把后缀去掉
				char * content = malloc(len + 1);
				strncpy(content, entry->d_name, len);
				//拿到想要的内容
				printf("%s\n",content);
			}
			
			
		}
	}
	closedir(fdir);
	
}

int main()
{
	const char * dir = "/home/pi/application/stardlib_test";
	get(dir);
	return 0;
}

