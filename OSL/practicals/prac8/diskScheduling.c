//	Disk Scheduling Algorithm


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calculateTotalSeekTimeFCFS(int initialHead, int requestQueue[], int size)
{
	int totalSeekTime = 0;
	
	printf("\nSeek sequence :- ");
	printf("-> %d ", initialHead);
	for(int i = 0; i < size; i++)
	{
		int seek = abs(initialHead - requestQueue[i]);
		printf("-> %d", requestQueue[i]); 
		initialHead = requestQueue[i];
		
		totalSeekTime += seek;
	}
	
	printf("\nTotal number of seek operations is : %d\n", totalSeekTime);
	float avgSeekTime = (float)(totalSeekTime) / size;
	printf("\nAverage Seek Time is : %f\n", avgSeekTime);
	
	return totalSeekTime;
}

int calculateTotalSeekTimeSSTF(int initialHead, int requestQueue[], int size)
{
	int totalSeekTime = 0;
	int currentPosition = initialHead;
	
	int visited[size];
	for(int i = 0; i < size; i++)
		visited[i] = 0;
	
	int seekSequence[size];
	for(int i = 0; i < size; i++)
		seekSequence[i] = -1;
	
	
	for(int i = 0; i < size; i++)
	{
		int shortestSeek = 999999;
		int nextRequest;
		for(int j = 0; j < size; j++)
		{
			if(!visited[j])
			{
				int seek = abs(currentPosition - requestQueue[j]);
				if(seek < shortestSeek)
				{
					shortestSeek = seek;
					nextRequest = j;
				}
				
			}
		}
		
		totalSeekTime += shortestSeek;
		visited[nextRequest] = 1;
		seekSequence[i] = requestQueue[nextRequest];
		currentPosition = requestQueue[nextRequest]; 
	}
	
	printf("\nSeek Sequence :- ");
	printf("%d ",initialHead);
	for(int i = 0; i < size; i++)
	{
		if(seekSequence[i] != -1)
			printf("-> %d ", seekSequence[i]);
	}
	
	printf("\nTotal number of seek operations is : %d\n", totalSeekTime);
	float avgSeekTime = (float)(totalSeekTime) / size;
	printf("\nAverage Seek Time is : %f\n", avgSeekTime);
	
	
	return totalSeekTime;
}


//	sorting the requests

void bubbleSort(int requestQueue[], int size)
{
	printf("\nInside the bubble sort...\n");
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size - i - 1; j++)
		{
			if(requestQueue[j] > requestQueue[j+1])
			{
				int temp = requestQueue[j];
				requestQueue[j] = requestQueue[j+1];
				requestQueue[j+1] = temp;
			}
		}
	
	}
}



