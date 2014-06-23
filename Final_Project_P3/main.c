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
	
		//	FILE *output =  fopen("b.txt", "w");
	
	if (table != NULL)
	{
			PrintTable(table, NULL);
		
			//WriteTableToFile(table, "b.txt");
	
			//	fclose(output);
	
			//Vector *v = GetFreePositions(table);
			Vector *v = GetXVector();

		printf("\n");
	
		for (int i = 0; i < v->count; i++)
		{
			printf("%d ", v->values[i].X);
			printf("%d\n", v->values[i].Y);
		}
	
		printf("\n");
		
		
		printf("Size: %d\n", table->dimensions);
		printf("Number of players: %d\n", table->numberOfPlayers);
		printf("Number of empty cells: %d\n", v->count);
		
		printf("Location of first empty cells: [%d, %d]\n", v->values[0].X + 1, v->values[0].Y + 1);
		printf("Location of last empty cells: [%d, %d]\n", v->values[v->count - 1].X + 1, v->values[v->count - 1].Y + 1);
		
		printf("Player ranking:\n");
		
		int * playersRanking = GetPlayerRanking();
		
		for (int i = 1; i <= table->numberOfPlayers; i++)
		{
			printf("Player %d has %d cells\n", i, playersRanking[i]);
		}
		
	
		free(v);
		free(table);
	}
	
    return 0;	
}

