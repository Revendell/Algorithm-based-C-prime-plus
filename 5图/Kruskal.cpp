#include<iostream>
using namespace std;
#define MaxVex 100  //������󶥵���
#define MaxArc 100*99/2  //����������
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������
//�߼�����洢ͼ�Ľṹ
typedef struct
{
	int begin;
	int end;
	EdgeType weight;
}Edge;
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
void Change(int *x,int *y)
{
	int temp;
	temp=*x;
	*x=*y;
	*y=temp;
}
//���鼯�㷨���Find���������ҽڵ�f�������ĸ��ڵ�
int Find(int *parent,int f)
{
	while(parent[f]!=f)  //���f���ϼ�����f�Լ����������ϲ���ֱ���ҵ�f�������ĸ��ڵ�
		f=parent[f];
	return f;  //����f�������ĸ��ڵ�
}
//Kruskal�㷨����С������
void Kruskal(MatrixGraph G)
{
	int i,j,n,m;
	Edge edges[MaxArc];  //�߼�����洢ͼ�бߵ���Ϣ�����������˵㼰Ȩֵ
	int parent[MaxVex];  //parent����洢��ǰ�±궥���������ṹ�е��ϼ����Ӷ��㣬����ͨ���������ϲ����ҵ����ĸ��ڵ�
	for(i=0;i<G.numVex;i++)
		parent[i]=i;    //��ʼ��parent����ֵ��Ϊ�Լ�����ʾĿǰÿ�����㶼�Ƕ����ģ��Լ����Լ��ĸ��ڵ�

	int edgeNum=0;
	//���ڽӾ���ת��Ϊ�߼�����
	for(i=0;i<G.numVex-1;i++)
	{
		for(j=i+1;j<G.numVex;j++)
		{
            if(G.arc[i][j]!=Inf)
			{
				edges[edgeNum].begin=i;
				edges[edgeNum].end=j;
				edges[edgeNum].weight=G.arc[i][j];
				edgeNum++;
			}
		}
	}
	//�Ա߼����鰴Ȩֵ��С��������̰���㷨��˼��
	for(i=0;i<edgeNum-1;i++)
	{
		for(j=i+1;j<edgeNum;j++)
		{
			if(edges[i].weight>edges[j].weight)
			{
				Change(&edges[i].weight,&edges[j].weight);
				Change(&edges[i].begin,&edges[j].begin);
				Change(&edges[i].end,&edges[j].end);
			}
		}
	}
	//�ϲ����㷨��˼�룬�ҵ�һ���ߵ������˵�ĸ��ڵ㣬�������ͨ�ͺϲ�����
	for(i=0;i<G.numArc;i++)
	{
		n=Find(parent,edges[i].begin);
		m=Find(parent,edges[i].end);
		if(n!=m)  //����ߵ������˵��������ĸ��ڵ㲻��ȣ�˵�������˵㲻��ͬһ��������(����ͨ)���Ͱ��������ڵ���ͨ��֧�ϲ�����
		{
			parent[n]=m;  //���鼯�㷨�����Join�������ϲ������˵�ĸ��ڵ㣬ʹ�������˵����ͨ��֧�ϲ�����
			cout<<edges[i].begin<<edges[i].end<<edges[i].weight<<endl;  //��ӡ��С��������һ����
		}
	}
}
int main()
{
	//�ڽӾ��󷨴���ͼ��ת��Ϊ�߼������ʾͼ����Kruskal�㷨������С������
	MatrixGraph G;
	CreateMatrixGraph(&G);
	Kruskal(G);
	return 0;
}
