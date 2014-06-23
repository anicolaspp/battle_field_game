//
//  RandomMoveStrategy.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <time.h>


#include "RandomMoveStrategy.h"



TPoint RandomMoveStrategy_Play(Vector *vector)
{
	if (vector->count > 0)
	{
		// Need a random position here
		
		srand((unsigned)time(NULL));
		
		int position = rand() % vector->count;
		
		return vector->values[position];
	}
	
	TPoint p;
	p.X = -1;
	p.Y = -1;
	
	return p;
}