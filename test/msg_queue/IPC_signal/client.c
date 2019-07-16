#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// 消息队列形式
struct msg_form {
    long mtype;
    char mtext;
};

// 信号量结构体
union semun
{
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};
//全局变量
struct sembuf first;
struct sembuf second;

// P操作
int sem_p(int sem_id, struct sembuf *buf)
{
    struct sembuf sbuf;
    //sbuf.sem_num =  buf->sem_num; /*信号量序号*/
    sbuf.sem_op = -1; /*P操作标志*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)// 对信号量进行操作
    {
        perror("P operation Error");
        return -1;
    }
	
    return 0;
}
// V操作
int sem_v(int sem_id,struct sembuf *buf)
{
    struct sembuf sbuf;
    //sbuf.sem_num = buf->sem_num; //序号
    sbuf.sem_op = 1;  /*V操作标志*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)// 对信号量进行操作
    {
        perror("V operation Error");
        return -1;
    }
    return 0;
}
int main()
{
	key_t key;
	int shmid, semid, msqid;
	char *shm;
	struct msg_form msg;
	int flag = 1; /*while 标签*/
	
	first.sem_num = 0; //semaphore 1
	second.sem_num = 1; //semphore 2 

	// 创建key值
	if((key = ftok(".", 'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// 获取一个共享内存
	if((shmid = shmget(key, 1024, 0)) == -1)
	{
		perror("shmget error");
		exit(1);
	}

	// 返回值：如果成功，返回共享存储段地址，出错返回-1
	shm = (char*)shmat(shmid, 0, 0);
	if(atoi(shm) == -1)
	{
		perror("Attach Shared Memory Error");
		exit(1);
	}

	// 消息队列获取
	if ((msqid = msgget(key, 0)) == -1)
	{
		perror("msgget error");
		exit(1);
	}
	

	// 信号量获取
	semid=semget(key,0,IPC_CREAT|0660);
	if(semid == -1)
	{
		perror("semget error");
		exit(1);
	}
	union semun sem_args;
    unsigned short array[2]={1,1};
	sem_args.array = array;
	if(semctl(semid, 1, SETALL, sem_args) == -1)
	{
		perror("semctl error");
		exit(1);
	}
	// 打印消息
	printf("***************************************\n");
	printf("*                 IPC                 *\n");
	printf("*    Input r to send data to server.  *\n");
	printf("*    Input q to quit.                 *\n");
	printf("***************************************\n");
	
	while(flag)
	{
		char c;
		printf("Please input command: ");
		c = getchar();
		switch(c)
		{
			case 'r':
				
				printf("Data to send: ");
				sem_p(semid,&first);  /*p -1*/
				scanf("%s", shm);
				sem_v(semid,&first);  /*v*/
				//printf("second input"); 
				sem_p(semid,&second);  /*p -1*/
				//目的是为了测试两个sem，但是进行两次写入会覆盖上一次操作
				//scanf("%s", shm);
				sem_v(semid,&second);  /*v*/				
				while((c=getchar())!='\n' && c!=EOF);
				msg.mtype = 888;  
				msg.mtext = 'r';  /*发送消息*/
				msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
				
				
				break;
			case 'q':
				msg.mtype = 888;
				msg.mtext = 'q';
				msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
				flag = 0;
				break;
			default:
				printf("Wrong input!\n");
				while((c=getchar())!='\n' && c!=EOF);
		}
	}

	// 删除共享内存
	shmdt(shm);

	return 0;
}
