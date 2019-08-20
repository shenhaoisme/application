/*
Y:\80x8ee\hg\8018_application\application\noemmi\NOE\noe_shared\mod\noeos
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#define IPC_QUEUE_NOEMMI            0x11111111


//msgget(得到消息队列标识符或创建一个消息队列对象)
//int msgget(key_t key, int msgflg)
//key 0(IPC_PRIVATE)会建立新的消息队列
//大于0的32位整数：视参数msgflg来确定操作。通常要求此值来源于ftok返回的IPC键值
/*0：取消息队列标识符，若不存在则函数会报错

IPC_CREAT：当msgflg&IPC_CREAT为真时，如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列，返回此消息队列的标识符

IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列则报错
*/
static int msgid=-1;
struct my_text
{
		long type;
		char mtext[20];
};

int msg_test_init(void)
{
	msgid = msgget(0, 0666);
	if (msgid < 0) {
           printf( "Message Queue creation failed" );
           return -1;
    }
	
    return 0;
	
}
 
void msg_test_term(void)
{
	 if (-1 != msgid)
    {
        if ( 0 != msgctl(msgid, IPC_RMID, NULL) )
        {
            printf("message queue delete failed" );
        }
        msgid = -1;
    }
	msgid = 0;
	msgid = 0;
    return;
}
/*
int msgsnd ( int msqid, struct msgbuf *msgp, int msgsz, int msgflg )
返回值： 0 on success
第一个参数msqid 是消息队列对象的标识符（由msgget()函数得
第二个参数msgp 指向要发送的消息所在的内存
第三个参数msgsz 是要发送信息的
长度（字节数），可以用以下的公式计算：
msgsz = sizeof(struct mymsgbuf) - sizeof(long);
*/
int msg_send()
{
	int flag=-1;
	int sendlen=0;
	
	struct my_text msgp;
	msgp.type = 3;
	//msgp.mtext = "shenhao : hello world";
	strcpy(msgp.mtext, "shenhao : hello world");
	sendlen = sizeof(struct my_text) - sizeof(long); // 256 * char 
	flag = msgsnd(msgid, (struct msgbuf*)&msgp, sendlen, 0);
	 if ( flag < 0 )
    {
        perror("send message error") ;
        return -1 ;
    } 
	
}
int msg_test_ctl(void)
{
	int flag=-1;
	struct msqid_ds info;
	flag = msgctl( msgid, IPC_STAT, &info ) ;
	if (flag < 0 )
	{
    	perror("get message status error") ;
    	return -1 ;
	}
	printf("uid:%d, gid = %d, cuid = %d, cgid= %d\n",info.msg_perm.uid,
			info.msg_perm.gid,info.msg_perm.cuid,info.msg_perm.cgid);
       	printf("read-write:%03o, cbytes = %lu, qnum = %lu, qbytes= %lu\n" ,
			info.msg_perm.mode&0777, info.msg_cbytes, info.msg_qnum, info.msg_qbytes ) ;
	system("ipcs -q");
	//recvlength = sizeof(struct msgbuf)-sizeof(long);
	//memset(&msgp, 0x00, sizeof(struct msgbuf));

}

int msg_test_recv()
{
	int flag=-1;
	struct my_text rev_buf;
	int rev_len = sizeof(struct my_text) - sizeof(long); // 256 * char 
	memset(&rev_buf, 0, sizeof(struct my_text));
	
	
	flag = msgrcv(msgid, &rev_buf,rev_len, 3, 0); //
	if ( flag < 0 )
	{
		perror("receive error \n");
		return -1;
	}
	printf("type is %ld, message is %s\n", rev_buf.type, rev_buf.mtext);
	flag = msgctl(msgid, IPC_RMID, NULL);
	if(flag < 0)
	{
		perror("rm message queue error\n");
		return -1;
	}
	system("ipcs -q");
	return 0;
}

int main(int argc, char *argv[])
{
	msg_test_init();
	msg_send();
	msg_test_ctl();
	
	msg_test_recv();
	msg_test_term();
	return 0;
}
