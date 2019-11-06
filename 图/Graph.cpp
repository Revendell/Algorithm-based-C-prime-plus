#include<iostream>
using namespace std;
#define MaxVex 100  //定义最大顶点数
#define Inf 65535  //定义无穷大
typedef char VertexType;  //定义顶点数据类型
typedef int EdgeType;  //定义边上权值数据类型


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
int main()
{
	MatrixGraph G1;
	AdjListGraph G2;
	CreateMatrixGraph(&G1);
	CreateAdjListGraph(&G2);
    cout<<G1.numVex<<G2.numVex<<endl;
	return 0;
}