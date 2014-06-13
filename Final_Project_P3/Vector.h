//
//  Vector.h
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#ifndef Final_Project_P3_Vector_h
#define Final_Project_P3_Vector_h

#include <stdio.h>
#include <stdlib.h>

typedef struct _Vector
{
	int *values;
	int count;
	
	
} Vector;


void Add(Vector vector, int value);

Vector GetVector(int size);

DisposeVector(Vector v);

#endif
