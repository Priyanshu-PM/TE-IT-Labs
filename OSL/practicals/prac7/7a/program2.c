#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main()
{
	
	int f1 = 0, f2 = 0, i = 0, ret;
	char readSentence[100], buffer[300];
	int numChar = 0, numWords = 0, numLines = 0, numLetters = 0;
	FILE *fp;
	
	//	giving the write and read permission on the pipe
	ret = mkfifo("myfifo", 0666);
	if((ret < 0) && (errno != EEXIST)) 
	{
		printf("\nERROR WHILE CREATING THE FILE !!\n");
		return 0;
	}
	
	if(errno == EEXIST)
	{
		printf("\nFIFO already exists !!\n");
	}
	
	printf("Waiting for output from FIFO 1...\n");
	sleep(5);
	
	//	reading from the pipe program 1 has created
	f1 = open("myfifo", O_RDONLY);
	read(f1, readSentence, 100);
	
	printf("\nThe data read from the pipe is :\n");
	printf("\n%s\n\n", readSentence);
	int w = 0;
	for(i = 0; readSentence[i] != '\0'; i++)
	{
		if((readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?')) 
		{
			numLines++;
		}
		if((readSentence[i] == ' ') || (readSentence[i] == ',')) 
		{
			numWords++;
		}
		
		if((readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?') || (readSentence[i] == ' ') || (readSentence[i] == ','))
		{
			w++;
		}
	}
	
	numChar = i-1;
	numLetters = i - w - 1;
	
	//	opening the file in write only mode
	fp = fopen("7a.txt", "w");
	fprintf(fp, "\nNO. OF CHARACTERS = %d\n", numChar);
	fprintf(fp, "\nNO. OF LETTERS = %d\n", numLetters);
	fprintf(fp, "\nNO. OF WORDS = %d\n", numWords+1);
	fprintf(fp, "\nNO. OF LINES = %d\n", numLines+1);
	fprintf(fp, "%c", EOF);
	fclose(fp);	//	closing the file
	
	
	//	opening the file in read only mode
	fp = fopen("7a.txt", "r");
	i = 0;	
	while(fscanf(fp, "%c", &buffer[i++]) != EOF )
	{
		buffer[i] = '\0';
	}
	
	//	closing the file
	fclose(fp);
	
	printf("\nWRITING THE OUTPUT TO FIFO 2...\n");
	f2 = open("myfifo", O_WRONLY);
	write(f2, buffer, (strlen(buffer)+1));
	sleep(5);
	
	//	file disruptor
	unlink("myfifo");
	
	return 0;
}
