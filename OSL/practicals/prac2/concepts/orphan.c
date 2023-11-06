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
		//	sleeping the child process to make it an orphan
		sleep(10);
		printf("\nThis is a child process...\n");
		printf("\nMy process Id is : %d\n", getpid());
		printf("\nMy parent process Id is : %d\n", getppid());
		system("ps");
	}
	else 
	{
		sleep(2);
		printf("\nThis is a parent process...\n");
		printf("\nMy process Id is : %d\n", getpid());
		printf("\nMy child process Id is : %d\n", p);
		system("ps");
	}
		
	return 0;
}
