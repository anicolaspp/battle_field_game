//
//  Table.h
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#ifndef Final_Project_P3_Table_h
#define Final_Project_P3_Table_h

#define Index(row, column) GetDimensions() * row + column

typedef struct
{
	int dimensions;
	int numberOfPlayers;
	
	int **grid;
	
} Table;

void Dispose(Table table);

#endif
