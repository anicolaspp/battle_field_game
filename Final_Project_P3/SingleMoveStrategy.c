//
//  SingleMoveStrategy.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>

#include "SingleMoveStrategy.h"


int SingleMoveStrategy_Play(Vector *vector)
{
	if (vector->count > 0)
	{
		return vector->values[0];
	}
	
	return -1;
}