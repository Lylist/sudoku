#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include "sudoku.h"
using namespace std;
int Map[9][9];	//数独地图
int TransMap[9][9];  //用于变换的数独
int Raw[9][9];	//记录第i行出现的1-9
int Col[9][9];	//记录第j列出现的1-9
int Palace[9][9];	/*第i个九宫出现的1-9*/
int n;			//记录迭代次数

bool New_Sudoku(int x);		//x 开始的位置，距离0的位置
void Clear_Random(int* r);   //清空随机数组
int Generator_Random(int* r);     //随机生成
void Print_Map(int Sudoku_Map[][9]); //输出终局
void Transform(int Col1, int Col2, int Raw1, int Raw2, int Number1, int Number2);   //通过变换生成新的终局

int read(char str[])
{
	int Number = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i]<'0' || str[i]>'9') return -1;
		Number = Number * 10 + str[i] - '0';
	}
	if (Number < 1 || Number>1000000) return -1;
	return Number;
}
int Generator_Sudoku(int t)
{
	freopen("sudoku.txt", "w", stdout);
	/*计时器
	clock_t startTime, endTime;
	startTime = clock();*/
	srand((int)time(0));
	int num = 0;
	while (t)
	{
		if (num %1373 == 0)               //一个种子终局可以产生1373个变换终局
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					Map[i][j] = 0;
					Raw[i][j] = 0;
					Col[i][j] = 0;
					Palace[i][j] = 0;
				}
			}
			n = 1;
			Map[0][0] = 1;
			Raw[0][0] = 1;
			Col[0][0] = 1;
			Palace[0][0] = 1;
			New_Sudoku(1);
			Print_Map(Map);
			num++;
			t--;
			continue;
		}
		for (int Col1 = 1; Col1 < 9; Col1++)   //先变换列，在变换行，再交换数字
		{
			if (t == 0) break;
			int UP_Col = Col1 / 3 * 3 + 2;
			for (int Col2 = Col1 + 1; Col2 <= UP_Col; Col2++)
			{
				if (t == 0) break;
				for (int Raw1 = 1; Raw1 < 9; Raw1++)
				{
					if (t == 0) break;
					int UP_Raw = Raw1 / 3 * 3 + 2;
					for (int Raw2 = Raw1 + 1; Raw2 <= UP_Raw; Raw2++)
					{
						if (t == 0) break;
						for (int Number1 = 2; Number1 <= 9; Number1++)
						{
							if (t == 0) break;
							for (int Number2 = Number1 + 1; Number2 <= 9; Number2++)
							{
								if (t == 0) break;
								Transform(Col1, Col2, Raw1, Raw2, Number1, Number2);
								num++;
								t--;
							}
						}
					}
				}
			}
		}
	}
	/*计时器
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;*/
	return 0;
}
bool New_Sudoku(int x)	//x为当前的位置
{
	if (x == 81) return true;
	int RandomRaw[9];		//用来随即生成1-9
	Clear_Random(RandomRaw);
	//开始往Map[i][j]插数据
	do
	{
		int num = Generator_Random(RandomRaw);
		//出现矛盾
		if (num == 0) return false;
		if (Raw[x / 9][num - 1] == 0 && Col[x % 9][num - 1] == 0 && Palace[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] == 0)
		{
			Raw[x / 9][num - 1] = 1;
			Col[x % 9][num - 1] = 1;
			Palace[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 1;
			Map[x / 9][x % 9] = num;
			n++;
			if (New_Sudoku(x + 1) == 1) return 1;
			//回溯
			Map[x / 9][x % 9] = 0;
			Raw[x / 9][num - 1] = 0;
			Col[x % 9][num - 1] = 0;
			Palace[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 0;
		}
	} while (1);
}
void Print_Map(int Sudoku_Map[][9])
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			putchar(Map[i][j] + '0');
			if (j != 8) putchar(' ');
		}
	}
	putchar('\n');
}
void Transform(int Col1, int Col2, int Raw1, int Raw2, int Number1, int Number2)
{
	for (int i = 0; i < 9; i++)    //交换数字
	{
		for (int j = 0; j < 9; j++)
		{
			if (Map[i][j] == Number1) TransMap[i][j] = Number2;
			else if (Map[i][j] == Number2) TransMap[i][j] = Number1;
			else TransMap[i][j] = Map[i][j];
		}
	}
	//交换列
	for (int i = 0; i < 9; i++) swap(TransMap[i][Col1], TransMap[i][Col2]);
	//交换行
	for (int i = 0; i < 9; i++) swap(TransMap[Raw1][i], TransMap[Raw2][i]);
	Print_Map(TransMap);
}
void Clear_Random(int* RandomRaw)
{
	for (int i = 0; i<9; i++) RandomRaw[i] = 0;
}
int Generator_Random(int* RandomRaw)	//1-9随机生成
{
	int num;
	num = rand() % 9;
	if (RandomRaw[num] == 0)
	{
		RandomRaw[num] = 1;
		return num + 1;
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			if (RandomRaw[i] == 0)
			{
				RandomRaw[i] = 1;
				return i + 1;
			}
		}
		return 0;
	}
}
