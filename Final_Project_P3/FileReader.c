//
//  FileReader.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>



#include "FileReader.h"
#include "Parser.h"

char * ReadFileContent(int fd);



Table *ReadTableFromFile(int fd)
{
	Table *table = NULL;
		
	char *dataString = ReadFileContent(fd);
	
	int *grid = ParseInputText(dataString);
	
	if (grid == NULL)
	{
		return table;
	}
	
	free(dataString);
	
	table = GetTable(GetDimensions(), GetNumberOfPlayers(), grid);  // calloc(1, sizeof(Table));//(sizeof(Table));
	
	return table;
}

void WriteTableToFile(Table *table, char *fileName)
{
	FILE *fileHandler = fopen(fileName, "w");
	
	if (fileHandler != NULL)
	{
		PrintTable(table, fileHandler);
	}
	
	fclose(fileHandler);
}

char * ReadFileContent(int fd)
{
	int bufferSize = 1024; // 1 KB
	char buffer[1024];
	char * input = calloc(bufferSize, sizeof(char)); //malloc(sizeof(char) * 1);
	
	
	
	size_t _read = 0;
	
	do
	{
		_read = read(fd, buffer, bufferSize);
		
			//printf("%d\n%s\n",_read, input);
		
		
		input = realloc(input, strlen(input) + _read + 1);
		
		strncat(input, buffer, _read);
	}
	while (_read == bufferSize);
	
	
	return input;
}


