#include<iostream>
using namespace std;
#define MaxVex 100  //定义最大顶点数
#define MaxArc 100*99/2  //定义最大边数
#define Inf 65535  //定义无穷大
typedef char VertexType;  //定义顶点数据类型
typedef int EdgeType;  //定义边上权值数据类型
//边集数组存储图的结构
typedef struct
{
	int begin;
	int end;
	EdgeType weight;
}Edge;
//邻接矩阵存储图的结构
typedef struct Graph
{
	VertexType vex[MaxVex];  //一维数组存储顶点信息
	EdgeType arc[MaxVex][MaxVex];  //二维数组存储边的权值信息，也就是邻接矩阵
	int numVex,numArc;  //记录图中当前顶点数、边数
}MatrixGraph;
//建立无向网图的邻接矩阵表示
void CreateMatrixGraph(MatrixGraph *G)
{
	int i,j,k,weight;
	//输入顶点数和边数
	cin>>G->numVex>>G->numArc;
	//输入顶点信息，建立顶点表
	for(i=0;i<G->numVex;i++)
		cin>>G->vex[i];
	//初始化邻接矩阵
	for(i=0;i<G->numVex;i++)
		for(j=0;j<G->numVex;j++)
			G->arc[i][j]=Inf;
	//输入边信息，建立邻接矩阵
	for(k=0;k<G->numArc;k++)
	{
		cin>>i>>j>>weight;
		G->arc[i][j]=weight;
		G->arc[j][i]=G->arc[i][j];  //无向图，矩阵对称
	}
}
void Change(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
//并查集算法里的Find函数，查找节点f所在树的根节点
int Find(int *parent,int f)
{
	while(parent[f]!=f)  //如果f的上级不是f自己，不断向上查找直到找到f所在树的根节点
		f=parent[f];
	return f;  //返回f所在树的根节点
}
//Kruskal算法求最小生成树
void Kruskal(MatrixGraph G)
{
	int i,j,n,m;
	Edge edges[MaxArc];  //边集数组存储图中边的信息，包括两个端点及权值
	int parent[MaxVex];  //parent数组存储当前下标顶点所在树结构中的上级连接顶点，可以通过不断向上查找找到树的根节点
	for(i=0;i<G.numVex;i++)
		parent[i]=i;    //初始化parent数组值都为自己，表示目前每个顶点都是独立的，自己是自己的根节点

	int edgeNum=0;
	//将邻接矩阵转换为边集数组
	for(i=0;i<G.numVex-1;i++)
	{
		for(j=i+1;j<G.numVex;j++)
		{
            if(G.arc[i][j]!=Inf)
			{
				edges[edgeNum].begin=i;
				edges[edgeNum].end=j;
				edges[edgeNum].weight=G.arc[i][j];
				edgeNum++;
			}
		}
	}
	//对边集数组按权值从小到大排序，贪心算法的思想
	for(i=0;i<edgeNum-1;i++)
	{
		for(j=i+1;j<edgeNum;j++)
		{
			if(edges[i].weight>edges[j].weight)
			{
				Change(&edges[i].weight,&edges[j].weight);
				Change(&edges[i].begin,&edges[j].begin);
				Change(&edges[i].end,&edges[j].end);
			}
		}
	}
	//合并集算法的思想，找到一条边的两个端点的根节点，如果不连通就合并起来
	for(i=0;i<G.numArc;i++)
	{
		n=Find(parent,edges[i].begin);
		m=Find(parent,edges[i].end);
		if(n!=m)  //如果边的两个端点所在树的根节点不相等，说明两个端点不在同一个树里面(不连通)，就把它们所在的连通分支合并起来
		{
			parent[n]=m;  //并查集算法里面的Join函数，合并两个端点的根节点，使得两个端点的连通分支合并起来
			cout<<edges[i].begin<<edges[i].end<<edges[i].weight<<endl;  //打印最小生成树的一条边
		}
	}
}
int main()
{
	//邻接矩阵法创建图并转换为边集数组表示图，用Kruskal算法构建最小生成树
	MatrixGraph G;
	CreateMatrixGraph(&G);
	Kruskal(G);
	return 0;
}
