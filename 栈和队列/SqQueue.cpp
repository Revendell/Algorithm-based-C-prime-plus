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
//初始化一个空队列Q
Status Init(SqQueue *Q)
{
    Q->front=0;
	Q->rear=0;
	return TRUE;
}
//返回队列的长度
int SqQueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MaxSize)%MaxSize;
}
//入队列操作，向队列插入元素e到Q的队尾
Status EnterSqQueue(SqQueue *Q,ElemType e)
{
	if((Q->rear+1)%MaxSize==Q->front)
		return FALSE;
	Q->data[Q->rear]=e;
	Q->rear=(Q->rear+1)%MaxSize;
	return TRUE;
}
//出队列操作，将队列队头元素出队列并返回给e
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