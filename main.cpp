#include <cstdio>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include "sudoku.h"

//extern int Generator_Sukodu(int t);

int main(int argc, char *argv[])
{
	if (argc < 2)  
	{
		printf("Plwase use the parameters\n");
		return 0;
	}
	else if (strcmp(argv[1], "-c") == 0) //生成 
	{
		int NumDudoku = read(argv[2]);  //参数错误 
		if (NumDudoku != -1)
		{
			
			Generator_Sudoku(NumDudoku);
		}
		else printf("Please enter the number in 1-1000000\n");
	}
	else if (strcmp(argv[1], "-s") == 0)  //求解 
	{
		Solve_Sudoku(argv[2]);
	}
	else printf("Please use ture command\n");
	return 0;
}
