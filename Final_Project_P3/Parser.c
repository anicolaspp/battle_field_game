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

int n, m;
int readingIndex = 0;

char **GetLines(char *);
void CleanCurrentValue(char *);
int ReadDimensions();

int GetNumbersInLine(char *line, int *numbers)
{
	int v = 0;
	int count = 0;
	
	char *current = malloc(sizeof(char) * 1000);
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
	int *numbers = malloc(sizeof(int) * 10000);
	
	int count = GetNumbersInLine(line, numbers);
	
	if (count != 2)
	{
		return 0;
	}
	
	n = numbers[0];
	m = numbers[1];
	
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
	
	char *result = malloc(sizeof(char) * len);
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
	
	return "";
}


int **ParseInputText(char *input)
{
	char *line = GetNextLine(input);
	
	if (!ReadDimensions(line))
	{
		return 0;
	}

	int **grid = malloc(sizeof(int) * n * n);
	
	for (int i = 0; i < n; i++)
	{
		free(line);
		line = GetNextLine(input);
		
		if (strlen(line) <= 0)
		{
			//error the input has an incorrect format
		}
		
		int *numbers = malloc(sizeof(int) * 10000);
		
		int count = GetNumbersInLine(line, numbers);
		
		if (count != m)
		{
			//error the input has an incorrect format
		}
		
		for (int j = 0; j < n; j++)
		{
			grid[(i * n) + j]  = numbers[j];
			
			printf("%d ", grid[(i * n) + j]);
		}
		
		printf("\n");
	}
	

	
	return grid;

	
//	char **lines = GetLines(input);
//	
//	char *header = lines[0];
//	
//		//int n,m;
//	
//	char currentValue[3];
//	int vIndex = 0;
//	
//	for (int i = 0; i < strlen(header); i++)
//	{
//		if (header[i] == '\n')
//		{
//			m = atoi(currentValue);
//			CleanCurrentValue(currentValue);
//			vIndex = 0;
//		}
//		else if (isspace(header[i]))
//		{
//			n = atoi(currentValue);
//			CleanCurrentValue(currentValue);
//			vIndex = 0;
//		}
//		else
//		{
//			currentValue[vIndex++] = header[i];
//		}
//	}
//	
//	int **grid = malloc(sizeof(int) * m * n);
//	
//	for (int i = 1; i < n; i++)
//	{
//		char *currentLine = lines[i];
//		
//		int columnIndex = 0;
//		
//		for (int j = 0; j < strlen(currentLine); j++)
//		{
//			if (isspace(currentLine[j]))
//			{
//				grid[i, columnIndex++] = atoi(currentValue);
//				CleanCurrentValue(currentValue);
//				vIndex = 0;
//			}
//			else
//			{
//				currentValue[vIndex++] = currentValue[j];
//			}
//		}
//	}
//	
//	return grid;
}

char **GetLines(char *txt)
{
	char **result = malloc(sizeof(char) * strlen(txt));
	
	int index = 0;
	
	while (txt[index] != '\n')
	{
		
	}
	
	return 0;
}

void CleanCurrentValue(char *value)
{}










