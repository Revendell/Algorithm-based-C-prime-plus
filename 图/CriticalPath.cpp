#include<iostream>
using namespace std;
#define MaxVex 100  //������󶥵���
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������
int *etv;  //earliest time of vertex �����¼����緢��ʱ��
int *ltv;  //latest time of vertex �����¼���ٷ���ʱ��
int *stack2;  //���ڴ洢�������е�ջ
int top2;  //stack2��ջ��ָ��
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
//���������󶥵����緢��ʱ��etv���������з����󶥵���ٷ���ʱ��ltv
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
	
	etv=(int*)malloc(G.numVex*sizeof(int));
	for(i=0;i<G.numVex;i++)
		etv[i]=0;  //�������緢��ʱ���ʼ��Ϊ0
	top2=0;
	stack2=(int*)malloc(G.numVex*sizeof(int));  //��ʼ�����ڴ洢�������е�ջ

	while(top!=0)  //��top=0ʱջ����û�ж���
	{
		gettop=stack[--top];
		stack2[top2++]=gettop;
		count++;
		e=G.adjList[gettop].firstEdge;  //��ջ��Ԫ�س�ջ�����ջ�����ڽӱ��ڽӵĶ�����ȶ���1���������0��Ҫ��ջ׼����Ϊ��һ�����
		while(e!=NULL)
		{
			j=e->vex;
			G.adjList[j].inDegree--;
			if(G.adjList[j].inDegree==0)
				stack[top++]=j;
			if((etv[gettop]+e->weight)>etv[j])
				etv[j]=etv[gettop]+e->weight;  //�󶥵����緢��ʱ��etv����Ϊ���㷢��ʱ�����ǰ�������ж��㶼�����˲��У�����etv�������ֵ������ͷ������etv����������������β������etv���ϻ���Ȩֵ���ֵ
			e=e->next;
		}
	}
	if(count<G.numVex)
		return 0;
	else
		return 1;

}
//��ؼ�·��
int CriticalPath(AdjListGraph G)
{
	EdgeNode *e;
	int i,j,k,gettop;
	int ete,lte;
	if(TopologicalSort(G)==0)  //���������򣬼�����������緢��ʱ��etv�ʹ洢�������е�ջ
		return 0;
	ltv=(int*)malloc(G.numVex*sizeof(int));
	for(i=0;i<G.numVex;i++)
		ltv[i]=etv[G.numVex-1];  //��ʼ������������ʱ��ltv������󶥵����緢��ʱ��

    //�󶥵���ٷ���ʱ��ltv(��ʵ�����������е��������еĹ���)��ltv����Сֵ��ʾԽ�緢����������������������ͷ������ltv��ٷ���ʱ�䣬����β������ltv����������������ͷ������ltv��ȥ����Ȩֵ��Сֵ
	while(top2!=0)
	{
		gettop=stack2[--top2];
		e=G.adjList[gettop].firstEdge;  //�洢�������е�ջ��ջ��Ԫ�س�ջ
		while(e!=NULL)
		{
			j=e->vex;
			if(ltv[j]-e->weight<ltv[gettop])
				ltv[gettop]=ltv[j]-e->weight;  //�󶥵���ٷ���ʱ��ltv��ltv����Сֵ��ʾԽ�緢����������������������ͷ������ltv��ٷ���ʱ�䣬����β������ltv����������������ͷ������ltv��ȥ����Ȩֵ��Сֵ
			e=e->next;
		}
	}
	//�������etv��ltv���㻡����緢��ʱ��ete�������ٷ���ʱ��lte�͹ؼ����ete=lteʱ
	for(i=0;i<G.numVex;i++)
	{
		e=G.adjList[i].firstEdge;
		while(e!=NULL)
		{
			j=e->vex;
			ete=etv[i];  //������緢��ʱ��ete���ڻ�β���������緢��ʱ��etv
			lte=ltv[j]-e->weight;  //�����ٷ���ʱ��lte���ڻ�ͷ��������ٷ���ʱ��ltv��ȥ����Ȩֵ
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