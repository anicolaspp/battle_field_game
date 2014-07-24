//
//  WinnerMoveStrategy.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 7/22/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>

#include "WinnerMoveStrategy.h"
#include "Table.h"
#include "RandomMoveStrategy.h"

int Flip(Table * table, TPoint move, int playerId)
{
		//TODO: flip the table using the playerId and return how many I win
		//TODO: I don't need to "flip" the table, but only count how many are fliped
    
  //  printf("Dimensions: %d\n", table->dimensions);
    
    int sum = 0;
    
    for (int i = 0; i < move.X; i++)
    {
        if (table->grid[Index(table->dimensions, i, move.Y)] == playerId)
        {
            sum += move.X - i;
            break;
        }
    }
    
    for (int i = table->dimensions; i > move.X; i--)
    {
        if (table->grid[Index(table->dimensions, i, move.Y)] == playerId)
        {
            sum += i - move.X;
            break;
        }
    }
    
    for (int i = 0; i < move.Y; i++)
    {
        if (table->grid[Index(table->dimensions, move.X, i)] == playerId)
        {
            sum += move.Y - i;
            break;
        }
    }
    
    for (int i = table->dimensions; i > move.Y; i--)
    {
        if (table->grid[Index(table->dimensions, move.X, i)] == playerId)
        {
            sum += i - move.Y;
        }
    }
    
	return sum;
}


TPoint WinnerMoveStrategy_Play(Table * table, Vector * emptyCells, int playerId)
{
	TPoint p;
	int max = 0;
    
//    
//    for (int i = 0; i < emptyCells->count; i++)
//    {
//        printf("[%d, %d] ", emptyCells->values[i].X, emptyCells->values[i].Y);
//    }
    
    printf("\n");
    
	
	for (int i = 0; i < emptyCells->count; i++)
	{
		TPoint move = emptyCells->values[i];
		
		int count = Flip(table, move, playerId);
		
		if (count > max)
		{
			p = move;
            max = count;
		}
	}
    
    if (max == 0)
    {
        p = RandomMoveStrategy_Play(emptyCells);
    }
    
	return p;
}