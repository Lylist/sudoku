/*学号1120161945*/
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <cstring>
#include <cstdio>
using namespace std;
int map[9][9];	//数独地图
int Row[9][9];	//记录第i行出现的1-9
int Col[9][9];	//记录第j列出现的1-9
int Palace[9][9];	/*第i个九宫出现的1-9*/
int n;			//记录迭代次数
bool newsudu(int x);		//x 开始的位置，距离0的位置
void clearrandom(int* r);   //初始化
int newrandom(int* r);    //随机生成棋盘
void coutsudu(void);      //棋盘输出
int main()
{
	freopen("sudoku.txt", "w", stdout);
	srand((int)time(0));

	int t = 20;
	while (t--)
	{
		memset(Col,0,sizeof(Col));          //棋盘初始化 
		memset(Row,0,sizeof(Row));
		memset(Palace,0,sizeof(Palace));
		memset(map,0,sizeof(map));
		n = 1;

		map[0][0] = 1;
		Row[0][0] = 1;
		Col[0][0] = 1;
		newsudu(1);
		coutsudu();
	}
	
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
	//开始往map[i][j]插数据
	while(1)
	{
		int num = newrandom(r);
		if (num == 0)	//不行了
		{
			return false;
		}
		if (Row[x / 9][num - 1] == 0 && Col[x % 9][num - 1] == 0 && Palace[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] == 0)
		{
			Row[x / 9][num - 1] = 1;
			Col[x % 9][num - 1] = 1;
			Palace[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 1;
			map[x / 9][x % 9] = num;
			n++;
			if (newsudu(x + 1) == true)
			{
				return true;
			}
			map[x / 9][x % 9] = 0;
			Row[x / 9][num - 1] = 0;
			Col[x % 9][num - 1] = 0;
			Palace[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 0;
		}
	}
}
void coutsudu(void)
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			cout << map[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}
void clearrandom(int* r)
{
	memset(r, 0, 9 * sizeof(int));
}
int newrandom(int* r)	//1-9
{
	int num;
	num = rand() % 9;
	if (r[num] == 0)
	{
		r[num] = 1;
		return num + 1;
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			if (r[i] == 0)
			{
				r[i] = 1;
				return i + 1;
			}
		}
	}
	return 0;
}
