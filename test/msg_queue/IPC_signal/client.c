#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// ��Ϣ������ʽ
struct msg_form {
    long mtype;
    char mtext;
};

// �ź����ṹ��
union semun
{
    int              val; /*for SETVAL*/
    struct semid_ds *buf;
    unsigned short  *array;
};
//ȫ�ֱ���
struct sembuf first;
struct sembuf second;

// P����
int sem_p(int sem_id, struct sembuf *buf)
{
    struct sembuf sbuf;
    //sbuf.sem_num =  buf->sem_num; /*�ź������*/
    sbuf.sem_op = -1; /*P������־*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)// ���ź������в���
    {
        perror("P operation Error");
        return -1;
    }
	
    return 0;
}
// V����
int sem_v(int sem_id,struct sembuf *buf)
{
    struct sembuf sbuf;
    //sbuf.sem_num = buf->sem_num; //���
    sbuf.sem_op = 1;  /*V������־*/
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sbuf, 1) == -1)// ���ź������в���
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
	int flag = 1; /*while ��ǩ*/
	
	first.sem_num = 0; //semaphore 1
	second.sem_num = 1; //semphore 2 

	// ����keyֵ
	if((key = ftok(".", 'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// ��ȡһ�������ڴ�
	if((shmid = shmget(key, 1024, 0)) == -1)
	{
		perror("shmget error");
		exit(1);
	}

	// ����ֵ������ɹ������ع���洢�ε�ַ��������-1
	shm = (char*)shmat(shmid, 0, 0);
	if(atoi(shm) == -1)
	{
		perror("Attach Shared Memory Error");
		exit(1);
	}

	// ��Ϣ���л�ȡ
	if ((msqid = msgget(key, 0)) == -1)
	{
		perror("msgget error");
		exit(1);
	}
	

	// �ź�����ȡ
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
	// ��ӡ��Ϣ
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
				//Ŀ����Ϊ�˲�������sem�����ǽ�������д��Ḳ����һ�β���
				//scanf("%s", shm);
				sem_v(semid,&second);  /*v*/				
				while((c=getchar())!='\n' && c!=EOF);
				msg.mtype = 888;  
				msg.mtext = 'r';  /*������Ϣ*/
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

	// ɾ�������ڴ�
	shmdt(shm);

	return 0;
}
