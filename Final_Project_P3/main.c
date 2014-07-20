//
//  main.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/12/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <Time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <poll.h>
#include <fcntl.h>


#include "FileReader.h"
#include "Table.h"
#include "Parser.h"

pid_t pid;


void ProcessFile(char * fName)
{
	Table *table = ReadTableFromFile(fName);
	
	char * foutputName = malloc(sizeof(char) * strlen(fName));
	
	strncpy(foutputName, fName, strlen(fName));
	strcat(foutputName, ".stat");
		
	FILE *output =  fopen("b.txt", "w");
		
	if (table != NULL)
	{
		Vector * v = GetXVector();
		
		FILE * output = fopen(foutputName, "w");
		
		if (output)
		{
			fprintf(output, "Size: %d\n", table->dimensions);
			fprintf(output, "Number of players: %d\n", table->numberOfPlayers);
		
			fprintf(output, "Number of empty cells: %d\n", v->count);
		
			if (v->count > 0)
			{
				fprintf(output, "Location of first empty cells: [%d, %d]\n", v->values[0].X + 1, v->values[0].Y + 1);
				fprintf(output, "Location of last empty cells: [%d, %d]\n", v->values[v->count - 1].X + 1, v->values[v->count - 1].Y + 1);
			}
		
			fprintf(output, "Player ranking:\n");
		
			int * playersRanking = GetPlayerRanking();
		
			for (int i = 1; i <= table->numberOfPlayers; i++)
			{
				fprintf(output, "    Player %d has %d cells\n", i, playersRanking[i]);
			}
							
			free(v);
			free(table);
		}
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

struct pollfd * CreatePipes(int numberOfPipes)
{
	struct pollfd * result = malloc(sizeof(struct pollfd) * numberOfPipes);
	
	for (int i = 0; i < numberOfPipes; i += 2)
	{
		char input[20];
		sprintf(input, "%d_%di", pid, i);
		
		mkfifo(input, 0600);
		
		result[i].fd = open(input, O_RDWR);
		result[i].events = POLLIN;
		result[i].revents = 0;
		
		
		char output[20];
		sprintf(output, "%d_%do", pid, i);
		
		mkfifo(output, 0600);
		
		result[i + 1].fd = open(output, O_RDWR);
	}
	
	return result;
}


int main(int argc, const char * argv[])
{
	
		//if (argc == 2)
	{
		pid = getpid();
		printf("%d", pid);
		
		int numberOfGames = 1; //atoi(argv[1]);
		
		int numberOfPipes = numberOfGames * 2;
		
		struct pollfd * fds = CreatePipes(numberOfPipes);
		
		while (1)
		{
			int ret = poll(fds, numberOfPipes, -1);
			
			for (int i = 0; i < numberOfPipes; i++)
			{
				if (fds[i].revents == POLLIN)
				{
					printf("%d\n", i);
					fds[i].revents = 0;
				}
			}
		}
		
		UnBind(numberOfPipes);
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

