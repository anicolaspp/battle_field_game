//
//  main.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/12/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>

#include "FileReader.h"
#include "Table.h"

int main(int argc, const char * argv[])
{
	char *fileName = "a.txt";
	
	Table table = ReadTableFromFile(fileName);
	
	if (table.dimensions > 0)
	{
		for (int i = 0; i < table.dimensions; i++)
		{
			for (int j = 0 ; j < table.dimensions; j++)
			{
				printf("%d ", table.grid[Index(i, j)]);
			}
			
			printf("\n");
		}
	}
	
	Dispose(table);
	
	// insert code here...
	printf("Hello, World!\n");
    return 0;
	
	
}

