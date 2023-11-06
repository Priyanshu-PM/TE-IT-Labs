#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>


void bubbleSort(int arr[], int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n - i - 1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

void printArray(int arr[], int n)
{
	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
		
	printf("\n");
}

int main()
{
	
	int i, a[15], n, key;
	char *arg[10], str[15], *str2;
	
	pid_t parent_id, child_id, id;
	printf("\nEnter the size of the input array : ");
	scanf("%d", &n);
	printf("\nEnter the elements of the input array : \n");
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	parent_id = getpid();
	printf("\nIn parent process ID --> %d\n", parent_id);
	printf("\nSorting numbers...\n");
	bubbleSort(a, n);
	
	id = fork();
	if(id == 0)
	{
		child_id = getpid();
		printf("\nIn child process ID --> %d\n", child_id);
		printf("\n\nThe sorted numbers are : \n");
		printArray(a, n);
		for(i = 0; i < n; i++)
		{
			//	storing the data in the string buffer
			sprintf(str, "%d", a[i]);
			arg[i] = malloc(sizeof(str));
			
			//	copying the str into arg[i]
			strcpy(arg[i], str);
		}
		
		arg[i] = NULL;
		printf("\n\nExecuting the EXECVE statement\n");
		execve("./2b2", arg, NULL);
		printf("\nEXECVE completed\n");
		printf("\nChild complete. Now child Exists\n\n");
		
		
	}
	else if(id > 0)
	{
		printf("\nIn parent process\n\nNow waiting\n\n");
		wait(NULL);
		printf("\n\nParent Complete. Now Parent Exists\n\n");
	}
	
	
	return 0;
}
