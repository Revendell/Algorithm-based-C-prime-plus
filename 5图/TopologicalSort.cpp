#include<iostream>
using namespace std;
#define MaxVex 100  //������󶥵���
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������
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
	int inDegree;  //�������ȣ����Ϊ0�Ķ��������ӡ
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
		G->adjList[i].inDegree=0;  //��ʼ�����ж������Ϊ0
	}
	//�������Ϣ�������߱�
	for(k=0;k<G->numArc;k++)
	{
		cin>>i>>j>>w;
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		e->vex=j;
		e->weight=w;
		G->adjList[j].inDegree++;
		//ͷ�巨����������Ϣ
		e->next=G->adjList[i].firstEdge;
		G->adjList[i].firstEdge=e;
	}
}
int TopologicalSort(AdjListGraph G)
{
    int i,j,gettop;
	int top=0;  //����ָ��ջ��
	int count=0;  //����ͳ���������ĸ��������û��������ж���˵�����ڻ�
	int *stack;  //��ջ�洢���Ϊ0�Ķ��㣬��Ϊ��Ҫ����Ķ���
	stack=(int*)malloc(G.numVex*sizeof(int));
	EdgeNode *e;
	for(i=0;i<G.numVex;i++)
		if(G.adjList[i].inDegree==0)
			stack[top++]=i;  //�����Ϊ0�Ķ�����ջ
	while(top!=0)  //��top=0ʱջ����û�ж���
	{
        gettop=stack[--top];
		cout<<G.adjList[gettop].data;
		count++;
		e=G.adjList[gettop].firstEdge;  //��ջ��Ԫ�س�ջ�����ջ�����ڽӱ��ڽӵĶ�����ȶ���1���������0��Ҫ��ջ׼����Ϊ��һ�����
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