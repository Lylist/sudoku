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

//初始化使用的临时数组
int r2[MAXC + MAXR * 5 + 10], l2[MAXC + MAXR * 5 + 10];
int u2[MAXC + MAXR * 5 + 10], d2[MAXC + MAXR * 5 + 10], head2[10][10][10];
int row2[MAXC + MAXR * 5 + 10], ans2[100], c2[MAXC + MAXR * 5 + 10], s2[MAXC + 10];

inline void Init(void);	//初始化
inline void Correspondence(int Col1, int cnt);	//找到对应关系
inline void Remove(int Col1);	//将Col1列去掉。并且将相应行也去掉。
inline void Resume(int Col1);	//将Col1列恢复，并将相应行恢复。记得顺序！！！
inline bool dfs(int now);	
inline void print(void);    //输出一个满足的解
inline bool Read_Number(int &num);	//快速读入函数
inline void init();

int Solve_Sudoku(char File[])
{
	freopen(File, "r", stdin);
	freopen("sudoku.tex", "w", stdout);
	/*计时器
	clock_t startTime, endTime;
	startTime = clock();*/
	init();
	while (Read_Number(Map[1][1])==true)
	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (i == 1 && j == 1) continue;
				Read_Number(Map[i][j]);
			}
		}
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

inline void Init()
{
	top = 0;
	for (int i = 0; i <= MAXC + MAXR * 5; i++)
	{
		r[i] = r2[i]; l[i] = l2[i];
		u[i] = u2[i]; d[i] = d2[i];
		c[i] = c2[i]; row[i] = row2[i];
	}
	for (int i = 0; i <= MAXC; i++)
	{
		s[i] = s2[i];
	}
	for (int i = 0; i < 90; i++) ans[i] = 0;
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			for (int k = 1; k <= 9; k++)
			{
				head[i][j][k] = head2[i][j][k];
			}
}

inline void init()   //初始化
{
	top = 0;
	for (int i = 0; i <= MAXC + MAXR * 5; i++)
	{
		r2[i] = 0; l2[i] = 0; u2[i] = 0; d2[i] = 0; c2[i] = 0; row2[i] = 0;
	}
	for (int i = 0; i <= MAXC; i++)
	{
		s2[i] = 0; l2[i] = i - 1; r2[i] = i + 1; u2[i] = d2[i] = i; c2[i] = 0;
	}
	l2[0] = MAXC; r2[MAXC] = 0;
	int cnt = MAXC;
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			for (int k = 1; k <= 9; k++)
			{
				for (int u = 1; u <= 4; u++)
				{
					l2[cnt + u] = cnt + u - 1;
					r2[cnt + u] = cnt + u + 1;
					row2[cnt + u] = 81 * (k - 1) + (i - 1) * 9 + j;
				}
				l2[cnt + 1] = cnt + 4; r2[cnt + 4] = cnt + 1;
				head2[i][j][k] = cnt + 1;
				Correspondence((i - 1) * 9 + j, cnt + 1);
				Correspondence(81 + (k - 1) * 27 + i, cnt + 2);
				Correspondence(81 + (k - 1) * 27 + 9 + j, cnt + 3);
				Correspondence(81 + (k - 1) * 27 + 18 + (j - 1) / 3 + 1 + ((i - 1) / 3) * 3, cnt + 4);
				cnt += 4;
			}    //建立原始矩阵（只是一种对应关系）
	for (int i = 0; i < 100; i++) ans2[i] = 0;
}

inline void Correspondence(int Col1, int cnt)//找到对应关系
{
	u2[d2[Col1]] = cnt;
	d2[cnt] = d2[Col1];
	u2[cnt] = Col1;
	d2[Col1] = cnt;
	s2[Col1]++;
	c2[cnt] = Col1;
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
	if (r[0] == 0) return true;
	int Col1, minnum = 10000000;
	for (int i = r[0]; i != 0; i = r[i])
	{
		if (s[i] == 0) return false;
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
