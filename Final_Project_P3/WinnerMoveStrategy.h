//
//  WinnerMoveStrategy.h
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 7/22/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#ifndef Final_Project_P3_WinnerMoveStrategy_h
#define Final_Project_P3_WinnerMoveStrategy_h

#include "Vector.h"
#include "Table.h"

TPoint WinnerMoveStrategy_Play(Table * table, Vector * emptyCells, int playerId);

#endif
