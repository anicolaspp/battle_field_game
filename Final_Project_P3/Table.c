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

void Dispose(Table * table)
{
	if (table->dimensions > 0)
	{
		free(table->grid);
	}
	
		//memset(table, 0, sizeof(table));
	free(table);
}

