#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t p;
	p = fork();
	
	
	if(p == 0)
	{
		printf("\nThis is a child process...\n");
		printf("\nProcess Id is : %d\n", getpid());
		printf("\nMy parent process Id is : %d\n", getppid());
		
		//	used for checking the CURRENTLY ACTIVE PROCESS in the provess table
		system("ps");
	}
	else
	{
		sleep(10);
		printf("\nThis is a parent...\n");
		printf("\nProcess Id is : %d\n", getpid());
		printf("\nMy child process Id is : %d\n", p);
		
		//	used for checking the CURRENTLY ACTIVE PROCESS in the provess table
		system("ps");
	}
	
	return 0;
}
