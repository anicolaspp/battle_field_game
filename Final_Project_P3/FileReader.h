//
//  FileReader.h
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#ifndef Final_Project_P3_FileReader_h
#define Final_Project_P3_FileReader_h


typedef struct
{
	int dimensions;
	int numberOfPlayers;
	
	int **grid;
	
} Table;

Table * ReadTableFromFile(char *fileName);

void WriteTableToFile(Table *table, char *fileName);


#endif
