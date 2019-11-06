#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define MaxVex 100  //������󶥵���
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������
int visited[MaxVex];  //���ʱ�־���飬1��ʾ���ʹ���0��ʾ��δ����

//�ڽӾ���洢ͼ�Ľṹ
typedef struct Graph
{
	VertexType vex[MaxVex];  //һά����洢������Ϣ
	EdgeType arc[MaxVex][MaxVex];  //��ά����洢�ߵ�Ȩֵ��Ϣ��Ҳ�����ڽӾ���
	int numVex,numArc;  //��¼ͼ�е�ǰ������������
}MatrixGraph;
//����������ͼ���ڽӾ����ʾ
void CreateMatrixGraph(MatrixGraph *G)
{
	int i,j,k,weight;
	//���붥�����ͱ���
	cin>>G->numVex>>G->numArc;
	//���붥����Ϣ�����������
	for(i=0;i<G->numVex;i++)
		cin>>G->vex[i];
	//��ʼ���ڽӾ���
	for(i=0;i<G->numVex;i++)
		for(j=0;j<G->numVex;j++)
			G->arc[i][j]=Inf;
	//�������Ϣ�������ڽӾ���
	for(k=0;k<G->numArc;k++)
	{
		cin>>i>>j>>weight;
		G->arc[i][j]=weight;
		G->arc[j][i]=G->arc[i][j];  //����ͼ������Գ�
	}
}
//�ڽӾ����������ȵݹ��㷨����δ���ʹ��Ķ������DFS����
void DFS(MatrixGraph G,int i)
{
	int j;
	visited[i]=TRUE;
	cout<<G.vex[i];
	for(j=0;j<G.numVex;j++)
	{
		if(G.arc[i][j]==1 && visited[j]==0)
			DFS(G,j);  //�Զ���i�ڽӵĶ���j�ݹ����(jδ������)
	}
}
//�ڽӾ������ȱ�������
void DFSTraverse(MatrixGraph G)
{
	int i;
	for(i=0;i<G.numVex;i++)
		visited[i]=FALSE;  //��ʼ���ж���״̬Ϊδ���ʹ�
	for(i=0;i<G.numVex;i++)
	{
		if(visited[i]==0)  //��δ���ʹ��Ķ������DFS�������������������
			DFS(G,i);
	}
}
/*
*
*
*
*
*/
//�ڽӱ�洢ͼ�Ľṹ
//�߽��
typedef struct EdgeNode
{
	int vex;  //�ڽӵ��򣬴洢����һ�����Ӷ����Ӧ���±�
	EdgeType weight;  //�ߵ�Ȩֵ
	struct EdgeNode *next;  //ָ����һ���ڽӵ�
}EdgeNode;
//������
typedef struct VexNode
{
	VertexType data;  //�����򣬴洢������Ϣ
	EdgeNode *firstEdge;  //�ߵ�ͷָ��
}VexNode;
//�ڽӱ�洢���ж�����
typedef struct  
{
	VexNode adjList[MaxVex];  //adjList����洢������
	int numVex,numArc;  //��¼ͼ�е�ǰ������������
}AdjListGraph;
//��������ͼ���ڽӱ�ṹ
void CreateAdjListGraph(AdjListGraph *G)
{
	int i,j,k,w;
	EdgeNode *e;
	//���붥�����ͱ���
	cin>>G->numVex>>G->numArc;
	//���붥����Ϣ�����������
	for(i=0;i<G->numVex;i++)
	{
		cin>>G->adjList[i].data;  //���붥����Ϣ
		G->adjList[i].firstEdge=NULL;  //���߱���Ϊ�ձ�
	}
	//�������Ϣ�������߱�
	for(k=0;k<G->numArc;k++)
	{
		cin>>i>>j>>w;
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->vex=j;
		e->weight=w;
		//ͷ�巨����������Ϣ
		e->next=G->adjList[i].firstEdge;
		G->adjList[i].firstEdge=e;

		//����ͼ����һ������ͬ���Ĳ���
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->vex=i;
		e->weight=w;
		//ͷ�巨����������Ϣ
		e->next=G->adjList[j].firstEdge;
		G->adjList[j].firstEdge=e;
	}
}
//�ڽӱ��������ȵݹ��㷨����δ���ʹ��Ķ������DFS����
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
//�ڽӱ����ȱ�������
void DFSTraverse_AdjListGraph(AdjListGraph G)
{
	int i;
	for(i=0;i<G.numVex;i++)
		visited[i]=FALSE;  //��ʼ���ж���״̬Ϊδ���ʹ�
	for(i=0;i<G.numVex;i++)
	{
		if(visited[i]==0)
			DFS_AdjListGraph(G,i);  //��δ���ʹ��Ķ������DFS�������������������
	}
}
int main()
{
	
	//�ڽӾ��󷨴���ͼ�������������ͼ
	MatrixGraph G1;
	CreateMatrixGraph(&G1);
    DFSTraverse(G1);
    //�ڽӱ�����ͼ�������������ͼ
	AdjListGraph G2;
	CreateAdjListGraph(&G2);
	DFSTraverse_AdjListGraph(G2);
	return 0;
}