#include <stdio.h>
#include "max.h"


int main(){
	int a=1;
	int b=2;
	if(max(a,b))
	{
		printf("a > b\n");
	}
	else
	{
		printf("a < b\n");
	}
	return 0;
}
