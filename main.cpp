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
	CSudoku(int n=40);// 随机生成数独,n越大越难
	void display();// 显示数独
	int resolve(int mod=ALL);// 解数独
	CSudoku(int *data);// 人工指定数独
	
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
				map[i][j]=0;//第i行先置0
			j=rand()%9;//j取0到8的随机数
			map[i][j]=i+1;//第1行随便找一列填1，第2行填2...第9行填9，因为填的不一样，所以重了也不要紧，
			//剩下的用resolve解
		}
	}while(!resolve(ANY));//没解了就再循环一次,其实这步还解出了这个数独，调用的就是带ANY的resolve
	
	// 挖窟窿
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
	
    if(mod==ALL)//all就是搜出全部解，开始解，any就是搜出任一个解，oly就找出唯一一个解
		
	{
		solves=0;
		dfs();
		return solves;
	}
	else if(mod==ANY)//填出题的那个数独
	{
		try
		{
			dfs();
			return 0;//不好意思，一直没执行到出题成功，怎么填都是c==0，返回上一个dfs()，一直返，不会因为
			//return 0;就退出所有递归，只退出一个递归
		}
		catch(int)
		{
			return 1;//好了，执行到im=-1就表示出题成功了
		}
	}
	return 0;
}
int CSudoku::check(int x,int y,int *mark)
{
	int i,j,is,js,count=0;//map[x][y]=0
	for(i=1;i<=9;++i)
		mark[i]=0;//这句话很重要，先把原来的标记都擦了
	for(i=0;i<9;++i)
		mark[map[x][i]]=1;//表示x行所有出现过的元素都不能用了
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
				return;//退出这个函数，返回调用它的函数
			if(c<min)//如果自由度一样就不理它
			{
				im=i;
				jm=j;
				min=c;
			}
		}
	}
	if(im==-1)
	{
		if(smod==ALL)//搜到所有解才停止
		{
			cout<<"No."<<++solves<<endl;
			display();
			return;//
		}
		
		
		else if(smod==ANY) //搜到一个解就停止 
		{
			
			throw(1);
		}
	}
	check(im,jm,mark);//count是最小可能性，这时重新标记一遍，因为循环到最后标记的还不一定是哪个呢，
	//如果用（9，9）的标记，肯定有无数种解，因为没有限制作用嘛~
	/*如果i可以选，就先填进去，然后开始解，然后再调用它（调用一次），找到最合适的解，
	发现有两种可能性，先试试1，然后发现c==0了，退出这个函数，返回调用它的函数，也就是for循环,这时
	重新填入可能的值，因为填的还是最后一个空格，所以不擦也行*/
	for(i=1;i<=9;++i)
	{
		if(mark[i]==0)
		{
			map[im][jm]=i;
			dfs();
		}
	}
	map[im][jm]=0;//把刚才赋过值的空格擦掉，重新来过，因为dfs()一直在调用自身，所以返回时也会层层调
	//用这句话来擦掉结果
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


