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

void PrintTable(Table table, FILE *outputFile)
{
	for (int i = 0; i < table.dimensions; i++)
	{
		for (int j = 0; j < table.dimensions; j++)
		{
			Print(table.grid[Index(i,j)], "%d ", outputFile);
			
		}
		
		Print("\n", "%s", outputFile);
	}
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

