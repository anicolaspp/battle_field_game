//
//  Table.h
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#ifndef Final_Project_P3_Table_h
#define Final_Project_P3_Table_h

#include "Vector.h"

#define Index(dim, row, column) dim * row + column

typedef struct _Table
{
	int dimensions;
	int numberOfPlayers;
	
	int *grid;
	
} Table;


Vector *GetFreePositions(Table table);

TPoint InvertIndex(int index, Table *table);


//
// Print to the file decriptor.
// If the file is NULL it will print to stdout
//
void PrintTable(Table *table, FILE *outputFile);

//
//	Releases allocated resourses
//
void DisposeTable(Table *table);

#endif
