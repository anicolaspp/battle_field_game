//
//  WinnerMoveStrategy.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 7/22/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>

#include "WinnerMoveStrategy.h"

int Flip(Table * table, TPoint move, int playerId)
{
		//TODO: flip the table using the playerId and return how many I win
		//TODO: I don't need to "flip" the table, but only count how many are fliped
	
	return 0;
}


TPoint WinnerMoveStrategy_Play(Table * table, int playerId)
{
	Table * mTable = CopyTable(table);
	Vector * emptyCells = GetFreePositions(*table);
	
	TPoint p;
	int max = 0;
	
	for (int i = 0; i < emptyCells->count; i++)
	{
		TPoint move = emptyCells->values[i];
		
		int count = Flip(mTable, move, playerId);
		
		if (count > max)
		{
			p = move;
		}
	}
	
	DisposeVector(emptyCells);
	DisposeTable(mTable);
	
	return p;
}