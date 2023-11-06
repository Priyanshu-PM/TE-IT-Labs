#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t p;
	p = fork();
	
	if(p == 0)
	{
		printf("\nI am a child process...\n");
		printf("\nMy process Id is : %d\n", getpid());
	}
	else 
	{
		printf("\nI am a parent process \n");
		printf("\nMy process Id is : %d\n", getpid());
	}
	
	return 0;
}
