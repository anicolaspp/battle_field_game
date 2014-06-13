//
//  Table.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/13/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "Table.h"


void Dispose(Table table)
{
	if (table.dimensions > 0)
	{
		free(table.grid);
	}
}