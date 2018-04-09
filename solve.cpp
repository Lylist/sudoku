#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;
const int maxr = 729, maxc = 324;//表明该矩阵为729*324.
int r[maxc + maxr * 5 + 10], l[maxc + maxr * 5 + 10];
int u[maxc + maxr * 5 + 10], d[maxc + maxr * 5 + 10], head[10][10][10];
int row[maxc + maxr * 5 + 10], map[10][10], ans[100], c[maxc + maxr * 5 + 10], s[maxc + 10], top = 0;

void node(int c1, int cnt)//找到对应关系
{
	u[d[c1]] = cnt;
	d[cnt] = d[c1];
	u[cnt] = c1;
	d[c1] = cnt;
	s[c1]++;
	c[cnt] = c1;
}
void init()   //初始化
{
	memset(s, 0, sizeof(s));
	memset(head, 0, sizeof(head));
	top = 0;
	for (int i = 0; i <= maxc + maxr * 5; i++)
	{
		r[i] = 0; l[i] = 0; u[i] = 0; d[i] = 0; c[i] = 0; row[i] = 0;
	}
	for (int i = 0; i <= maxc; i++)
	{
		s[i] = 0; l[i] = i - 1; r[i] = i + 1; u[i] = d[i] = i; c[i] = 0;
	}
	l[0] = maxc; r[maxc] = 0;
	int cnt = maxc;
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
				node((i - 1) * 9 + j, cnt + 1);
				node(81 + (k - 1) * 27 + i, cnt + 2);
				node(81 + (k - 1) * 27 + 9 + j, cnt + 3);
				node(81 + (k - 1) * 27 + 18 + (j - 1) / 3 + 1 + ((i - 1) / 3) * 3, cnt + 4);
				cnt += 4;
			}    //建立原始矩阵（只是一种对应关系）
	for (int i = 0; i < 100; i++) ans[i] = 0;
}
void remove(int c1)//将c1列去掉。并且将相应行也去掉。
{
	l[r[c1]] = l[c1]; r[l[c1]] = r[c1];
	for (int i = d[c1]; i != c1; i = d[i])
		for (int j = r[i]; j != i; j = r[j])
		{
			u[d[j]] = u[j];
			d[u[j]] = d[j];
			s[c[j]]--;
		}
}

void resume(int c1)//将c1列恢复，并将相应行恢复。记得顺序！！！！之前是d-r，现在是u-l。
{
	for (int i = u[c1]; i != c1; i = u[i])
		for (int j = l[i]; j != i; j = l[j])
		{
			u[d[j]] = j;
			d[u[j]] = j;
			s[c[j]]++;
		}
	l[r[c1]] = c1;
	r[l[c1]] = c1;
}
bool dfs(int k)
{
	//printf("%d\n", k);
	//if (k>81) return true;
	if (r[0] == 0) return true;
	int c1, minnum = 10000000;
	for (int i = r[0]; i != 0; i = r[i])
	{
		if (!s[i]) return false;
		if (s[i]<minnum)
		{
			minnum = s[i]; c1 = i;
		}
	}
	remove(c1);
	for (int i = d[c1]; i != c1; i = d[i])
	{
		ans[k] = row[i];
		for (int j = r[i]; j != i; j = r[j])
			remove(c[j]);
		if (dfs(k + 1)) return true;
		for (int j = l[i]; j != i; j = l[j])
			resume(c[j]);
	}
	resume(c1);
	return false;
}
void print()    //输出一个满足的解
{
	int x, y, num;
	for (int i = 1; i <= 81; i++)
	{
		num = (ans[i] - 1) / 81 + 1;
		x = (ans[i] - (num - 1) * 81 - 1) / 9 + 1;
		y = ans[i] - (num - 1) * 81 - (x - 1) * 9;
		map[x][y] = num;
	}
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			printf("%d%c", map[i][j], j == 9 ? '\n' : ' ');
		}
	}
	printf("\n");
}
int main()
{
	freopen("test1.txt", "r", stdin);
	freopen("test.out", "w", stdout);
	/*计时器*/
	clock_t startTime, endTime;
	startTime = clock();
	int t;
	while (scanf("%d", &map[1][1]) != EOF)
	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (i == 1 && j == 1) continue;
				scanf("%d", &map[i][j]);
			}
		}
		init();//初始化；
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++)
				if (map[i][j])   //将已经存在的元素在矩阵中去掉，就是删除并记录相应的行与列
				{
					top++;
					ans[top] = row[head[i][j][map[i][j]]];
					remove(c[head[i][j][map[i][j]]]);
					for (int u = r[head[i][j][map[i][j]]]; u != head[i][j][map[i][j]]; u = r[u])
						remove(c[u]);
				}
		bool anss;
		anss=dfs(top + 1);//我们一共要填入81个数，但因为已经给了top个数，所以只需要搜索剩下的即可
		if (anss == true) print();
		else printf("No solution\n");
	}
	/*计时器*/
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}