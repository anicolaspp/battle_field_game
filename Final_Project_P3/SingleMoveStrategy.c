//
//  SingleMoveStrategy.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>

#include "SingleMoveStrategy.h"


TPoint SingleMoveStrategy_Play(Vector *vector)
{
	if (vector->count > 0)
	{	
		return vector->values[0];
	}
	
	TPoint p;
	p.X = -1;
	p.Y = -1;
	
	return p;
}