//	don't include maximum and minimum ranges, then similar to SCAN
int calculateTotalSeekTimeLOOK(int requestQueue[], int size, int initialHead) 
{
	int totalSeekTime = 0;
	int headPosition = initialHead;

	//	sorting the requests
	bubbleSort(requestQueue, size);
	
	
	//	finding the greater index
	int startIndex = 0;
	for(int i = 0; i < size; i++)
	{
		if(requestQueue[i] > headPosition)
		{
			startIndex = i;
			break;
		}
	}
	
	printf("\n\nStart index is : %d\n", startIndex);
	
	int seekRight = abs(requestQueue[startIndex] - headPosition);
	int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
	
	
	printf("\nSeek LEFT := %d", seekLeft);
	printf("\nSeek RIGHT := %d", seekRight);
	
	int direction;
	printf("\n\n1) LEFT direction\n");
	printf("2) RIGHT direction\n");
	printf("Choose your direction := ");
	scanf("%d", &direction);
	
	if(direction == 1)
	{
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards left direct because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex - 1; i >= 0; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		totalSeekTime += abs(headPosition - requestQueue[startIndex]);
		headPosition = requestQueue[startIndex];
		printf("-> %d ", headPosition);
		
		for(int i = startIndex; i < size; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
	}
	else
	{
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards right direction because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex; i < size; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		totalSeekTime += abs(headPosition - requestQueue[startIndex-1]);
		headPosition = requestQueue[startIndex-1];
		printf("-> %d ", headPosition);
		
		for(int i = startIndex - 2; i >= 0; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
	}
	
	
	printf("\n\nTotal number of seek operations is : %d\n", totalSeekTime);
	float avgSeekTime = (float)(totalSeekTime) / size;
	printf("\nAverage Seek Time is : %f\n", avgSeekTime);
	
	
	return totalSeekTime;
	
}


//	don't include maximum and minimum ranges, then similar to C_SCAN
int calculateTotalSeekTimeC_LOOK(int requestQueue[], int size, int initialHead)
{
	int totalSeekTime = 0;
	int headPosition = initialHead;

	//	sorting the requests
	bubbleSort(requestQueue, size);
	
	
	//	finding the greater index
	int startIndex = 0;
	for(int i = 0; i < size; i++)
	{
		if(requestQueue[i] > headPosition)
		{
			startIndex = i;
			break;
		}
	}
	
	
	int seekRight = abs(requestQueue[startIndex] - headPosition);
	int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
	
	
	printf("\nSeek LEFT := %d", seekLeft);
	printf("\nSeek RIGHT := %d", seekRight);
	
	int direction;
	printf("\n\n1) LEFT direction\n");
	printf("2) RIGHT direction\n");
	printf("Choose your direction := ");
	scanf("%d", &direction);
	if(direction == 1)
	{
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards left direct because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex - 1; i >= 0; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		headPosition = requestQueue[size-1];
		printf("-> %d ", headPosition);
		
		for(int i = size-2; i >= startIndex; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
	}
	else
	{
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards right direction because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex; i < size; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		headPosition = requestQueue[0];
		printf("-> %d ", headPosition);
		
		//	shifting directly to the opposite side without head counts
		
		for(int i = 1; i < startIndex; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
	}
	
	
	printf("\n\nTotal number of seek operations is : %d\n", totalSeekTime);
	float avgSeekTime = (float)(totalSeekTime) / size;
	printf("\nAverage Seek Time is : %f\n", avgSeekTime);
	
	
	return totalSeekTime;
}

int calculateTotalSeekTimeSCAN(int requestQueue[], int size, int initialHead, int minRange, int maxRange)
{
	int totalSeekTime = 0;
	int headPosition = initialHead;

	//	sorting the requests
	bubbleSort(requestQueue, size);
	
	
	//	finding the greater index
	int startIndex = 0;
	for(int i = 0; i < size; i++)
	{
		if(requestQueue[i] > headPosition)
		{
			startIndex = i;
			break;
		}
	}
	
	
	int seekRight = abs(requestQueue[startIndex] - headPosition);
	int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
	
	
	printf("\nSeek LEFT := %d", seekLeft);
	printf("\nSeek RIGHT := %d", seekRight);
	
	int direction;
	printf("\n\n1) LEFT direction\n");
	printf("2) RIGHT direction\n");
	printf("Choose your direction := ");
	scanf("%d", &direction);
	
	if(direction == 1)
	{
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards left direct because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex - 1; i >= 0; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		totalSeekTime += abs(headPosition - minRange);
		headPosition = minRange;
		printf("-> %d ", headPosition);
		
		for(int i = startIndex; i < size; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		
		
	}
	else 
	{
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards right direction because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex; i < size; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		totalSeekTime += abs(maxRange - headPosition);
		headPosition = maxRange;
		printf("-> %d ", headPosition);
		
		for(int i = startIndex - 1; i >= 0; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		
	}
	

	printf("\n\nTotal number of seek operations is : %d\n", totalSeekTime);
	float avgSeekTime = (float)(totalSeekTime) / size;
	printf("\nAverage Seek Time is : %f\n", avgSeekTime);
	
	
	return totalSeekTime;
}

int calculateTotalSeekTimeC_SCAN(int requestQueue[], int size, int initialHead, int minRange, int maxRange)
{
	int totalSeekTime = 0;
	int headPosition = initialHead;
	
	//	sorting the requests
	bubbleSort(requestQueue, size);
	
	
	//	finding the greater index
	int startIndex = 0;
	for(int i = 0; i < size; i++)
	{
		if(requestQueue[i] > headPosition)
		{
			startIndex = i;
			break;
		}
	}
	
	
	int seekRight = abs(requestQueue[startIndex] - headPosition);
	int seekLeft = abs(requestQueue[startIndex - 1] - headPosition);
	
	printf("\nSeek LEFT := %d", seekLeft);
	printf("\nSeek RIGHT := %d", seekRight);
	
	int direction;
	printf("\n\n1) LEFT direction\n");
	printf("2) RIGHT direction\n");
	printf("Choose your direction := ");
	scanf("%d", &direction);
	
	if(direction == 1)
	{
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards left direct because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex - 1; i >= 0; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		totalSeekTime += abs(headPosition - minRange);
		
		headPosition = minRange;
		printf("-> %d ", headPosition);
		
		//	shifting directly to the opposite side without head counts
		headPosition = maxRange;
		printf("-> %d ", maxRange);
		
		for(int i = size - 1; i >= startIndex; i--)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		
	}
	else
	{
	
		printf("\n---------------------------------------------------------------------------------------------------------------------\n");
		printf("----------------------- Going towards right direction because the seek time is minimum over there --------------------------\n\n");
		printf("Seek sequence :=  %d ", initialHead);
		
		for(int i = startIndex; i < size; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		totalSeekTime += abs(maxRange - headPosition);
		headPosition = maxRange;
		printf("-> %d ", headPosition);
		
		//	shifting directly to the opposite ide without head counts
		headPosition = minRange;
		printf("-> %d ", headPosition);
		
		for(int i = 0; i < startIndex; i++)
		{
			totalSeekTime += abs(headPosition - requestQueue[i]);
			headPosition = requestQueue[i];
			printf("-> %d ", headPosition);
		}
		
		
	}
	
	printf("\n\nTotal number of seek operations is : %d\n", totalSeekTime);
	float avgSeekTime = (float)(totalSeekTime) / size;
	printf("\nAverage Seek Time is : %f\n", avgSeekTime);
	
	return totalSeekTime;
}


int main()
{
	int size, initialHead, minRange, maxRange, seekTime = 0;
	printf("\nEnter the number of requests : ");
	scanf("%d", &size);
	printf("\nEnter the min range of the disk : ");
	scanf("%d", &minRange);
	printf("\nEnter the max range of the disk : ");
	scanf("%d", &maxRange);
	
	int requestQueue[size];
	printf("\nEnter the requests int the queue : \n");
	for(int i = 0; i < size; i++)
		scanf("%d", &requestQueue[i]);
		
		
	printf("\nEnter the initial head : ");
	scanf("%d", &initialHead);
		
	while(1)
	{
		printf("\n\nDISK SCHEDULING ALGORITHM\n");
		printf("\n1) FCFS");
		printf("\n2) SSTF");
		printf("\n3) LOOK");
		printf("\n4) C_LOOK");
		printf("\n5) SCAN");
		printf("\n6) C_SCAN");
		printf("\n7) EXIT");
		printf("\nEnter your choice : ");
		int choice;
		scanf("%d", &choice);
		if(choice == 7)
		{
			printf("\nThanks for using our system...\n");
			break;
		}

		switch(choice)
		{
			case 1:
				printf("\n\n-------------------------- FCFS ------------------------------\n");
				seekTime = calculateTotalSeekTimeFCFS(initialHead, requestQueue, size);
				break;
				
			case 2:
				printf("\n\n-------------------------- SSTF ------------------------------\n");
				seekTime = calculateTotalSeekTimeSSTF(initialHead, requestQueue, size);
				break;
				
			case 3:
				printf("\n\n-------------------------- LOOK ------------------------------\n");
				seekTime = calculateTotalSeekTimeLOOK(requestQueue, size, initialHead);
				break;
				
			case 4:
				printf("\n\n------------------------ C LOOK ------------------------------\n");
				seekTime = calculateTotalSeekTimeC_LOOK(requestQueue, size, initialHead);
				break;
				
			case 5:
				printf("\n\n------------------------- SCAN -------------------------------\n");
				seekTime = calculateTotalSeekTimeSCAN(requestQueue, size, initialHead, minRange, maxRange);
				break;
				
			case 6:
				printf("\n\n------------------------- C SCAN ------------------------------\n");
				seekTime = calculateTotalSeekTimeC_SCAN(requestQueue, size, initialHead, minRange, maxRange);
				break;
				
			default:
				printf("\n\nInvalid choice... Please enter again....\n\n");
				break;
		}
		
	}
	
	
	return 0;
}



