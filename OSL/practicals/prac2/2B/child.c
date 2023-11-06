#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int a[10];
	int low, high, mid;
	int key, ans = 0;
	
	printf("\n\nEnter the number to be searched : ");
	scanf("%d", &key);
	
	int i;
	for(i = 0; i < argc; i++)
	{
		a[i] = atoi(argv[i]);
	}
	low = 0, high = i - 1;
	while(low <= high)
	{
		mid = (low + high)/2;
		if(key == a[mid])
		{
			ans = 1;
			break;
		}
		else if(key < a[mid])
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	
	if(ans == 1)
		printf("\nThe number is found...\n");
	else
		printf("\nThe number is not found\n");
	
	
	return 0;
}
