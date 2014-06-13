//
//  main.c
//  Final_Project_P3
//
//  Created by Nicolas A Perez on 6/12/14.
//  Copyright (c) 2014 Nicolas A Perez. All rights reserved.
//

#include <stdio.h>
#include "Parser.h"

int main(int argc, const char * argv[])
{

	char * input = "3 3\n1 2 0\n0 2 0\n3 0 0";
	
	int **parsedData = ParseInputText(input);
	
	// insert code here...
	printf("Hello, World!\n");
    return 0;
	
	
}

