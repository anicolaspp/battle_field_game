//
//  Table.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "Table.h"
#include "Parser.h"
#include "Vector.h"
#include "Point.h"



Vector *GetFreePositions(Table table)
{
	Vector *vector = GetVector(table.dimensions * table.dimensions);
	
	for (int i = 0; i < table.dimensions; i++)
	{
		for (int j = 0; j < table.dimensions; j++)
		{
			int k = PIndex(i,j);
			
			if (table.grid[k] == 0)
			{
				TPoint p;
				p.X = i;
				p.Y = j;
				
				vector->values[vector->count++] = p;
			}
		}
	}
	
	return vector;
}

void Print(void *value, char *format , FILE *file)
{
	if (file == NULL)
	{
		printf(format, value);
	}
	else
	{
		fprintf(file, format, value);
	}
}

void PrintTable(Table *table, FILE *outputFile)
{
	for (int i = 0; i < table->dimensions; i++)
	{
		for (int j = 0; j < table->dimensions; j++)
		{
			Print(table->grid[PIndex(i,j)], "%d ", outputFile);
		}
		
		Print("\n", "%s", outputFile);
	}
}

TPoint InvertIndex(int index, Table *table)
{
	TPoint point;
	
	// Computer here
	
	return point;
}

void DisposeTable(Table * table)
{
	if (table != NULL)
	{
		free(table->grid);
		free(table);
	}
}

int * CopyGrid(int * grid, int n)
{
	int * result = calloc(n, sizeof(int));
	
	for (int i = 0; i < n; i++)
	{
		result[i] = grid[i];
	}
	
	return result;
}

Table * GetTable(int dimensions, int numberOfPlayers, int * grid)
{
	Table * result = calloc(1, sizeof(Table));
	
	result->dimensions = dimensions;
	result->numberOfPlayers = numberOfPlayers;
	result->grid = CopyGrid(grid, dimensions * dimensions);
	
	return result;
}

Table * CopyTable(Table * table)
{
	Table * result = GetTable(table->dimensions, table->numberOfPlayers, table->grid);
	
	return result;
}





