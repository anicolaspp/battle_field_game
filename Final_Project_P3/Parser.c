//
//  Parser.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/12/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Parser.h"
#include "Vector.h"

int *playerCount;

Vector *_vector;


int _dimesion, _numberOfPlayers;
int readingIndex = 0;

int _hasBeenInit = 0;

int *grid;

int ReadDimensions();
char *GetNextLine(char *);
void PrintGrid(int **);
int GetNumbersInLine(char *line, int *numbers);

Vector *GetXVector()
{
	return _vector;
}

int * GetPlayerRanking()
{
	return playerCount;
}

void InitVars()
{
	readingIndex = 0;
	_hasBeenInit = 0;
}

void InitPlayerRanking(void)
{
	playerCount = calloc(_numberOfPlayers, sizeof(int));//(sizeof(int) * _numberOfPlayers);
	
	for (int i = 0; i <= _numberOfPlayers; i++)
	{
		playerCount[i] = 0;
	}
}

int * ParseInputText(char *input)
{
	InitVars();
	
	char *line = GetNextLine(input);
	
	if (!ReadDimensions(line))
	{
		return 0;
	}
	
	grid = calloc(_dimesion * _dimesion, sizeof(int));//(sizeof(int) * _dimesion * _dimesion);
	_vector = GetVector(_dimesion * _dimesion);
	
	free(line);
		//InitPlayerRanking();
	
	for (int i = 0; i < _dimesion; i++)
	{
			//free(line);
		line = GetNextLine(input);
		
		if (strlen(line) <= 0)
		{
				//error the input has an incorrect format
		}
		
		int *numbers = calloc(_dimesion, sizeof(int));//(sizeof(int) * _dimesion);
		
		int count = GetNumbersInLine(line, numbers);
		
		if (count != _dimesion)
		{
				//error the input has an incorrect format
		}
		
		for (int j = 0; j < _dimesion; j++)
		{
			int k = PIndex(i, j);
			
			grid[k]  = numbers[j];
			
			if (grid[k] == 0)
			{
				TPoint p;
				p.X = i;
				p.Y = j;
				
				_vector->values[_vector->count++] = p;
			}
		}

		free(line);
		free(numbers);
	}

	
	_hasBeenInit = 1;
	
	return grid;
	
}

int GetDimensions()
{
	return _dimesion;
}

int GetNumberOfPlayers()
{
	return _numberOfPlayers;
}

int HasTableBeenInitialized()
{
	return _hasBeenInit;
}

int *GetGrid()
{
	if (HasTableBeenInitialized())
	{
		return grid;
	}
	
	return NULL;
}

int GetNumbersInLine(char *line, int *numbers)
{
	int v = 0;
	int count = 0;
	
	char *current = calloc(strlen(line), sizeof(char));//(sizeof(char) * strlen(line));
	int countCurrent = 0;
	
	while (v <= strlen(line))
	{
		if (line[v] == '\t' || line[v] == ' ' || line[v] == '\0')
		{
			char xxx[countCurrent];

			for (int i = 0; i < countCurrent; i++)
			{
				xxx[i] = current[i];
			}
				
			int value = atoi(xxx);
			countCurrent = 0;
			
			numbers[count++] = value;
		}
		else
		{
			current[countCurrent++] = line[v];
		}
		
		v++;
	}
	
	free(current);
	
	return count;
}

int ReadDimensions(char *line)
{
	int *numbers = calloc(strlen(line), sizeof(int));//(sizeof(int) * strlen(line));
	
	int count = GetNumbersInLine(line, numbers);
	
	if (count != 2)
	{
		return 0;
	}
	
	_dimesion = numbers[0];
	_numberOfPlayers = numbers[1];
	
	free(numbers);
		
	return 1;
}

char *GetNextLine(char * input)
{
	
	int len = strlen(input);
	
	if (len <= readingIndex)
	{
		return "";
	}
	
	char *result = calloc(len, sizeof(char));
	int vIndex = 0;
	
	while (readingIndex < len)
	{
		if (input[readingIndex] == '\0')
		{
			return result;
		}
		else if (input[readingIndex] == '\n')
		{
			readingIndex++;
			return result;
		}
		else
		{
			result[vIndex++] = input[readingIndex];
		}
		
		readingIndex++;
	}
	
	return result;
}

void PrintGrid(int **grid)
{
	for (int i = 0; i < GetDimensions(); i++)
	{
		for (int j = 0; j < GetDimensions(); j ++)
		{
			printf("%d ", grid[PIndex(i, j)]);
		}
		
		printf("\n");
	}
}











