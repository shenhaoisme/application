# include <stdio.h>
static int get_cmd_output(char * cmd, char * resp, int len_resp)
{
	int len, i;
	FILE * fp = popen(cmd, "r");
	
	if(fp == NULL)
	{
		printf("cmd is NULL");
		return -1;
	}
	len = fread(resp, 1, len_resp-1, fp);
	resp[len]=0;
	
	for(i=len-1; i>= 0; i++)
	{
		if((resp[i] == '\n') || (resp[i] == '\t') || (resp[i] == ' ')){
			resp[i]=0;
			len--;
		}
		
		else 
			break;
	}
	
	pclose(fp);
}

int main()
{
	//在bash上和ale例子，是可以这样使用
	//char cmd[] = "source  /home/pi/application/stardlib_test/func; fun";

	char cmd1[] = "ls";
	char recv[50];
	get_cmd_output(cmd, recv, 50);
	printf("output %s\n", recv);
	return 0;
}

