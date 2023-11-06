#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Process {

	int arrivalTime;
	int burstTime;
	int remainingTime;
	int pid;
};

void swap(struct Process *a, struct Process *b)
{
	struct Process temp = *a;
	*a = *b;
	*b = temp;
}

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


int main()
{
	
	int n;
	int timeQuantum;
	printf("\nEnter the number of processes : ");
	scanf("%d", &n);
	printf("\nEnter the time quantum : ");
	scanf("%d", &timeQuantum);
	
	printf("\n");
	
	struct Process processes[n];
	
	printf("\nEnter the details of the processes : \n");
	printf("\narrival time \t\t burst time\n");
	
	for(int i = 0; i < n; i++)
	{
		printf("\nEnter the values for process %d : ", i + 1);
		processes[i].pid = i+1;
		scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
		processes[i].remainingTime = processes[i].burstTime;
	}
	
	
	int completionTime[n];
	int waitingTime[n];
	int turnAroundTime[n];
	
	int currentTime = 0;
	int completedProcess = 0;
	
	printf("\nSorting the process according to the arrival time...\n");
	sortByArrival(processes, n);
	
	while(completedProcess < n)
	{
		
		for(int i = 0; i < n; i++)
		{
			if(processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) 
			{
				if(processes[i].remainingTime > timeQuantum)
				{
					currentTime += timeQuantum;
					processes[i].remainingTime -= timeQuantum;
				}
				else 
				{
					currentTime += processes[i].remainingTime;
					processes[i].remainingTime = 0;
					completedProcess++;
					
					completionTime[i] = currentTime;
					turnAroundTime[i] = completionTime[i] - processes[i].arrivalTime;
					waitingTime[i] = turnAroundTime[i] - processes[i].burstTime;
				}
			}
		}
		
	}
	
	printf("\nProcess Id\tArrival Time\tBurst Time\tCompletion Time\tTurnAround Time\tWaiting Time\n");
	int totalTurnAroundTime = 0, totalCompletionTime = 0, totalWaitingTime = 0;
	
	for(int i = 0; i < n; i++)
	{
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, completionTime[i], turnAroundTime[i], waitingTime[i]);
		totalTurnAroundTime += turnAroundTime[i];
		totalCompletionTime += completionTime[i];
		totalWaitingTime += waitingTime[i];
	}
	
	float avgTAT = totalTurnAroundTime / n;
	float avgCT = totalCompletionTime / n;
	float avgWT = totalWaitingTime / n;
	
	printf("\n\nAVG. COMPLETION TIME = %f", avgCT);
	printf("\n\nAVG. TURNAROUND TIME = %f", avgTAT);
	printf("\n\nAVG. TOTAL WAITING TIME = %f\n", avgWT);
	printf("\n\n");


	return 0;
}





