#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>

#include <stdbool.h>

int allocationMatrix[100][100], remainingNeed[100][100], maximumDemands[100][100], availableResources[100];
bool isProcessFinished[100];
int safeSequence[100];

int numProcess, numResources;

//	checking if the system is safe or not
void isSystemSafe()
{
	int i, j, work[100], count = 0;
	
	//	copy all available resources in work matrix
	for(i = 0; i < numResources; i++)
	{
		work[i] = availableResources[i];
	}
	
	//	initializing the process finished array
	for(i = 0; i < 100; i++)
	{
		isProcessFinished[i] = false;
	}
	
	while(count < numProcess)
	{
		bool canAllocate = false;
		for(i = 0; i < numProcess; i++)
		{
			if(isProcessFinished[i] == false)
			{
				for(j = 0; j < numResources; j++)
				{
					if(work[j] < remainingNeed[i][j])
						break;
				}
				
				if(j == numResources)
				{
					for(j = 0; j < numResources; j++)
					{
						work[j] += allocationMatrix[i][j];
					}
					
					//	add to the safe sequence
					safeSequence[count++] = i;
					
					//	set the process finished to true
					isProcessFinished[i] = false;
					canAllocate = true;
				}
			}
		}
		
		if(canAllocate == false)
		{
			printf("\nSystem is not safe...\n");
			return;
		}
		
	}
	
	printf("\nSystem is in an process state...\n");
	printf("Safe sequence : ");
	for(int i = 0; i < numProcess; i++)
	{
		printf(" -> %d", safeSequence[i]);
	}
	
	printf("\n");
	
}


//	calculating the need matrix
void needMatrix()
{
	for(int i = 0; i < numProcess; i++)
		for(int j = 0; j < numResources; j++)
			remainingNeed[i][j] = maximumDemands[i][j] - allocationMatrix[i][j];
}


int main()
{
	int i;
	int processIndex, resourceRequest[100];
	printf("\nEnter the number of processes :- ");
	scanf("%d", &numProcess);
	printf("\nEnter the number of resources :- ");
	scanf("%d", &numResources);
	
	printf("\nEnter the available resources:\n");
	for(int i = 0; i < numResources; i++)
		scanf("%d", &availableResources[i]);
	
	
	printf("\nEnter the resource allocation matrix :\n");
	for(int i = 0; i < numProcess; i++)
	{
		printf("Enter the allocation matrix for process %d : ", i+1);
		for(int j = 0; j < numResources; j++)
		{
			scanf("%d", &allocationMatrix[i][j]);
		}		
	}
	
	printf("\nEnter the matrix for maximum demand of each process :\n");
	for(int i = 0; i < numProcess; i++)
	{
		printf("Enter the demand matrix for process %d :- ", i+1);
		for(int j = 0; j < numResources; j++)
		{
		
			scanf("%d", &maximumDemands[i][j]);
		}
	}
			
			
	needMatrix();
		
	while(true)
	{
		int choice;
		printf("\n\n--------------- Welcome to the Banker's Algorithm ----------------\n\n");
		printf("1) Calculate Need Matrix\n");
		printf("2) Check Safety\n");
		printf("3) Request Resource\n");
		printf("4) Exit\n");
		printf("Enter your choice :-	");
		scanf("%d", &choice);
		
		if(choice == 4) 
		{
			printf("\nThanks for using the system...\n\n");
			break;				
		}
		
		switch(choice)
		{
			case 1:
				needMatrix();
				break;
				
			case 2:
				isSystemSafe();
				break;
				
			case 3:
				printf("\nEnter the process number for resource request : ");
				scanf("%d", &processIndex);
				
				printf("\nEnter the resource request matrix :\n");
				for(i = 0; i < numResources; i++)
					scanf("%d", &resourceRequest[i]);

				for(i = 0; i < numResources; i++)
				{
					if(remainingNeed[processIndex][i] < resourceRequest[i] || resourceRequest[i] > availableResources[i])
					{
						printf("\nCannot request\n");
						break;
					}
				}				
					
				if( i == numResources )
				{
					for(i = 0; i < numResources; i++)
					{
					
						allocationMatrix[processIndex][i] += resourceRequest[i];
						availableResources[i] -= resourceRequest[i];
						remainingNeed[processIndex][i] -= resourceRequest[i];
						
					}
					isSystemSafe();
				}
					
			default:
				printf("\nInvalid choice... please try again\n\n");
				break;	
		}
		
	}
	
	return 0;
}
