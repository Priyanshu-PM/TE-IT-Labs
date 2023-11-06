#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n)
{
	int temp, i, j;
	for(i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

void printArray(int arr[], int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n");
}

int main()
{
	int n;
	printf("\nEnter the size of the array: ");
	scanf("%d", &n);
	
	int arr[n];
	printf("Enter %d elements : \n", n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	pid_t p;
	p = fork();
	
	if(p == 0)
	{
		printf("\n");
		sleep(5);
		printf("\nI am a child...");
		printf("\nMy process Id is : %d", getpid());
		printf("\nMy parent process Id is : %d", getppid());
		printf("\n");
		
		printf("\nArray before sorting in child process : \n");
		printArray(arr, n);
		printf("\nArray after sorting in child process is : \n");
		bubbleSort(arr, n);
		printArray(arr, n);
		system("ps");
		
	}
	else 
	{
		printf("\n");
		sleep(3);
		printf("\nI am a parent process");
		printf("\nMy process Id is : %d", getpid());
		printf("\n");
		
		printf("\nArray before sorting in child process : \n");
		printArray(arr, n);
		printf("Array after sorting in parent process is : \n");
		bubbleSort(arr, n);
		printArray(arr, n);
		system("ps"); 
	
	}
	
	return 0;
}
