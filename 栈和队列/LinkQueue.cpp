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
	Node front;    //front指向队列的头结点，front->next就是队列队头
	Node rear;   //rear指向队列队尾
}LinkQueue;
//链队列的第一个结点头结点front不作为结点，front->next才作为链队列的队头
/*
简单介绍下什么情况下使用malloc：
1.在c语言中，内存模型分为栈和堆。
2.这两种模型内存的方式是不同的，在栈中存放的变量是由系统自动管理的，在函数结束后系统会自动释放，不需要人为的进行任何操作。
3.而在堆中存放的是用户自己管理的内存，手动分配的，malloc建立，系统不会在函数体执行结束后自动释放，需要用户手动释放通过free函数。
当你对分配的空间进行自己的管理和释放需要使用malloc，或者当你的分配的空间在函数结束后还需要存在。
*/
Status InitList(LinkQueue *Q)
{
	Node s=(QNode*)malloc(sizeof(QNode));
	Q->front=s;
	Q->rear=s;
	return TRUE;
}
//链队列的入队列操作，将元素e插入队列队尾
Status EnterQueue(LinkQueue *Q,ElemType e)
{
	Node s=(QNode*)malloc(sizeof(QNode));
	s->data=e;
	s->next=NULL;
	Q->rear->next=s;
	Q->rear=s;
	return TRUE;
}
//链队列的出队操作，将队头元素删除并返回给e
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
//返回线性表的元素个数
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