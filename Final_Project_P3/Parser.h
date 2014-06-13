//
//  Parser.h
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/12/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#ifndef Final_Project_P3_Parser_h
#define Final_Project_P3_Parser_h

#define Index(row, column) GetDimensions() * row + column

int **ParseInputText(char *input);

int GetDimensions();

int GetNumberOfPlayers();

int HasTableBeenInitialized();

int **GetGrid();

#endif
