//	Preemptive Shortest Job First


#include <stdio.h>
#include <stdlib.h>

struct Process
{
	int pid;
	int arrivalTime;
	int burstTime;
	int remainingTime;
};


//	sorting by arrival time
void sortByArrival(struct Process processes[], int n) 
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n - i - 1; j++)
		{
			if(processes[j].arrivalTime > processes[j+1].arrivalTime)
			{
				struct Process temp = processes[j];
				processes[j] = processes[j+1];
				processes[j+1] = temp;
			}
		}
	}
	
}


//	for finding the job with shortest burst time left
int findShortestJob(struct Process processes[], int n, int currentTime) 
{
	int shortestJob = -1;
	int shortestBurst = 999999;
	for(int i = 0; i < n; i++)
	{
		if(processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].remainingTime < shortestBurst)
		{
			shortestBurst = processes[i].remainingTime;
			shortestJob = i;
		}
	}
	
	return shortestJob;
}

void printArray(struct Process processes[], int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("\n%d\t\t%d\t\t%d\t\t%d", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].remainingTime);
	}
	
	printf("\n\n");
}

int main()
{
	int n;
	printf("\nEnter the number of processes : ");
	scanf("%d", &n);
	
	struct Process processes[n];
	printf("\nEnter the arrival time and burst time\n");
	printf("\t\tArrival Time\tBurst Time\n");
	for(int i = 0; i < n; i++)
	{
		printf("\nEnter the values for process %d : ", i+1);
		scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
		processes[i].remainingTime = processes[i].burstTime;		
		processes[i].pid = i+1;
	}
	
	//	printArray(processes, n);
	printf("\nSorting the processes on the basis of their arrival time\n\n");
	sortByArrival(processes, n);
	printArray(processes, n);
	
	int completionTime[n];
	int turnAroundTime[n];
	int waitingTime[n];
	int currentTime = 0;
	int completedProcess = 0;
	int shortestJob = -1;
	while(completedProcess < n)
	{
		shortestJob = findShortestJob(processes, n, currentTime);
		
		if(shortestJob == -1)
		{
			currentTime++;
			continue;
		}
		
		processes[shortestJob].remainingTime--;
		currentTime++;
		
		if(processes[shortestJob].remainingTime == 0)
		{
			completedProcess++;
			completionTime[shortestJob] = currentTime;
		}
	}
	
	float totalTurnAroundTime = 0, totalWaitingTime = 0;
	printf("\n\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnAround Time\tWaiting Time\n");
	
	for(int i = 0; i < n; i++)
	{
		turnAroundTime[i] = completionTime[i] - processes[i].arrivalTime;
		waitingTime[i] = turnAroundTime[i] - processes[i].burstTime;
		
		totalTurnAroundTime += turnAroundTime[i];
		totalWaitingTime += waitingTime[i];
		
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, completionTime[i], turnAroundTime[i], waitingTime[i]);
	}
	
	float avgTAT = totalTurnAroundTime / n;
	float avgWT = totalWaitingTime / n;
	
	printf("AVG TURN AROUND TIME = %f\n", avgTAT);
	printf("AVG WAITING TIME = %f\n", avgWT);
	printf("\n\n\n");
	
	
	return 0;
}



