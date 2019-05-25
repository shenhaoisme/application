/*
#include <unistd.h>
int daemon(int nochdir, int noclose)；
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <syslog.h>

#include <stdlib.h> //for exit

int init_daemon()
{
	pid_t pid, sid;
	int i;
	/*Unix环境下，当一个进程以后台形式启动，但尝试去读写控制台终端时，
	将会触发SIGTTIN（读）和SIGTTOU（写）信号量，接着，进程将会暂停（linux默认情况下），
	read/write将会返回错误。这个时候，shell将会发送通知给用户，提醒用户切换此进程为前台进程，
	以便继续执行。由后台切换至前台的方式是fg命令，前台转为后台则为CTRL+Z快捷键。*/
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	/* SIGTSTP与SIGSTOP都是使进程暂停（都使用SIGCONT让进程重新激活）。唯一的区别是SIGSTOP不可以捕获和忽略。

捕捉SIGTSTP后一般处理如下：

1）处理完额外的事

2）恢复默认处理

3）发送SIGTSTP信号给自己。（使进程进入suspend状态。）
	*/
	signal(SIGTSTP,SIG_IGN);
	/*　1、终端关闭时，该信号被发送到session首进程以及作为job提交的进程（即用 & 符号提交的进程）； 
　　		2、session首进程退出时，该信号被发送到该session中的前台进程组中的每一个进程； 
　　 	3、若父进程退出导致进程组成为孤儿进程组，且该进程组中有进程处于停止状态（收到SIGSTOP或SIGTSTP信号），该信号会被发送到该进程组中的每一个进程
	而且默认处理方式是终止当前程序
---*/
	signal(SIGHUP,SIG_IGN);
	
	pid = fork();
	if (pid >0)
		exit(0);
	else if(pid < 0)
		exit(-1);
	
	sid = setsid(); //become to a top of session 
	
	pid=fork();
	if (pid >0)
		exit(0);
	else if(pid < 0)
		exit(-1);

	for (i=0;i<NOFILE; close (i++));
	
	//chdir('/');
	
	umask(0);
	signal(SIGCHLD,SIG_IGN); 
	
	return 0;		
}

int main()
{
	time_t now;
	//init_daemon();
	
	daemon(0,0);
	syslog(LOG_USER|LOG_INFO,"TestDaemonProcess! \n");
	while(1) { 
		sleep(8);
		time(&now); 
		syslog(LOG_USER|LOG_INFO,"SystemTime: \t%s\t\t\n",ctime(&now));
	} 
}