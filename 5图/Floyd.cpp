#include<iostream>
using namespace std;
#define MaxVex 100  //������󶥵���
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������
EdgeType Distance[MaxVex][MaxVex];  //Distance���ڴ洢����������̾���
int pre[MaxVex][MaxVex];  //pre����洢������֮��;����ǰ������
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
//Floyd�㷨�����·��
void Floyd(MatrixGraph G)
{
    int i,j,k;
	//��ʼ��������ά����Distance��pre��Distance���ڴ洢����������̾��룬pre����洢������֮��;����ǰ������
	for(i=0;i<G.numVex;i++)
	{
		for(j=0;j<G.numVex;j++)
		{
			Distance[i][j]=G.arc[i][j];
			pre[i][j]=j;
		}
	}
	for(k=0;k<G.numVex;k++)
	{
		for(i=0;i<G.numVex;i++)
		{
			for(j=0;j<G.numVex;j++)
			{
				//�����±�Ϊk����·����ԭ�������·������
				if(Distance[i][j]>Distance[i][k]+Distance[k][j])
				{
					Distance[i][j]=Distance[i][k]+Distance[k][j];  //������̾���
					pre[i][j]=pre[i][k];  //������i��j֮�����·�������Ķ���k��¼��pre[i][j]����Ϊ��¼����pre[i][k]��������pre[k][j]����������ӡ·��ʱ�ǰ�����ȷ˳���v0��v8������Dijkstra�㷨�������ӡ;������
				}
			}
		}
	}
}
int main()
{
	//�ڽӾ��󷨴���ͼ����Dijkstra�㷨�����·��
	MatrixGraph G;
	CreateMatrixGraph(&G);
	Floyd(G);
	int i,j,k;
	//���ͼ�����ж��㵽�����������̾��뼰���·������Ϊ����ͼv0��v8��v8��v0·��һ��������ֻ��ӡ�����Ƕ���·��
	for(i=0;i<G.numVex;i++)
	{
		for(j=i+1;j<G.numVex;j++)
		{
			//��ӡ�������i������j�Լ�i��j֮�����̾���
			cout<<i<<" "<<j<<" "<<Distance[i][j]<<endl;
			k=pre[i][j];  //��ȡ��i��j֮��;���Ķ���k
			cout<<"Path:"<<i;
			while(k!=j)
			{
				cout<<k;
				k=pre[k][j];  //������ǰ�ƽ��ҵ�k��j֮��;���Ķ���k
			}
			cout<<j<<endl;
		}
	}
	return 0;
}
