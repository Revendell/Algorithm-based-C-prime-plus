#include<iostream>
using namespace std;
#define MaxVex 100  //定义最大顶点数
#define Inf 65535  //定义无穷大
typedef char VertexType;  //定义顶点数据类型
typedef int EdgeType;  //定义边上权值数据类型
EdgeType Distance[MaxVex][MaxVex];  //Distance用于存储各顶点间的最短距离
int pre[MaxVex][MaxVex];  //pre数组存储各顶点之间途经的前驱顶点
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
//Floyd算法求最短路径
void Floyd(MatrixGraph G)
{
    int i,j,k;
	//初始化两个二维数组Distance和pre，Distance用于存储各顶点间的最短距离，pre数组存储各顶点之间途经的前驱顶点
	for(i=0;i<G.numVex;i++)
	{
		for(j=0;j<G.numVex;j++)
		{
			Distance[i][j]=G.arc[i][j];
			pre[i][j]=j;
		}
	}
	for(k=0;k<G.numVex;k++)
	{
		for(i=0;i<G.numVex;i++)
		{
			for(j=0;j<G.numVex;j++)
			{
				//经过下标为k顶点路径比原两个点间路径更短
				if(Distance[i][j]>Distance[i][k]+Distance[k][j])
				{
					Distance[i][j]=Distance[i][k]+Distance[k][j];  //更新最短距离
					pre[i][j]=pre[i][k];  //将顶点i与j之间最短路径经过的顶点k记录到pre[i][j]，因为记录的是pre[i][k]，而不是pre[k][j]，所以最后打印路径时是按照正确顺序从v0到v8而不是Dijkstra算法中逆序打印途经顶点
				}
			}
		}
	}
}
int main()
{
	//邻接矩阵法创建图并用Dijkstra算法求最短路径
	MatrixGraph G;
	CreateMatrixGraph(&G);
	Floyd(G);
	int i,j,k;
	//输出图中所有顶点到其他顶点的最短距离及最短路径，因为有向图v0到v8和v8到v0路径一样，所以只打印上三角顶点路径
	for(i=0;i<G.numVex;i++)
	{
		for(j=i+1;j<G.numVex;j++)
		{
			//打印输出顶点i，顶点j以及i到j之间的最短距离
			cout<<i<<" "<<j<<" "<<Distance[i][j]<<endl;
			k=pre[i][j];  //获取到i与j之间途经的顶点k
			cout<<"Path:"<<i;
			while(k!=j)
			{
				cout<<k;
				k=pre[k][j];  //不断向前推进找到k与j之间途经的顶点k
			}
			cout<<j<<endl;
		}
	}
	return 0;
}
