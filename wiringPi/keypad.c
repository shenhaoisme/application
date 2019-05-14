#include <wiringPi.h>
#include <stdio.h>
//#define TRUE 1
//#define FALSE 0

int keypadIs4x4=TRUE;
char ret_key =' ';
char keypad4x3[4][3] = {
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
};
	
char keypad4x4[4][4] = {
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'}
	
};
void _getkey(void);

static int ROW_PINS[4] = {25,28,29,0};
static int COL_PINS[4]= {1,2,3,4};
void func(void)
{}
int createKeypad(int row, int col, int time_out)
{	
	int i,j;
	keypadIs4x4 = TRUE;
	if(col == 3) 
	{
		keypadIs4x4 = FALSE;
		COL_PINS[3] =-1;
	}
	
	for(i=0; i< row; i++)
	{
		pinMode(ROW_PINS[i], INPUT);
		pullUpDnControl(ROW_PINS[i], PUD_UP);
		//setup ISR 
		wiringPiISR(ROW_PINS[i], INT_EDGE_FALLING, &_getkey);
	}
	for(j=0; j< col; j++)
	{
		if(COL_PINS[j] == -1)
			continue;
		pinMode(COL_PINS[j],OUTPUT);
		digitalWrite(COL_PINS[j],LOW);
	}
	
	return 0;
}
void _getkey(void)
{
	int i,j;
	int tempret;
	int row=-1,col=-1;
	char key;
	for(i=0;i<4;i++)
	{
		tempret = digitalRead(ROW_PINS[i]) ;
		
		if(tempret == LOW)
		{
			row=i;
			
			break;
		}
	}
	if(row == -1) 
		return;
	for(j=0;j<4;j++)
	{
		digitalWrite(COL_PINS[j], HIGH);//roolback
		delayMicroseconds(10);
		if(digitalRead(ROW_PINS[row])==HIGH)
		{
			digitalWrite(COL_PINS[j],LOW);
			col=j;
			delayMicroseconds(1000);
			break;
		}
		
	}
	if(col == -1) 
		return;
	if(keypadIs4x4 == FALSE)
		ret_key = keypad4x3[row][col];
	else
		ret_key = keypad4x4[row][col];
	printf("\n%c\n",ret_key);
	fflush (stdout) ;
	row=col=-1;
	ret_key=' ';
	
	return;
}
void waitIRC(void)
{
	if(ret_key != ' ' )
	{
		printf("\n%c\n",ret_key);
		ret_key=' ';
	}
}
int main(int ac, char* av[])
{
	wiringPiSetup();
	createKeypad(4,4, 10);
	while(1);
		//waitIRC();
	return 0;
}
