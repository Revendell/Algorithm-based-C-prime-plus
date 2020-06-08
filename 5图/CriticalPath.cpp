#include<iostream>
using namespace std;
#define MaxVex 100  //定义最大顶点数
#define Inf 65535  //定义无穷大
typedef char VertexType;  //定义顶点数据类型
typedef int EdgeType;  //定义边上权值数据类型
int *etv;  //earliest time of vertex 顶点事件最早发生时间
int *ltv;  //latest time of vertex 顶点事件最迟发生时间
int *stack2;  //用于存储拓扑序列的栈
int top2;  //stack2的栈顶指针
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
//拓扑排序求顶点最早发生时间etv和拓扑序列方便求顶点最迟发生时间ltv
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
	
	etv=(int*)malloc(G.numVex*sizeof(int));
	for(i=0;i<G.numVex;i++)
		etv[i]=0;  //顶点最早发生时间初始化为0
	top2=0;
	stack2=(int*)malloc(G.numVex*sizeof(int));  //初始化用于存储拓扑序列的栈

	while(top!=0)  //当top=0时栈内已没有顶点
	{
		gettop=stack[--top];
		stack2[top2++]=gettop;
		count++;
		e=G.adjList[gettop].firstEdge;  //当栈顶元素出栈，与出栈顶点邻接表邻接的顶点出度都减1，如果减到0就要入栈准备作为下一个输出
		while(e!=NULL)
		{
			j=e->vex;
			G.adjList[j].inDegree--;
			if(G.adjList[j].inDegree==0)
				stack[top++]=j;
			if((etv[gettop]+e->weight)>etv[j])
				etv[j]=etv[gettop]+e->weight;  //求顶点最早发生时间etv，因为顶点发生时间必须前驱的所有顶点都发生了才行，所以etv是求最大值，弧的头部顶点etv等于所有相连弧的尾部顶点etv加上弧的权值最大值
			e=e->next;
		}
	}
	if(count<G.numVex)
		return 0;
	else
		return 1;

}
//求关键路径
int CriticalPath(AdjListGraph G)
{
	EdgeNode *e;
	int i,j,k,gettop;
	int ete,lte;
	if(TopologicalSort(G)==0)  //求拓扑排序，计算出顶点最早发生时间etv和存储拓扑序列的栈
		return 0;
	ltv=(int*)malloc(G.numVex*sizeof(int));
	for(i=0;i<G.numVex;i++)
		ltv[i]=etv[G.numVex-1];  //初始化顶点最晚发生时间ltv对于最大顶点最早发生时间

    //求顶点最迟发生时间ltv(其实就是拓扑序列倒过来进行的过程)，ltv是最小值表示越早发生才能满足所有相连弧的头部顶点ltv最迟发生时间，弧的尾部顶点ltv等于所有相连弧的头部顶点ltv减去弧的权值最小值
	while(top2!=0)
	{
		gettop=stack2[--top2];
		e=G.adjList[gettop].firstEdge;  //存储拓扑序列的栈的栈顶元素出栈
		while(e!=NULL)
		{
			j=e->vex;
			if(ltv[j]-e->weight<ltv[gettop])
				ltv[gettop]=ltv[j]-e->weight;  //求顶点最迟发生时间ltv，ltv是最小值表示越早发生才能满足所有相连弧的头部顶点ltv最迟发生时间，弧的尾部顶点ltv等于所有相连弧的头部顶点ltv减去弧的权值最小值
			e=e->next;
		}
	}
	//用已求得etv和ltv计算弧活动最早发生时间ete、弧活动最迟发生时间lte和关键活动当ete=lte时
	for(i=0;i<G.numVex;i++)
	{
		e=G.adjList[i].firstEdge;
		while(e!=NULL)
		{
			j=e->vex;
			ete=etv[i];  //弧活动最早发生时间ete等于弧尾部顶点最早发生时间etv
			lte=ltv[j]-e->weight;  //弧活动最迟发生时间lte等于弧头部顶点最迟发生时间ltv减去弧的权值
			if(ete==lte)
				cout<<G.adjList[i].data<<" "<<G.adjList[j].data<<" "<<e->weight<<endl;
			e=e->next;
		}
	}
	return 1;

}
int main()
{
	AdjListGraph G;
	CreateAdjListGraph(&G);
	if(CriticalPath(G)==1)
		cout<<"Success!"<<endl;
	return 0;
}