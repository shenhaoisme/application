#include <stdio.h>


extern char ** environ;
int 
main(int ac, char* av[])
{
	int j;
	char ** ep;
	for(j=0; j< ac ; j++)
	{
		printf("av[%d], = %s \n",j, av[j] );
	}
	
	for(ep = environ; *ep != NULL ; *ep ++)
	{
		printf("environ %s\n", *ep);
	}
	return 0;
}