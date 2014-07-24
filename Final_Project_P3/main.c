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
#include <pthread.h>

#include "FileReader.h"
#include "Table.h"
#include "Parser.h"
#include "WinnerMoveStrategy.h"
#include "Vector.h"

#define true 1
#define false 0

pid_t pid;
int numberOfGames;
int numberOfPipes;
struct pollfd * fds;

int * playerIds;

int threadCancelled = 0;


typedef struct
{
	int inputFd;
	int outputFd;
	int gameId;
} ProcessFileArgs;




void sigterm_handler(int signal);

void ProcessFileContentAsync(int fd, int outFd, int gameId);
void * ProcessFile(ProcessFileArgs * args);

char * GetOutputFileName(int index);
char * GetInputFileName(int index);

void CreatePipes(int numberOfPipes);
void UnBind(int pipesCount);

int IsInputPipeIndex(int index);
void PrintStats(Table *table, Vector *emptyCellVector);
void ProcessInputFileDecriptors(struct pollfd * fds);
void InitPlayerIds(int numberOfGames);
int GetPlayerId(int gameId, Table * table);


void sig_thread(void * args)
{
    sigset_t * set = args;
    int s, sig;
    
    for (;;)
    {
        s = sigwait(set, &sig);
		
		printf("%d\n", sig);
    
        if (sig == SIGTERM)
        {
            pthread_exit(NULL);
        }
    }
    
}

void ProcessInput()
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	
    while (true)
    {
        int ret = poll(fds, numberOfPipes, 5);
        
        if (ret > 0)
        {
			ProcessInputFileDecriptors(fds);
        }
		else if (threadCancelled == 1)
		{
			pthread_exit(NULL);
		}
    }
}

int main(int argc, const char * argv[])
{
	if (argc == 2)
	{
	    pthread_t thread;
        sigset_t set;
        
        sigemptyset(&set);
        sigaddset(&set, SIGTERM);
        
        pthread_sigmask(SIG_BLOCK, &set, NULL);
        pthread_create(&thread, NULL, &sig_thread, &set);
        
		pid = getpid();
		printf("%d\n", pid);
		
		numberOfGames = 1; //atoi(argv[1]);
		numberOfPipes = numberOfGames * 2;

		CreatePipes(numberOfPipes);
		InitPlayerIds(numberOfGames);
        
        pthread_t mainPThread;
        
        pthread_create(&mainPThread, NULL, &ProcessInput, NULL);

        pthread_join(thread, NULL);
        
        pthread_cancel(mainPThread);
        
        UnBind(numberOfPipes);
		
		pthread_exit(NULL);
	}
	
    return 0;	
}



void ProcessInputFileDecriptors(struct pollfd * fds)
{
	for (int i = 0; i < numberOfPipes; i++)
	{
		if (fds[i].revents == POLLIN)
		{
			assert(IsInputPipeIndex(i));
			
			ProcessFileArgs * args = calloc(1, sizeof(ProcessFileArgs));
			args->inputFd = fds[i].fd;
			args->outputFd = fds[i + 1].fd;
			args->gameId = i;
			
            ProcessFile(args);
		}
	}
}

void InitPlayerIds(int numberOfGames)
{
	playerIds = malloc(sizeof(int) * numberOfGames);
	
	for (int i = 0 ; i < numberOfGames; i++)
	{
		playerIds[i] = -1;
	}
}

void sigterm_handler()
{
   	UnBind(numberOfPipes);
	
	free(playerIds);
}

void * ProcessFile(ProcessFileArgs * args)//int fd, int outFd, int gameId)
{
	Table *table = ReadTableFromFile(args->inputFd);
	
	if (table != NULL)
	{
		Vector * emptyCellVector = GetXVector();
		
		PrintStats(table, emptyCellVector);
		
		int playerId = GetPlayerId(args->gameId, table);
		
		TPoint move = WinnerMoveStrategy_Play(table, emptyCellVector, playerId); //RandomMoveStrategy_Play(emptyCellVector);
		
		char buffer[100];
		int len = sprintf(buffer, "[%d, %d, %d]\n", playerId, move.X + 1, move.Y + 1);
		
		write(args->outputFd, buffer, len);
		
		DisposeVector(emptyCellVector);
		DisposeTable(table);
	}
	
	return NULL;
}

void PrintStats(Table *table, Vector *emptyCellVector)
{
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
}

int GetPlayerId(int gameId, Table * table)
{
	if (playerIds[gameId] >= 0)
	{
		return playerIds[gameId];
	}
	
	int maxValue = -1;
	
	for (int i = 0; i < table->dimensions; i ++)
	{
		for (int j = 0; j < table->dimensions; j++)
		{
			int index = PIndex(i, j);
			
			if (maxValue < table->grid[index])
			{
				maxValue = table->grid[index];
			}
		}
	}
	
	playerIds[gameId] = maxValue + 1;
	
	return maxValue + 1;
}

void CreatePipes(int numberOfPipes)
{
	fds = malloc(sizeof(struct pollfd) * numberOfPipes);
	
	for (int i = 0; i < numberOfPipes; i += 2)
	{
		char * input = GetInputFileName(i);
		
		mkfifo(input, 0777);
		
		fds[i].fd = open(input, O_RDWR);
		fds[i].events = POLLIN;
		fds[i].revents = 0;
		
		char * output = GetOutputFileName(i);
		
		mkfifo(output, 0777);
		
		fds[i + 1].fd = open(output, O_RDWR);
		
		free(input);
		free(output);
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

int IsInputPipeIndex(int index)
{
	return index % 2 == 0;
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


