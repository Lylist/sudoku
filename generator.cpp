#include<iostream>
#include<stdlib.h>
#include<time.h> 
using namespace std;
int map[9][9];	//������ͼ
int I[9][9];	//��¼��i�г��ֵ�1-9
int J[9][9];	//��¼��j�г��ֵ�1-9
int B[9][9];	/*��i���Ź����ֵ�1-9	0 1 2
				3 4 5
				6 7 8*/
int n;			//��¼��������
bool newsudu(int x);		//x ��ʼ��λ�ã�����0��λ��
void clearrandom(int* r);
int newrandom(int* r);
void coutsudu(void);
int main()
{
	srand((unsigned)time(0));
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			map[i][j] = 0;
			I[i][j] = 0;
			J[i][j] = 0;
			B[i][j] = 0;
		}
	}
	n = 0;

	newsudu(0);
	coutsudu();
	//cout << n << endl;
	getchar();
	return 0;
}
bool newsudu(int x)	//x ��ʼ��λ�ã�����0��λ��
{
	if (x == 81)
	{
		return true;
	}
	int r[9];		//�����漴����1-9���Ҳ����ظ�
	clearrandom(r);
	//��ʼ��map[i][j]������
	do
	{
		int num = newrandom(r);
		if (num == 0)	//������
		{
			//cout<<x<<endl;
			return false;
		}
		if (I[x / 9][num - 1] == 0 && J[x % 9][num - 1] == 0 && B[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] == 0)
		{
			I[x / 9][num - 1] = 1;
			J[x % 9][num - 1] = 1;
			B[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 1;
			map[x / 9][x % 9] = num;
			n++;
			//coutsudu();
			if (newsudu(x + 1) == true)
			{
				return true;
			}
			map[x / 9][x % 9] = 0;
			I[x / 9][num - 1] = 0;
			J[x % 9][num - 1] = 0;
			B[((x / 9) / 3) * 3 + (x % 9 / 3)][num - 1] = 0;
		}
	} while (1);
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
	cout << "---------------------------------" << endl;
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