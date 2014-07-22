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
#include "SingleMoveStrategy.h"
#include "RandomMoveStrategy.h"

#define true 1
#define false 0

pid_t pid;
int numberOfGames;
int numberOfPipes;
struct pollfd * fds;

void sigterm_handler(int signal);

void ProcessFileContentAsync(int fd, int outFd);
void ProcessFile(int fd, int outFd);

char * GetOutputFileName(int index);
char * GetInputFileName(int index);

void CreatePipes(int numberOfPipes);
void UnBind(int pipesCount);

int IsInputPipeIndex(int index);


int main(int argc, const char * argv[])
{
		//if (argc == 2)
	{
		signal(SIGTERM, sigterm_handler);
		
		pid = getpid();
		printf("%d\n", pid);
		
		numberOfGames = 1; //atoi(argv[1]);
		numberOfPipes = numberOfGames * 2;
		CreatePipes(numberOfPipes);
		
		while (true)
		{
			int ret = poll(fds, numberOfPipes, -1);
			
			if (ret > 0)
			{
				for (int i = 0; i < numberOfPipes; i++)
				{
					if (fds[i].revents == POLLIN)
					{
						assert(IsInputPipeIndex(i));
						char * outputFileName = GetOutputFileName(i);
					
						ProcessFileContentAsync(fds[i].fd, fds[i + 1].fd);
					
						free(outputFileName);
					}
				}
			}
		}
	}
	
    return 0;	
}

void sigterm_handler()
{
	
	printf("-----------\n");
	
	
	UnBind(numberOfPipes);
	
		//TODO: I will probably have to wait for children to finish before exit
	
	exit(EXIT_SUCCESS);
}



int IsInputPipeIndex(int index)
{
	return index % 2 == 0;
}

void ProcessFileContentAsync(int fd, int outFd)
{
	ProcessFile(fd, outFd);
		//
		//
		//	pid_t nPid = fork();
		//
		//	if (nPid)
		//	{
		//		ProcessFile(fd, outputFileName);
		//		exit(EXIT_SUCCESS);
		//	}
}

void ProcessFile(int fd, int outFd)
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
		
		int playerId = 0; //GetPlayerId();
		
		
		TPoint move = RandomMoveStrategy_Play(emptyCellVector);
		
		char buffer[100];
		int len = sprintf(buffer, "[%d, %d, %d]\n", playerId, move.X + 1, move.Y + 1);
		
		write(outFd, buffer, len);
			
		free(emptyCellVector);
		free(table);
		
	}
}

void UnBind(int pipesCount)
{
	for (int i = 0; i < pipesCount; i += 2)
	{
		char * input = GetInputFileName(i);
		char * output = GetOutputFileName(i);
		
		close(fds[i].fd);
		close(fds[i+1].fd);
		
		unlink(input);
		unlink(output);
		
		free(input);
		free(output);
	}
	
	free(fds);
}




void CreatePipes(int numberOfPipes)
{
	fds = malloc(sizeof(struct pollfd) * numberOfPipes);
	
	for (int i = 0; i < numberOfPipes; i += 2)
	{
		char * input = GetInputFileName(i);
		
		mkfifo(input, 0600);
		
		fds[i].fd = open(input, O_RDWR);
		fds[i].events = POLLIN;
		fds[i].revents = 0;
		
		char * output = GetOutputFileName(i);
		
		mkfifo(output, 0600);
		
		fds[i + 1].fd = open(output, O_RDWR);
		
		free(input);
		free(output);
	}
}

char * GetOutputFileName(int index)
{
	char * output = malloc(sizeof(char) * 20);
	sprintf(output, "%d_%do", pid, index);
	
	return output;
}


char * GetInputFileName(int index)
{
	char * input = malloc(sizeof(char) * 20);
	sprintf(input, "%d_%di", pid, index);
	
	return input;
}


