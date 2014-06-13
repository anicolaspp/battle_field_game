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


void PrintTable(Table table)
{
	for (int i = 0; i < table.dimensions; i++)
	{
		for (int j = 0; j < table.dimensions; j++)
		{
			int k = Index(i,j);
			
			int v = table.grid[k];
			
			printf("%d ", v);
		}
		
		printf("\n");
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