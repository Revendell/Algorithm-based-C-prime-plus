#include<iostream>
using namespace std;
#define MaxVex 100  //定义最大顶点数
#define Inf 65535  //定义无穷大
typedef char VertexType;  //定义顶点数据类型
typedef int EdgeType;  //定义边上权值数据类型
int visited[MaxVex];  //访问标志数组，1表示访问过，0表示还未访问
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
//Prim算法生成最小生成树
void Prim(MatrixGraph G)
{
	int min_cost,min_vex;
	int i,j,k;
	int lowcost[MaxVex];  //记录未加入生成树的顶点到生成树的最小权值距离min_cost，已加入生成树的权值lowcost=0
	int adjvex[MaxVex];  //记录未加入生成树的顶点与生成树相连的最小权值距离的顶点下标
	
	lowcost[0]=0;  //v0加入生成树，cost=0
	adjvex[0]=0;  //初始化第一个顶点下标为0
	for(i=1;i<G.numVex;i++)
	{
		lowcost[i]=G.arc[0][i];  //将v0顶点与其他顶点有边的权值存入lowcost，无边的权值为Inf
		adjvex[i]=0;  //初始化都为v0的下标，其他顶点到生成树的端点只有v0，下标为0
	}
	for(i=1;i<G.numVex;i++) //循环numVex-1次，为的是找到生成树的所有numVex-1条边
	{
		min_cost=Inf;  //标记下一个最近距离边的权值
		j=1;
		min_vex=0;  //标记下一个最近距离的顶点下标
		/*
        第一步找到未加入生成树所有顶点中距离生成树最小权值距离的顶点min_vex，它到生成树的最小权值距离为min_cost
		*/
		while(j<G.numVex)
		{
			if(lowcost[j]!=0 && lowcost[j]<min_cost)  //顶点j未加入生成树并且顶点j的权值距离到生成树中顶点最小，j作为下一个加入生成树的顶点
			{
				min_cost=lowcost[j];
				min_vex=j;
			}
			j++;
		}
		cout<<adjvex[min_vex]<<min_vex<<lowcost[min_vex]<<endl;  //打印刚找到的距离生成树顶点最小权值距离的边的两端顶点以及边的权值
		/*
		第二步更新lowcost和adjvex，因为生成树中加入了新的顶点，那么其他未加入生成树的顶点到生成树的最小权值距离改变，与生成树相连的顶点也改变
		*/
		lowcost[min_vex]=0;  //将新加入生成树顶点min_vex到生成树的权值距离cost=0，表示当前顶点加入生成树
        //更新lowcost和adjvex，因为有新加入生成树的顶点min_vex，所以所有其他顶点到生成树的最小权值距离以及相连的顶点有变化，更新
		for(j=1;j<G.numVex;j++)
		{
			if(lowcost[j]!=0 && G.arc[min_vex][j]<lowcost[j])  //只更新未加入生成树的顶点并且到新加入生成树顶点min_vex的距离小于lowcost
			{
				lowcost[j]=G.arc[min_vex][j];  //更新lowcost，顶点j到新加入生成树顶点min_vex的权值距离小于lowcost
				adjvex[j]=min_vex;  //更新adjvex，未加入到生成树的顶点j与生成树相连端点改为min_vex新加入生成树的顶点
			}
		}
	}
}
int main()
{
	//邻接矩阵法创建图并用Prim算法构建最小生成树
	MatrixGraph G;
	CreateMatrixGraph(&G);
	Prim(G);
	return 0;
}