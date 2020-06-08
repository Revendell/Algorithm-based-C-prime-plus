#include<iostream>
using namespace std;
#define MaxVex 100  //定义最大顶点数
#define Inf 65535  //定义无穷大
typedef char VertexType;  //定义顶点数据类型
typedef int EdgeType;  //定义边上权值数据类型
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
	int inDegree;  //顶点的入度，入度为0的顶点输出打印
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
		G->adjList[i].inDegree=0;  //初始化所有顶点入度为0
	}
	//输入边信息，建立边表
	for(k=0;k<G->numArc;k++)
	{
		cin>>i>>j>>w;
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->vex=j;
		e->weight=w;
		G->adjList[j].inDegree++;
		//头插法链表插入边信息
		e->next=G->adjList[i].firstEdge;
		G->adjList[i].firstEdge=e;
	}
}
int TopologicalSort(AdjListGraph G)
{
    int i,j,gettop;
	int top=0;  //用于指向栈顶
	int count=0;  //用于统计输出顶点的个数，如果没有输出所有顶点说明存在环
	int *stack;  //建栈存储入度为0的顶点，作为将要输出的顶点
	stack=(int*)malloc(G.numVex*sizeof(int));
	EdgeNode *e;
	for(i=0;i<G.numVex;i++)
		if(G.adjList[i].inDegree==0)
			stack[top++]=i;  //将入度为0的顶点入栈
	while(top!=0)  //当top=0时栈内已没有顶点
	{
        gettop=stack[--top];
		cout<<G.adjList[gettop].data;
		count++;
		e=G.adjList[gettop].firstEdge;  //当栈顶元素出栈，与出栈顶点邻接表邻接的顶点出度都减1，如果减到0就要入栈准备作为下一个输出
		while(e!=NULL)
		{
			j=e->vex;
			G.adjList[j].inDegree--;
			if(G.adjList[j].inDegree==0)
				stack[top++]=j;
			e=e->next;
		}
	}
	if(count<G.numVex)
		return 0;
	else
		return 1;
	
}
int main()
{
	AdjListGraph G;
	CreateAdjListGraph(&G);
	if(TopologicalSort(G)==1)
		cout<<endl;
	return 0;

}