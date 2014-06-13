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


#include "FileReader.h"
#include "Parser.h"

char * ReadFileContent(FILE *fileHandler);



Table ReadTableFromFile(char *fileName)
{
	Table table;
	
	FILE *fileHandler = fopen(fileName, "r");
	
	if (!fileHandler)
	{
		return table;
	}
		
	char *dataString = ReadFileContent(fileHandler);
	
	fclose(fileHandler);
	
	// I will need the FORMATTER here!!!
	
	int **grid = ParseInputText(dataString);
	
	if (grid == NULL)
	{
		return table;
	}
	
	table.grid = grid;
	table.dimensions = GetDimensions();
	table.numberOfPlayers = GetNumberOfPlayers();
	
	return table;
}

void WriteTableToFile(Table *table, char *fileName)
{
	
}




char * ReadFileContent(FILE *fileHandler)
{
	fseek(fileHandler, 0, SEEK_END);
	int fsize = ftell(fileHandler);
	rewind(fileHandler);
	
	char *dataString = (char*) malloc(sizeof(char) * fsize);
	fread(dataString, 1, fsize, fileHandler);
	
	return dataString;
}

