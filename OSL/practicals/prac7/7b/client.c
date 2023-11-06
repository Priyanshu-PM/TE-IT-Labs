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
	//	passing the same key to connect to the same memory location
	shmid = shmget((key_t)2345, 1024, 0666);
	
	printf("Key of shared memory is : %d\n", shmid);
	shared_memory = shmat(shmid, NULL, 0);
	
	printf("Process attached at %p\n", shared_memory);
	
	printf("Data read from the shared memory is : \n%s\n", (char*)shared_memory);
	
	
	return 0;
}
