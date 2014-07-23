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
#include "Point.h"

typedef struct _Vector
{
	TPoint *values;
	int count;
	int capacity;
	
} Vector;

Vector *GetVector(int size);

void DisposeVector(Vector * vector);

#endif
