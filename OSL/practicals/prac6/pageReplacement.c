//	First In First Out Algorithm
//	Least Recently Used Algorithm
//	Optimal Page Replacement

#include <stdio.h>
#include <stdlib.h>


//	printing the frame
void printFrame(int frames[], int frame_size, char hit_or_miss)
{
	printf("| ");
	for(int i = 0; i < frame_size; i++)
	{
		printf("%d |", frames[i]);
	}
	printf(" --> %c |", hit_or_miss);
	printf("\n");
}


//	function to check if the page is in frame
int is_page_in_frame(int page, int frames[], int frame_size)
{
	for(int i = 0; i < frame_size; i++)
	{
		if(page == frames[i])
		{
			return 1;
		}
	}
	return 0;
}


//	FIFO page replacement algorithm
int fifo_page_replacement(int pageArray[], int pages, int frame_size)
{
	int pageFaults = 0;
	int frameIndex = 0;
	
	//	initializing frame with -1
	int frames[frame_size];
	for(int i = 0; i < frame_size; i++)
		frames[i] = -1;
	
	for(int i = 0; i < pages; i++)
	{
		
		if(!is_page_in_frame(pageArray[i], frames, frame_size))
		{
			pageFaults++;
		
			frames[frameIndex] = pageArray[i];
			frameIndex = (frameIndex + 1) % frame_size;	
			printFrame(frames, frame_size, 'M');
		}
		else
		{
			printFrame(frames, frame_size, 'H');
		}
	}
	
	return pageFaults;
}

int get_least_recently_used_index(int pageArray[], int frame_size, int frames[], int currentIndex)
{
	int index = -1;
	int leastRecent = currentIndex;
	for(int i = 0; i < frame_size; i++)
	{
		for(int j = currentIndex - 1; j >= 0; j--)
		{
			if(frames[i] == pageArray[j])
			{
				if(j < leastRecent)
				{
					leastRecent = j;
					index = i;
				}
				break;
			}
		}
	}
	
	return index;
}


int LRU_page_replacement(int pages, int pageArray[], int frame_size)
{
	int pageFaults = 0;

	int frames[frame_size];
	
	//	initializing frame with -1
	for(int i = 0; i < frame_size; i++)
		frames[i] = -1;
	
	for(int i = 0; i < pages; i++)
	{
		if(!is_page_in_frame(pageArray[i], frames, frame_size))
		{
			pageFaults++;
			
			if(pageFaults <= frame_size)
			{
				for(int j = 0; j < frame_size; j++)
				{
					if(frames[j] == -1)
					{
						frames[j] = pageArray[i];
						break;
					}
				}
			}
			else 
			{
			
				int replace_index = get_least_recently_used_index(pageArray, frame_size, frames, i);
				frames[replace_index] = pageArray[i];
			}
			
			
			printFrame(frames, frame_size, 'M');
		}
		else
		{
			printFrame(frames, frame_size, 'H');
		}
	}
	
	return pageFaults;
}

int get_farthest_in_future(int pages, int pageArray[], int currentIndex, int frame_size, int frames[])
{
	int index = -1;
	int farthest = -1;
	
	for(int i = 0; i < frame_size; i++)
	{
		int found = 0;
		for(int j = currentIndex+1; j < pages; j++)
		{
			if(frames[i] == pageArray[j])
			{
				if(j > farthest)
				{
					farthest = j;
					index = i;
				}
			}
			found = 1;
			break;
		}
		
		if(found == 0)
		{
			return i;
		}
	}
	
	return index;
}

int optimal_page_replacement(int pages, int pageArray[], int frame_size)
{
	int pageFaults = 0;
	
	int frames[frame_size];
	for(int i = 0; i < frame_size; i++)
		frames[i] = -1;
		
	for(int i = 0; i < pages; i++)
	{
		
		if(!is_page_in_frame(pageArray[i], frames, frame_size))
		{
			pageFaults++;
			if(pageFaults <= frame_size)
			{
				for(int j = 0; j < frame_size; j++)
				{
					if(frames[j] == -1)
					{
						frames[j] = pageArray[i];
						break;
					}
				}
			}
			else
			{
				int farthest_index = get_farthest_in_future(pages, pageArray, i, frame_size, frames);
				frames[farthest_index] = pageArray[i];
			}
			
			printFrame(frames, frame_size, 'M');
		}
		else
		{
			printFrame(frames, frame_size, 'H');
		}	
		
	}
	
	
	return pageFaults;
}


int main()
{
	int pages;
	int frame_size;
	int algoChoice;
	printf("\nEnter the number of pages : ");
	scanf("%d", &pages);
	
	int pageArray[pages];
	printf("\nEnter the page sequence : ");	
	for(int i = 0; i < pages; i++)
		scanf("%d", &pageArray[i]);
		
	printf("\nEnter the frame size : ");
	scanf("%d", &frame_size);
	
	
	while(1)
	{
		printf("\n\nPage Replacement Algorithm\n");
		printf("1) FIFO\n");
		printf("2) LRU\n");
		printf("3) Optimal Page Replacement\n");
		printf("4) Exit\n");
		printf("Enter your choice :- ");
		scanf("%d", &algoChoice);
		int pageFaults = 0;
		if(algoChoice == 4)
		{
			printf("\nThanks for using the system...\n\n");
			break;
		}
		
		switch(algoChoice)
		{
			case 1:
				pageFaults = fifo_page_replacement(pageArray, pages, frame_size);
				printf("\nNUMBER OF PAGE FAULTS ARE :- %d\n", pageFaults);
				break;
				
			case 2:
				pageFaults = LRU_page_replacement(pages, pageArray, frame_size);
				printf("\nNUMBER OF PAGE FAULTS ARE :- %d\n", pageFaults);
				break;
				
			case 3:
				pageFaults = optimal_page_replacement(pages, pageArray, frame_size);
				printf("\nNUMBER OF PAGE FAULTS ARE :- %d\n", pageFaults);
				break;
			
			default:
				printf("\nInvalid choice... Please enter again...\n");
				break;
		}
	}
	
	return 0;
}
