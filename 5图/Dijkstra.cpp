#include<iostream>
using namespace std;
#define MaxVex 100  //������󶥵���
#define Inf 65535  //���������
typedef char VertexType;  //���嶥����������
typedef int EdgeType;  //�������Ȩֵ��������
int visited[MaxVex];  //������飬visited[w]=1��ʾ�����V0��Vw�����·����0��ʾ��δ���
int Distance[MaxVex];  //���ڴ洢�������㵽V0����̾���
int pre[MaxVex];  //���ڼ�¼��V0���ö�������·���У����±�Ķ����ǰ�������±꣬ͨ��pre��������ҵ����ⶥ�㵽V0�����·����������Щ����
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
void Dijkstra(MatrixGraph G,int v0)
{
	int i,j,min_vex,min_Distance;
	//��ʼ��visited��Distance��pre��������
	for(i=0;i<G.numVex;i++)
	{
		visited[i]=0;  //��ʼ��visited����Ϊ0����ʾ��δ���V0��������������·��
		Distance[i]=G.arc[v0][i];  //���ڴ洢�������㵽V0����̾���
		pre[i]=0;  //��ʼ������preΪ0����δ��ö�������·��
	}
	Distance[v0]=0;  //v0��v0�ľ���Ϊ0
	visited[v0]=1;  //�����v0�����·��
	//��ʼ��ѭ����ѭ��numVex-1�Σ��ҵ���v0���������㵽v0�����·����ÿ��ѭ�����һ����������·��
	for(i=1;i<G.numVex;i++)
	{
		min_Distance=Inf;
		//Ѱ����v0����ĵ�min_vex��v0��min_vex��̾���Ϊmin_Distance
		for(j=0;j<G.numVex;j++)
		{
			if(!visited[j] && Distance[j]<min_Distance)
			{
				min_vex=j;
				min_Distance=Distance[j];
			}
		}
		visited[min_vex]=1;  //���ҵ�min_vex��v0����̾��룬���Ϊ1
        //��Ϊmin_vex��v0�����·���Ѿ��ҵ������Լ������min_vex���ڶ��㵽v0�����·������̾���
		for(j=0;j<G.numVex;j++)
		{
			if(!visited[j] && (min_Distance+G.arc[min_vex][j]<Distance[j]))
			{
				Distance[j]=min_Distance+G.arc[min_vex][j];
				pre[j]=min_vex;
			}
		}
	}
}
int main()
{
	//�ڽӾ��󷨴���ͼ����Dijkstra�㷨�����·��
	MatrixGraph G;
	CreateMatrixGraph(&G);
	int v0=0,v3=3,k;
	Dijkstra(G,v0);
	//��ӡv0��v3����̾���
    cout<<Distance[v3]<<endl;
	k=v3;
	//��ӡv0��v3�����·��
	cout<<G.vex[v3];
	while(pre[k]!=0)
	{
		cout<<G.vex[pre[k]];
		k=pre[k];
	}
	cout<<G.vex[pre[k]];
	return 0;
}