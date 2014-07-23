//
//  WinnerMoveStrategy.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 7/22/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>

#include "WinnerMoveStrategy.h"

int Flip(Table * table, TPoint move)
{
	return 0;
}


TPoint WinnerMoveStrategy_Play(Table * table)
{
	Table * mTable = CopyTable(table);
	Vector * emptyCells = GetFreePositions(*mTable);
	
	TPoint p;
	int max = 0;
	
	for (int i = 0; i < emptyCells->count; i++)
	{
		TPoint move = emptyCells->values[i];
		
		int count = Flip(mTable, move);
		
		if (count > max)
		{
			p = move;
		}
	}
	
	DisposeVector(emptyCells);
	DisposeTable(mTable);
	
	return p;
}