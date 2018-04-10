#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "sudoku.h"
using namespace std;
const int MAXR = 729, MAXC = 324;//表明该矩阵为729*324.
int r[MAXC + MAXR * 5 + 10], l[MAXC + MAXR * 5 + 10];
int u[MAXC + MAXR * 5 + 10], d[MAXC + MAXR * 5 + 10], head[10][10][10];
int row[MAXC + MAXR * 5 + 10], Map[10][10], ans[100], c[MAXC + MAXR * 5 + 10], s[MAXC + 10], top = 0;

inline void Init(void);	//初始化
inline void Correspondence(int Col1, int cnt);	//找到对应关系
inline void Remove(int Col1);	//将Col1列去掉。并且将相应行也去掉。
inline void Resume(int Col1);	//将Col1列恢复，并将相应行恢复。记得顺序！！！
inline bool dfs(int now);	
inline void print(void);    //输出一个满足的解
inline bool Read_Number(int &num);	//快速读入函数

int Solve_Sudoku(char File[])
{
	freopen(File, "r", stdin);
	freopen("sudoku.txt", "w", stdout);
	/*计时器
	clock_t startTime, endTime;
	startTime = clock();*/
	int t = 0;
	while (Read_Number(Map[1][1])==true)
	{
		//printf("%d\n", ++t);
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (i == 1 && j == 1) continue;
				Read_Number(Map[i][j]);
			//	printf("%d ", Map[i][j]);
			}
			//printf("\n");
		}
		//printf("\n");
		Init();//初始化；
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++)
				if (Map[i][j])   //将已经存在的元素在矩阵中去掉，就是删除并记录相应的行与列
				{
					top++;
					ans[top] = row[head[i][j][Map[i][j]]];
					Remove(c[head[i][j][Map[i][j]]]);
					for (int u = r[head[i][j][Map[i][j]]]; u != head[i][j][Map[i][j]]; u = r[u])
						Remove(c[u]);
				}
		bool ok;
		ok=dfs(top + 1);	//只需要搜索剩下的即可
		if (ok == true) print();
		else printf("No solution\n");
	}
	/*计时器
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;*/
	return 0;
}

inline bool Read_Number(int &num)
{
	char in; 
	bool IsN = false;
	in = getchar();
	if (in == EOF) return false;
	while (in != '-' && (in<'0' || in>'9'))
	{
		in = getchar();
		if (in == EOF) return false;
	}
	if (in == '-') { IsN = true; num = 0; }
	else num = in - '0';
	while (in = getchar(), in >= '0'&&in <= '9') {
		num *= 10, num += in - '0';
	}
	if (IsN) num = -num;
	return true;
}

inline void Init()   //初始化
{
	top = 0;
	for (int i = 0; i <= MAXC + MAXR * 5; i++)
	{
		r[i] = 0; l[i] = 0; u[i] = 0; d[i] = 0; c[i] = 0; row[i] = 0;
	}
	for (int i = 0; i <= MAXC; i++)
	{
		s[i] = 0; l[i] = i - 1; r[i] = i + 1; u[i] = d[i] = i; c[i] = 0;
	}
	l[0] = MAXC; r[MAXC] = 0;
	int cnt = MAXC;
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			for (int k = 1; k <= 9; k++)
			{
				for (int u = 1; u <= 4; u++)
				{
					l[cnt + u] = cnt + u - 1;
					r[cnt + u] = cnt + u + 1;
					row[cnt + u] = 81 * (k - 1) + (i - 1) * 9 + j;
				}
				l[cnt + 1] = cnt + 4; r[cnt + 4] = cnt + 1;
				head[i][j][k] = cnt + 1;
				Correspondence((i - 1) * 9 + j, cnt + 1);
				Correspondence(81 + (k - 1) * 27 + i, cnt + 2);
				Correspondence(81 + (k - 1) * 27 + 9 + j, cnt + 3);
				Correspondence(81 + (k - 1) * 27 + 18 + (j - 1) / 3 + 1 + ((i - 1) / 3) * 3, cnt + 4);
				cnt += 4;
			}    //建立原始矩阵（只是一种对应关系）
	for (int i = 0; i < 100; i++) ans[i] = 0;
}

inline void Correspondence(int Col1, int cnt)//找到对应关系
{
	u[d[Col1]] = cnt;
	d[cnt] = d[Col1];
	u[cnt] = Col1;
	d[Col1] = cnt;
	s[Col1]++;
	c[cnt] = Col1;
}

inline void Remove(int Col1)//将Col1列去掉。并且将相应行也去掉。
{
	l[r[Col1]] = l[Col1]; r[l[Col1]] = r[Col1];
	for (int i = d[Col1]; i != Col1; i = d[i])
		for (int j = r[i]; j != i; j = r[j])
		{
			u[d[j]] = u[j];
			d[u[j]] = d[j];
			s[c[j]]--;
		}
}

inline void Resume(int Col1)//将Col1列恢复，并将相应行恢复。记得顺序！！！！之前是d-r，现在是u-l。
{
	for (int i = u[Col1]; i != Col1; i = u[i])
		for (int j = l[i]; j != i; j = l[j])
		{
			u[d[j]] = j;
			d[u[j]] = j;
			s[c[j]]++;
		}
	l[r[Col1]] = Col1;
	r[l[Col1]] = Col1;
}
inline bool dfs(int now)
{
	//if (k>81) return true;
	if (r[0] == 0) return true;
	int Col1, minnum = 10000000;
	for (int i = r[0]; i != 0; i = r[i])
	{
		if (!s[i]) return false;
		if (s[i]<minnum)
		{
			minnum = s[i]; Col1 = i;
		}
	}
	Remove(Col1);
	for (int i = d[Col1]; i != Col1; i = d[i])
	{
		ans[now] = row[i];
		for (int j = r[i]; j != i; j = r[j])
			Remove(c[j]);
		if (dfs(now + 1)) return true;
		for (int j = l[i]; j != i; j = l[j])
			Resume(c[j]);
	}
	Resume(Col1);
	return false;
}
inline void print()    //输出一个满足的解
{
	int x, y, num;
	for (int i = 1; i <= 81; i++)
	{
		num = (ans[i] - 1) / 81 + 1;
		x = (ans[i] - (num - 1) * 81 - 1) / 9 + 1;
		y = ans[i] - (num - 1) * 81 - (x - 1) * 9;
		Map[x][y] = num;
	}
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			putchar(Map[i][j] + '0');
			if (j != 9) putchar(' ');
		}
		putchar('\n');
	}
	putchar('\n');
}
