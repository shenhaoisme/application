/*
#include <unistd.h>

       int daemon(int nochdir, int noclose);


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
	
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
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