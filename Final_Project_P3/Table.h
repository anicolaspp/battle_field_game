//
//  Table.h
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#ifndef Final_Project_P3_Table_h
#define Final_Project_P3_Table_h

#define Index(dim, row, column) dim * row + column

typedef struct _Table
{
	int dimensions;
	int numberOfPlayers;
	
	int **grid;
	
} Table;

void PrintTable(Table  table);

void Dispose(Table *table);

#endif
