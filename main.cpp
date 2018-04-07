#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
class CSudoku
{
	int map[9][9];
	int smod;
	int solves;
	int check(int,int,int*);
	void dfs();
public:
	enum{ANY=0,ALL=1};
	CSudoku(int n=40);// �����������,nԽ��Խ��
	void display();// ��ʾ����
	int resolve(int mod=ALL);// ������
	CSudoku(int *data);// �˹�ָ������
	
};

CSudoku::CSudoku(int n)
{
	int i,j;
	srand(time(0));
	do
	{
		for(i=0;i<9;++i)
		{
			for(j=0;j<9;++j)
				map[i][j]=0;//��i������0
			j=rand()%9;//jȡ0��8�������
			map[i][j]=i+1;//��1�������һ����1����2����2...��9����9����Ϊ��Ĳ�һ������������Ҳ��Ҫ����
			//ʣ�µ���resolve��
		}
	}while(!resolve(ANY));//û���˾���ѭ��һ��,��ʵ�ⲽ�������������������õľ��Ǵ�ANY��resolve
	
	// �ڿ���
	for(int k=0;k<n;)//n represent the number of blank, the position of 0 is random
	{
		i=rand()%81;//i=0~80
		j=i%9;//j=0~8
		i=i/9;//i=0~8
		if(map[i][j]>0)
		{
			map[i][j]=0;
			++k;
		}
		
	}
	cout<<"randomized sudoku created with "<<n<<" blanks"<<endl;
}
CSudoku::CSudoku(int *data)
{
	int *pm=(int*)map;
	for(int i=0;i<81;++i)
		pm[i]=data[i];
}

void CSudoku::display()
{
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<9;++j)
		{
			if(map[i][j]>0)
				cout<<map[i][j]<<" ";
			else
				cout<<"  ";
		}
		cout<<"\n";
	}
}
int CSudoku::resolve(int mod)//enum all, any
{
	smod=mod;
	
    if(mod==ALL)//all�����ѳ�ȫ���⣬��ʼ�⣬any�����ѳ���һ���⣬oly���ҳ�Ψһһ����
		
	{
		solves=0;
		dfs();
		return solves;
	}
	else if(mod==ANY)//�������Ǹ�����
	{
		try
		{
			dfs();
			return 0;//������˼��һֱûִ�е�����ɹ�����ô���c==0��������һ��dfs()��һֱ����������Ϊ
			//return 0;���˳����еݹ飬ֻ�˳�һ���ݹ�
		}
		catch(int)
		{
			return 1;//���ˣ�ִ�е�im=-1�ͱ�ʾ����ɹ���
		}
	}
	return 0;
}
int CSudoku::check(int x,int y,int *mark)
{
	int i,j,is,js,count=0;//map[x][y]=0
	for(i=1;i<=9;++i)
		mark[i]=0;//��仰����Ҫ���Ȱ�ԭ���ı�Ƕ�����
	for(i=0;i<9;++i)
		mark[map[x][i]]=1;//��ʾx�����г��ֹ���Ԫ�ض���������
	for(i=0;i<9;++i)
		mark[map[i][y]]=1;
	is=x/3*3;
	js=y/3*3;
	for(i=0;i<3;++i)
	{
		for(j=0;j<3;++j)
			mark[map[is+i][js+j]]=1;
	}
	for(i=1;i<=9;++i)
		if(mark[i]==0)
			count++;
		return count;
}
void CSudoku::dfs()
{
	int i,j,im=-1,jm,min=10;
	int mark[10];
	for(i=0;i<9;++i)
	{
		for(j=0;j<9;++j)
		{
			if(map[i][j])
				continue;
			int c=check(i,j,mark);
			if(c==0)
				return;//�˳�������������ص������ĺ���
			if(c<min)//������ɶ�һ���Ͳ�����
			{
				im=i;
				jm=j;
				min=c;
			}
		}
	}
	if(im==-1)
	{
		if(smod==ALL)//�ѵ����н��ֹͣ
		{
			cout<<"No."<<++solves<<endl;
			display();
			return;//
		}
		
		
		else if(smod==ANY) //�ѵ�һ�����ֹͣ 
		{
			
			throw(1);
		}
	}
	check(im,jm,mark);//count����С�����ԣ���ʱ���±��һ�飬��Ϊѭ��������ǵĻ���һ�����ĸ��أ�
	//����ã�9��9���ı�ǣ��϶��������ֽ⣬��Ϊû������������~
	/*���i����ѡ���������ȥ��Ȼ��ʼ�⣬Ȼ���ٵ�����������һ�Σ����ҵ�����ʵĽ⣬
	���������ֿ����ԣ�������1��Ȼ����c==0�ˣ��˳�������������ص������ĺ�����Ҳ����forѭ��,��ʱ
	����������ܵ�ֵ����Ϊ��Ļ������һ���ո����Բ���Ҳ��*/
	for(i=1;i<=9;++i)
	{
		if(mark[i]==0)
		{
			map[im][jm]=i;
			dfs();
		}
	}
	map[im][jm]=0;//�ѸղŸ���ֵ�Ŀո������������������Ϊdfs()һֱ�ڵ����������Է���ʱҲ�����
	//����仰���������
}

#include <iostream>
//#include "sudoku.h"
using namespace std;
int main()
{
	int data1[]=
	{4,9,0,0,0,0,0,2,7,
	5,0,0,0,1,0,0,0,4,
	6,0,0,0,0,8,0,0,3,
	1,0,4,0,0,0,0,0,0,
	0,6,0,0,0,0,0,5,0,
	0,0,0,0,0,0,2,0,8,
	7,0,0,2,0,0,0,0,5,
	8,0,0,0,9,0,0,0,1,
	3,4,0,5,0,0,0,6,2
	};
	CSudoku s(data1); 
	s.display();
	s.resolve();
	/*CSudoku s1();
	s1.display();
	s1.resolve();*/
	return 0;
}


