#include<iostream>
using namespace std;
#define MaxVex 100  //������󶥵���
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������


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
int main()
{
	MatrixGraph G1;
	AdjListGraph G2;
	CreateMatrixGraph(&G1);
	CreateAdjListGraph(&G2);
    cout<<G1.numVex<<G2.numVex<<endl;
	return 0;
}