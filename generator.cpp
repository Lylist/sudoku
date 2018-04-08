#include<iostream>
#include<stdlib.h>
#include<time.h> 
#include <cstdio>
using namespace std;
int Map[9][9];	//数独地图
int TransMap[9][9];  //用于变换的数独
int Raw[9][9];	//记录第i行出现的1-9
int Col[9][9];	//记录第j列出现的1-9
int B[9][9];	/*第i个九宫出现的1-9*/
int n;			//记录迭代次数
bool newsudu(int x);		//x 开始的位置，距离0的位置
void clearrandom(int* r);
int newrandom(int* r);
void coutsudu(int Sudoku_Map[][9]);
void Transform(int Col1, int Col2, int Raw1, int Raw2, int Number1, int Number2);
int main()
{
	freopen("xx.txt", "w", stdout);
	clock_t startTime, endTime;
	startTime = clock();
	srand((int)time(0));
	int t = 1000000;
	int num = 0;
	while (t)
	{
		if (num %1373 == 0)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					Map[i][j] = 0;
					Raw[i][j] = 0;
					Col[i][j] = 0;
					B[i][j] = 0;
				}
			}
			n = 1;
			Map[0][0] = 1;
			Raw[0][0] = 1;
			Col[0][0] = 1;
			B[0][0] = 1;
			newsudu(1);
			coutsudu(Map);
			num++;
			t--;
			continue;
		}
		for (int Col1 = 1; Col1 < 9; Col1++)
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
								cout << num << endl;
							}
						}
					}
				}
			}
		}
	}
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	cout << num << endl;
	//cout<<n<<endl;
	//getchar();
	return 0;
}
bool newsudu(int x)	//x 开始的位置，距离0的位置
{
	if (x == 81)
	{
		return true;
	}
	int r[9];		//用来随即生成1-9，且不能重复
	clearrandom(r);
	//开始往Map[i][j]插数据
	do
	{
		int num = newrandom(r);
		if (num == 0)	//不行了
		{
			//cout<<x<<endl;
			return false;
		}
		if (Raw[x / 9][num - 1] == 0 && Col[x % 9][num - 1] == 0 && B[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] == 0)
		{
			Raw[x / 9][num - 1] = 1;
			Col[x % 9][num - 1] = 1;
			B[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 1;
			Map[x / 9][x % 9] = num;
			n++;
			//coutsudu();
			if (newsudu(x + 1) == true)
			{
				return true;
			}
			Map[x / 9][x % 9] = 0;
			Raw[x / 9][num - 1] = 0;
			Col[x % 9][num - 1] = 0;
			B[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 0;
		}
	} while (1);
}
void coutsudu(int Sudoku_Map[][9])
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			printf("%d%c", Sudoku_Map[i][j], j == 8 ? '\n' : ' ');
		}
	}
	//cout<<"---------------------------------"<<endl;
	printf("\n");
}
void Transform(int Col1, int Col2, int Raw1, int Raw2, int Number1, int Number2)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (Map[i][j] == Number1) TransMap[i][j] = Number2;
			else if (Map[i][j] == Number2) TransMap[i][j] = Number1;
			else TransMap[i][j] = Map[i][j];
		}
	}
	for (int i = 0; i < 9; i++) swap(TransMap[i][Col1], TransMap[i][Col2]);
	for (int i = 0; i < 9; i++) swap(TransMap[Raw1][i], TransMap[Raw2][i]);
	coutsudu(TransMap);
}
void TransformNumber(int Number1, int Number2)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{	
			if (Map[i][j] == Number1) TransMap[i][j] = Number2;
			else if (Map[i][j] == Number2) TransMap[i][j] = Number1;
			else TransMap[i][j] = Map[i][j];
		}
	}
	coutsudu(TransMap);
}
void TransformCol(int Col1, int Col2)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == Col1) TransMap[i][j] = Map[i][Col2];
			else if (j == Col2) TransMap[i][j] = Map[i][Col1];
			else TransMap[i][j] = Map[i][j];
		}
	}
	coutsudu(TransMap);
}
void TransformRaw(int Raw1, int Raw2)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (i == Raw1) TransMap[i][j] = Map[Raw2][j];
			else if (i == Raw2) TransMap[i][j] = Map[Raw1][j];
			else TransMap[i][j] = Map[i][j];
		}
	}
	coutsudu(TransMap);
}
void clearrandom(int* r)
{
	for (int i = 0; i<9; i++)
	{
		r[i] = 0;
	}
}
int newrandom(int* r)	//1-9
{
	int num;
	do
	{
		num = rand() % 9;
		if (r[num] == 0)
		{
			r[num] = 1;
			return num + 1;
		}
		else
		{
			for (int i = 0; i<9; i++)
			{
				if (r[i] == 0)
				{
					r[i] = 1;
					return i + 1;
				}
			}
			return 0;
		}
	} while (1);
}
