//
//  main.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/12/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

#include "FileReader.h"
#include "Table.h"
#include "Parser.h"

#define true 1
#define false 0

pid_t pid;
int numberOfGames;

int numberOfPipes;

void sigterm_handler(int signal);


void ProcessFile(int fd, char * outputFileName)
{
	Table *table = ReadTableFromFile(fd);
		
	if (table != NULL)
	{
		Vector * emptyCellVector = GetXVector();
		
		printf("Size: %d\n", table->dimensions);
		printf("Number of players: %d\n", table->numberOfPlayers);
		
		printf("Number of empty cells: %d\n", emptyCellVector->count);
		
		if (emptyCellVector->count > 0)
		{
			printf("Location of first empty cells: [%d, %d]\n",
				   emptyCellVector->values[0].X + 1, emptyCellVector->values[0].Y + 1);
		
			printf("Location of last empty cells: [%d, %d]\n",
				   emptyCellVector->values[emptyCellVector->count - 1].X + 1, emptyCellVector->values[emptyCellVector->count - 1].Y + 1);
		}
	
		FILE *output =  fopen(outputFileName, "w");
		
		if (output)
		{
				//TODO: ready to play
				
		}
		
		free(emptyCellVector);
		free(table);

	}
}

void UnBind(int pipesCount)
{
	for (int i = 0; i < pipesCount; i++)
	{
		char input[20];
		sprintf(input, "%d_%di", pid, i);
		
		unlink(input);
		
		char output[20];
		sprintf(output, "%d_%do", pid, i);
		
		unlink(output);
	}
}

char * GetInputFileName(int index)
{
	char * input = malloc(sizeof(char) * 20);
	sprintf(input, "%d_%di", pid, index);
	
	return input;
}

char * GetOutputFileName(int index)
{
	char * output = malloc(sizeof(char) * 20);
	sprintf(output, "%d_%do", pid, index);
	
	return output;
}

struct pollfd * CreatePipes(int numberOfPipes)
{
	struct pollfd * result = malloc(sizeof(struct pollfd) * numberOfPipes);
	
	for (int i = 0; i < numberOfPipes; i += 2)
	{
		char * input = GetInputFileName(i);
		
		mkfifo(input, 0600);
		
		result[i].fd = open(input, O_RDWR);
		result[i].events = POLLIN;
		result[i].revents = 0;
		
		char * output = GetOutputFileName(i);
		
		mkfifo(output, 0600);
		
		result[i + 1].fd = open(output, O_RDWR);
		
		free(input);
		free(output);
	}
	
	return result;
}

int _sig ;

void sigterm_handler()
{

	printf("-----------\n");
	
	
	UnBind(numberOfPipes);

		//TODO: I will probably have to wait for children to finish before exit
	
	exit(EXIT_SUCCESS);
}

void ProcessFileContentAsync(int fd, char * outputFileName)
{
	ProcessFile(fd, outputFileName);
//	
//	
//	pid_t nPid = fork();
//	
//	if (nPid)
//	{
//		ProcessFile(fileContentStr, outputFileName);
//		exit(EXIT_SUCCESS);
//	}
}

typedef void (*sighandler_t)(int);

int IsInputPipeIndex(int index)
{
	return index % 2 == 0;
}

int main(int argc, const char * argv[])
{
	
		//if (argc == 2)
	{
		signal(SIGTERM, sigterm_handler);
		
		pid = getpid();
		printf("%d\n", pid);
		
		int numberOfGames = 1; //atoi(argv[1]);
		int numberOfPipes = numberOfGames * 2;
		struct pollfd * fds = CreatePipes(numberOfPipes);
		
		while (true)
		{
			int ret = poll(fds, numberOfPipes, 500);
			
			for (int i = 0; i < numberOfPipes; i++)
			{
				if (fds[i].revents == POLLIN)
				{
					assert(IsInputPipeIndex(i));
					char * outputFileName = GetOutputFileName(i);
					
					ProcessFileContentAsync(fds[i].fd, outputFileName);
					
						//fds[i].revents = 0;
					printf("\n");
					
					free(outputFileName);
				}
			}
		}
	}
	
	
	
//	if (argc != 2)
//	{
//		printf("Incorrent input");
//
//		return -1;
//	}
//	
//	char * fileName = argv[1];
//	FILE * handler = fopen(fileName, "r");
//	
//	if (handler)
//	{
//		char * fName = malloc(sizeof(char) * 30);
//		
//		while (1)
//		{
//			int result = fscanf(handler, "%s\n", fName);
//			
//			if (result == EOF)
//			{
//				break;
//			}
//			
//			pid_t pid = fork();
//			
//			if (pid == 0)
//			{
//				ProcessFile(fName);
//				
//				return 0;
//			}
//			else
//			{
//				printf("Created child %d working of file %s\n", pid, fName);
//			}
//		}
//	
//	}
//	
//	int status;
//	pid_t wpid;
//	
//	while ((wpid = wait(&status)) > 0) {
//
//	}
	
    return 0;	
}

