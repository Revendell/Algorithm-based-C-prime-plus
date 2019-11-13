#include<iostream>
using namespace std;
#define MaxVex 100  //定义最大顶点数
#define Inf 65535  //定义无穷大
typedef char VertexType;  //定义顶点数据类型
typedef int EdgeType;  //定义边上权值数据类型
int visited[MaxVex];  //标记数组，visited[w]=1表示已求得V0至Vw的最短路径，0表示还未求得
int Distance[MaxVex];  //用于存储其他顶点到V0的最短距离
int pre[MaxVex];  //用于记录从V0到该顶点的最短路径中，该下标的顶点的前驱顶点下标，通过pre数组可以找到任意顶点到V0的最短路径所经过哪些顶点
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
void Dijkstra(MatrixGraph G,int v0)
{
	int i,j,min_vex,min_Distance;
	//初始化visited、Distance、pre三个数组
	for(i=0;i<G.numVex;i++)
	{
		visited[i]=0;  //初始化visited数组为0，表示还未求得V0到其他顶点的最短路径
		Distance[i]=G.arc[v0][i];  //用于存储其他顶点到V0的最短距离
		pre[i]=0;  //初始化数组pre为0，还未求得顶点的最短路径
	}
	Distance[v0]=0;  //v0到v0的距离为0
	visited[v0]=1;  //已求得v0的最短路径
	//开始主循环，循环numVex-1次，找到除v0外其他顶点到v0的最短路径，每次循环求得一个顶点的最短路径
	for(i=1;i<G.numVex;i++)
	{
		min_Distance=Inf;
		//寻找离v0最近的点min_vex，v0到min_vex最短距离为min_Distance
		for(j=0;j<G.numVex;j++)
		{
			if(!visited[j] && Distance[j]<min_Distance)
			{
				min_vex=j;
				min_Distance=Distance[j];
			}
		}
		visited[min_vex]=1;  //已找到min_vex到v0的最短距离，标记为1
        //因为min_vex到v0的最短路径已经找到，可以计算出与min_vex相邻顶点到v0的最短路径和最短距离
		for(j=0;j<G.numVex;j++)
		{
			if(!visited[j] && (min_Distance+G.arc[min_vex][j]<Distance[j]))
			{
				Distance[j]=min_Distance+G.arc[min_vex][j];
				pre[j]=min_vex;
			}
		}
	}
}
int main()
{
	//邻接矩阵法创建图并用Dijkstra算法求最短路径
	MatrixGraph G;
	CreateMatrixGraph(&G);
	int v0=0,v3=3,k;
	Dijkstra(G,v0);
	//打印v0到v3的最短距离
    cout<<Distance[v3]<<endl;
	k=v3;
	//打印v0到v3的最短路径
	cout<<G.vex[v3];
	while(pre[k]!=0)
	{
		cout<<G.vex[pre[k]];
		k=pre[k];
	}
	cout<<G.vex[pre[k]];
	return 0;
}