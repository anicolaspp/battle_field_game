//
//  main.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/12/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <Time.h>

#include "FileReader.h"
#include "Table.h"
#include "Parser.h"

int main(int argc, const char * argv[])
{
	char *fileName = "a.txt";
	
	Table *table = ReadTableFromFile(fileName);
	
	FILE *output =  fopen("b.txt", "w");
	
	PrintTable(table, NULL);
	
	fclose(output);
	
		//Vector *v = GetFreePositions(table);
		Vector *v = GetXVector();

	printf("\n");
	
	for (int i = 0; i < v->count; i++)
	{
		printf("%d ", v->values[i]);
	}
	
	printf("\n");
	
	free(v);
	free(table);
	
    return 0;	
}

