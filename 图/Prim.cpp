#include<iostream>
using namespace std;
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
//Prim�㷨������С������
void Prim(MatrixGraph G)
{
	int min_cost,min_vex;
	int i,j,k;
	int lowcost[MaxVex];  //��¼δ�����������Ķ��㵽����������СȨֵ����min_cost���Ѽ�����������Ȩֵlowcost=0
	int adjvex[MaxVex];  //��¼δ�����������Ķ�������������������СȨֵ����Ķ����±�
	
	lowcost[0]=0;  //v0������������cost=0
	adjvex[0]=0;  //��ʼ����һ�������±�Ϊ0
	for(i=1;i<G.numVex;i++)
	{
		lowcost[i]=G.arc[0][i];  //��v0���������������бߵ�Ȩֵ����lowcost���ޱߵ�ȨֵΪInf
		adjvex[i]=0;  //��ʼ����Ϊv0���±꣬�������㵽�������Ķ˵�ֻ��v0���±�Ϊ0
	}
	for(i=1;i<G.numVex;i++) //ѭ��numVex-1�Σ�Ϊ�����ҵ�������������numVex-1����
	{
		min_cost=Inf;  //�����һ���������ߵ�Ȩֵ
		j=1;
		min_vex=0;  //�����һ���������Ķ����±�
		/*
        ��һ���ҵ�δ�������������ж����о�����������СȨֵ����Ķ���min_vex����������������СȨֵ����Ϊmin_cost
		*/
		while(j<G.numVex)
		{
			if(lowcost[j]!=0 && lowcost[j]<min_cost)  //����jδ�������������Ҷ���j��Ȩֵ���뵽�������ж�����С��j��Ϊ��һ�������������Ķ���
			{
				min_cost=lowcost[j];
				min_vex=j;
			}
			j++;
		}
		cout<<adjvex[min_vex]<<min_vex<<lowcost[min_vex]<<endl;  //��ӡ���ҵ��ľ���������������СȨֵ����ıߵ����˶����Լ��ߵ�Ȩֵ
		/*
		�ڶ�������lowcost��adjvex����Ϊ�������м������µĶ��㣬��ô����δ�����������Ķ��㵽����������СȨֵ����ı䣬�������������Ķ���Ҳ�ı�
		*/
		lowcost[min_vex]=0;  //���¼�������������min_vex����������Ȩֵ����cost=0����ʾ��ǰ�������������
        //����lowcost��adjvex����Ϊ���¼����������Ķ���min_vex�����������������㵽����������СȨֵ�����Լ������Ķ����б仯������
		for(j=1;j<G.numVex;j++)
		{
			if(lowcost[j]!=0 && G.arc[min_vex][j]<lowcost[j])  //ֻ����δ�����������Ķ��㲢�ҵ��¼�������������min_vex�ľ���С��lowcost
			{
				lowcost[j]=G.arc[min_vex][j];  //����lowcost������j���¼�������������min_vex��Ȩֵ����С��lowcost
				adjvex[j]=min_vex;  //����adjvex��δ���뵽�������Ķ���j�������������˵��Ϊmin_vex�¼����������Ķ���
			}
		}
	}
}
int main()
{
	//�ڽӾ��󷨴���ͼ����Prim�㷨������С������
	MatrixGraph G;
	CreateMatrixGraph(&G);
	Prim(G);
	return 0;
}