#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define MaxVex 100  //������󶥵���
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������
typedef int Status;
int visited[MaxVex];  //���ʱ�־���飬1��ʾ���ʹ���0��ʾ��δ����

typedef struct{
	int data[MaxVex];
	int front;
	int rear;
}Queue;
//��ʼ��һ���ն���Q
Status Init(Queue *Q)
{
	Q->front=0;
	Q->rear=0;
	return TRUE;
}
//���ض��еĳ���
int QueueLength(Queue Q)
{
	return (Q.rear-Q.front+MaxVex)%MaxVex;
}
//����в���������в���Ԫ��e��Q�Ķ�β
Status EnterQueue(Queue *Q,int e)
{
	if((Q->rear+1)%MaxVex==Q->front)
		return FALSE;
	Q->data[Q->rear]=e;
	Q->rear=(Q->rear+1)%MaxVex;
	return TRUE;
}
//�����в����������ж�ͷԪ�س����в����ظ�e
Status DeleteQueue(Queue *Q,int *e)
{
	if(Q->front==Q->rear)
		return FALSE;
	*e=Q->data[Q->front];
	Q->front=(Q->front+1)%MaxVex;
	return TRUE;
}

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
//�ڽӾ���Ĺ�ȱ����㷨
void BFSTraverse(MatrixGraph G)
{
    int i,j;
	Queue Q;
	for(i=0;i<G.numVex;i++)
		visited[i]=FALSE;  //��ʼ���ж���״̬Ϊδ���ʹ�
	Init(&Q);
	for(i=0;i<G.numVex;i++)  //��ÿһ������ѭ����һ�жϷ���
	{
		if(visited[i]==0)
		{
			visited[i]=TRUE;
			cout<<G.vex[i];
			EnterQueue(&Q,i);  //�����ʹ��Ķ��������
			while(QueueLength(Q)!=0)
			{
				DeleteQueue(&Q,&i);  //����Ԫ�س�����
				for(j=0;j<G.numVex;j++)
				{
					if(G.arc[i][j]==1 && visited[j]==0)  //�ж��ڽӶ����Ƿ���ʹ�
					{
						visited[j]=TRUE;
						cout<<G.vex[j];
						EnterQueue(&Q,j);  //�����ʹ��Ķ��������
					}
				}
			}
		}
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
//�ڽӱ�Ĺ�ȱ����㷨
void BFSTraverse_AdjListGraph(AdjListGraph G)
{
	int i;
	EdgeNode *p;
	Queue Q;
	for(i=0;i<G.numVex;i++)
		visited[i]=FALSE;  //��ʼ���ж���״̬Ϊδ���ʹ�
	Init(&Q);
	for(i=0;i<G.numVex;i++)  //��ÿһ������ѭ����һ�жϷ���
	{
		if(visited[i]==0)
		{
			visited[i]=TRUE;
			cout<<G.adjList[i].data;
			EnterQueue(&Q,i);  //�����ʹ��Ķ��������
			while(QueueLength(Q)!=0)
			{
				DeleteQueue(&Q,&i);   //����Ԫ�س�����
				p=G.adjList[i].firstEdge;
				while(p!=NULL)
				{
					if(visited[p->vex]==0)  //���ڽӶ������δ�����ʣ��Զ���ָ����ڽӶ������
					{
						visited[p->vex]=TRUE;
						cout<<G.adjList[p->vex].data;
						EnterQueue(&Q,p->vex);  //�����ʹ��Ķ��������
					}
					p=p->next;
				}
			}
		}
	}
}
int main()
{
	//�ڽӾ��󷨴���ͼ�������������ͼ
	MatrixGraph G1;
	CreateMatrixGraph(&G1);
	BFSTraverse(G1);
	//�ڽӱ�����ͼ�������������ͼ
	AdjListGraph G2;
	CreateAdjListGraph(&G2);
	BFSTraverse_AdjListGraph(G2);
	return 0;
}