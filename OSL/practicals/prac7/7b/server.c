#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

int main() 
{

	int i;
	void *shared_memory;
	
	char buffer[100];
	int shmid;
	shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
	//	memory creation for inter process communication
	
	printf("Key of shared memory is : %d\n", shmid);
	shared_memory = shmat(shmid, NULL, 0);
	
	printf("Process attached at memory segment : %p\n", shared_memory);
	 
	printf("Enter the data to write into the file :\n");
	//	scanf("%s", buffer);
	
	read(0, buffer, 100);
	strcpy(shared_memory, buffer);
	printf("You wrote the following data in the memory segment \n%s\n", (char *)shared_memory);

	return 0;
}
