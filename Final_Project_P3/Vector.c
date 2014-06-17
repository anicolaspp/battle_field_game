//
//  Vector.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>

#include "Vector.h"


Vector *GetVector(int size)
{
	Vector *v = malloc(sizeof(Vector));
	v->values = malloc(sizeof(int) * size);
	v->capacity = size;
	v->count = 0;
	
	return v;
}

void DesposeVector(Vector v)
{
	if (v.values != NULL)
	{
		free(v.values);
	}
}