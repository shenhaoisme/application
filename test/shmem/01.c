# include <stdio.h>
#include <stdlib.h>
# include <string.h>

//for O_WRONLY
# include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
# include <unistd.h>

//for share memory
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
/*
共享内存是为了两个进程间的通讯。
程序原意：通过给程序传参，parma 1是 shmid， parm 2 是读写
因为程序是分两次执行，共享内存是一个独立的存在，每次执行都会把这块内存
和程序关联起来，分两次执行，相当于俩个独立的程序去控制 share memory 

但问题： 当我直接传一个值当作shmid是，shmat去添加这块share memory会失败，
也好理解，因为shmget才会分配空间。并返回shmid。所以不明白例子是怎么成功的。
分两次执行也不存在意义. 所以会提供读还是写的选项给用户！


*/


int main(int argc, char * args[])
{
	 //
	int shmid=0;
	char* shm_buf = (void *)0;
	char ret;
	char ret_SHM[10];
	puts("do you want to write ot read\n\
if you want to write, please input 'w'\n\
if you want to read,please input 'r'\n");
	scanf("%c",&ret);
	if(ret == 'w')
	{
		shmid = shmget((key_t)0, 1024, 0666|IPC_CREAT);
		if(shmid == -1){
		 fprintf(stderr,"shmget failed\n");
		 exit(-1);
		}
		printf("%d\n", shmid); 
		//attaches  the System V shared memory segment identified by shmid to the address space of the calling process.  
		shm_buf= shmat(shmid, 0 ,0);
		if(shm_buf == (void *)-1){ //error occurs
			fprintf(stderr,"shmat failed\n");
			exit(-1);
		}
		scanf("%s", shm_buf);
	}
	else
	{	
		system("ipcs -m");
		puts("which memory do you want? please input shmid\n");
		scanf("%s",ret_SHM);
		shmid= atoi(ret_SHM);
		shm_buf= shmat(shmid, 0 ,0);
		printf("%s\n",shm_buf);
	}
	//de-attach
	shmdt(shm_buf);
	return 0;
	
}	
