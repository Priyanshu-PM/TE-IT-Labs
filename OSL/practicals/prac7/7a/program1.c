//	Process 1

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
	
	int f1 = 0, f2 = 0, ret = 0;
	char sentence[100], readSentence[300];
	
	printf("\nCreating NAMED PIPE 1...\n");
	
	//	used for creating the pipe
	//	1 - char path, 2 - mode of opening
	
	ret = mkfifo("myfifo", 0666);
	
	//	return value < 0 means error in creating the file
	if((ret < 0) && (errno != EEXIST)) 
	{
		printf("\nError while creating the fifo\n");
		return 0;
	}
	
	if(errno == EEXIST)
	{
		printf("FIFO ALREADY EXISTS !!\n");
	}
	
	//	taking the input from the user
	printf("Enter a sentence : \n");
	read(0, sentence, 100);
	printf("\nWriting the sentence to FIFO 1...\n");
	
	//	opening the pipe as a file in write only mode
	f1 = open("myfifo", O_WRONLY);
	write(f1, sentence, (strlen(sentence)+1));
	printf("\nWaiting for output from FIFO 2\n");
	
	//	waiting for program 2 to write text to the file
	sleep(5);
	
	//	opening the file in read only mode
	f2 = open("myfifo", O_RDONLY);
	read(f2, readSentence, 300);
	
	//	printing the data to the terminal
	printf("\nThe data read from the file is : \n%s", readSentence);
	
	unlink("myfifo");
	
	
	return 0;
}
