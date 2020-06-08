#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
typedef struct QNode
{
	ElemType data;
	struct QNode *next;
}*Node;
typedef struct
{
	Node front;    //frontָ����е�ͷ��㣬front->next���Ƕ��ж�ͷ
	Node rear;   //rearָ����ж�β
}LinkQueue;
//�����еĵ�һ�����ͷ���front����Ϊ��㣬front->next����Ϊ�����еĶ�ͷ
/*
�򵥽�����ʲô�����ʹ��malloc��
1.��c�����У��ڴ�ģ�ͷ�Ϊջ�Ͷѡ�
2.������ģ���ڴ�ķ�ʽ�ǲ�ͬ�ģ���ջ�д�ŵı�������ϵͳ�Զ�����ģ��ں���������ϵͳ���Զ��ͷţ�����Ҫ��Ϊ�Ľ����κβ�����
3.���ڶ��д�ŵ����û��Լ�������ڴ棬�ֶ�����ģ�malloc������ϵͳ�����ں�����ִ�н������Զ��ͷţ���Ҫ�û��ֶ��ͷ�ͨ��free������
����Է���Ŀռ�����Լ��Ĺ�����ͷ���Ҫʹ��malloc�����ߵ���ķ���Ŀռ��ں�����������Ҫ���ڡ�
*/
Status InitList(LinkQueue *Q)
{
	Node s=(QNode*)malloc(sizeof(QNode));
	Q->front=s;
	Q->rear=s;
	return TRUE;
}
//�����е�����в�������Ԫ��e������ж�β
Status EnterQueue(LinkQueue *Q,ElemType e)
{
	Node s=(QNode*)malloc(sizeof(QNode));
	s->data=e;
	s->next=NULL;
	Q->rear->next=s;
	Q->rear=s;
	return TRUE;
}
//�����еĳ��Ӳ���������ͷԪ��ɾ�������ظ�e
Status DeleteQueue(LinkQueue *Q,ElemType *e)
{
	Node p;
	if(Q->front==Q->rear)
		return FALSE;
	p=Q->front->next;
	*e=p->data;
	Q->front->next=p->next;
	if(Q->rear==p)
		Q->rear=Q->front;
	free(p);
	return TRUE;
}
//�������Ա��Ԫ�ظ���
int ListQueueLength(LinkQueue Q)
{
	int count=0;
	Node p;
	p=Q.front->next;
	while(p!=NULL)
	{
		count++;
		p=p->next;
	}
	return count;
}

int main()
{
	LinkQueue Q;
	Node p;
	ElemType e;
	InitList(&Q);	
	EnterQueue(&Q,1);
	EnterQueue(&Q,2);
	EnterQueue(&Q,3);
	p=Q.front->next;
	for(int i=0;i<ListQueueLength(Q);i++)
	{
        cout<<p->data<<endl;
		p=p->next;
	}
	DeleteQueue(&Q,&e);
	cout<<e<<endl;
	return TRUE;
}