#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
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
//邻接矩阵的深度优先递归算法，对未访问过的顶点调用DFS访问
void DFS(MatrixGraph G,int i)
{
	int j;
	visited[i]=TRUE;
	cout<<G.vex[i];
	for(j=0;j<G.numVex;j++)
	{
		if(G.arc[i][j]==1 && visited[j]==0)
			DFS(G,j);  //对顶点i邻接的顶点j递归调用(j未被访问)
	}
}
//邻接矩阵的深度遍历操作
void DFSTraverse(MatrixGraph G)
{
	int i;
	for(i=0;i<G.numVex;i++)
		visited[i]=FALSE;  //初始所有顶点状态为未访问过
	for(i=0;i<G.numVex;i++)
	{
		if(visited[i]==0)  //对未访问过的顶点调用DFS进行深度优先搜索访问
			DFS(G,i);
	}
}
/*
*
*
*
*
*/
//邻接表存储图的结构
//边结点
typedef struct EdgeNode
{
	int vex;  //邻接点域，存储边另一个连接顶点对应的下标
	EdgeType weight;  //边的权值
	struct EdgeNode *next;  //指向下一个邻接点
}EdgeNode;
//顶点结点
typedef struct VexNode
{
	VertexType data;  //顶点域，存储顶点信息
	EdgeNode *firstEdge;  //边的头指针
}VexNode;
//邻接表存储所有顶点结点
typedef struct  
{
	VexNode adjList[MaxVex];  //adjList数组存储顶点结点
	int numVex,numArc;  //记录图中当前顶点数、边数
}AdjListGraph;
//建立无向图的邻接表结构
void CreateAdjListGraph(AdjListGraph *G)
{
	int i,j,k,w;
	EdgeNode *e;
	//输入顶点数和边数
	cin>>G->numVex>>G->numArc;
	//输入顶点信息，建立顶点表
	for(i=0;i<G->numVex;i++)
	{
		cin>>G->adjList[i].data;  //输入顶点信息
		G->adjList[i].firstEdge=NULL;  //将边表置为空表
	}
	//输入边信息，建立边表
	for(k=0;k<G->numArc;k++)
	{
		cin>>i>>j>>w;
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->vex=j;
		e->weight=w;
		//头插法链表插入边信息
		e->next=G->adjList[i].firstEdge;
		G->adjList[i].firstEdge=e;

		//无向图，另一个顶点同样的操作
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->vex=i;
		e->weight=w;
		//头插法链表插入边信息
		e->next=G->adjList[j].firstEdge;
		G->adjList[j].firstEdge=e;
	}
}
//邻接表的深度优先递归算法，对未访问过的顶点调用DFS访问
void DFS_AdjListGraph(AdjListGraph G,int i)
{
	EdgeNode *p;
	visited[i]=TRUE;
	cout<<G.adjList[i].data;
	p=G.adjList[i].firstEdge;
	while(p!=NULL)
	{
		if(visited[p->vex]==0)
			DFS_AdjListGraph(G,p->vex);
		p=p->next;
	}
}
//邻接表的深度遍历操作
void DFSTraverse_AdjListGraph(AdjListGraph G)
{
	int i;
	for(i=0;i<G.numVex;i++)
		visited[i]=FALSE;  //初始所有顶点状态为未访问过
	for(i=0;i<G.numVex;i++)
	{
		if(visited[i]==0)
			DFS_AdjListGraph(G,i);  //对未访问过的顶点调用DFS进行深度优先搜索访问
	}
}
int main()
{
	
	//邻接矩阵法创建图并深度优先搜索图
	MatrixGraph G1;
	CreateMatrixGraph(&G1);
    DFSTraverse(G1);
    //邻接表法创建图并深度优先搜索图
	AdjListGraph G2;
	CreateAdjListGraph(&G2);
	DFSTraverse_AdjListGraph(G2);
	return 0;
}