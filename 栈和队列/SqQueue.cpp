#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define MaxSize 100
typedef int ElemType;
typedef int Status;
typedef struct  
{
	ElemType data[MaxSize];
	int front;
	int rear;
}SqQueue;
//��ʼ��һ���ն���Q
Status Init(SqQueue *Q)
{
    Q->front=0;
	Q->rear=0;
	return TRUE;
}
//���ض��еĳ���
int SqQueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MaxSize)%MaxSize;
}
//����в���������в���Ԫ��e��Q�Ķ�β
Status EnterSqQueue(SqQueue *Q,ElemType e)
{
	if((Q->rear+1)%MaxSize==Q->front)
		return FALSE;
	Q->data[Q->rear]=e;
	Q->rear=(Q->rear+1)%MaxSize;
	return TRUE;
}
//�����в����������ж�ͷԪ�س����в����ظ�e
Status DeleteSqueue(SqQueue *Q,ElemType *e)
{
	if(Q->front==Q->rear)
		return FALSE;
	*e=Q->data[Q->front];
	Q->front=(Q->front+1)%MaxSize;
	return TRUE;
}
int main()
{
    SqQueue Q;
	Init(&Q);
	ElemType e;
	EnterSqQueue(&Q,1);
	EnterSqQueue(&Q,2);
	EnterSqQueue(&Q,3);
	for(int i=Q.front;i<SqQueueLength(Q);i++)
		cout<<Q.data[i]<<endl;
    DeleteSqueue(&Q,&e);
    cout<<e<<endl;
	return 0;
}