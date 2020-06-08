#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
typedef struct Node
{
	ElemType data;
	struct Node *next;
}Node,*LinkStack;
//链栈的第一个结点top不作为结点，top->next才作为链栈的第一个结点
Status InitList(LinkStack *S)
{
	*S=(Node*)malloc(sizeof(Node));
	(*S)->next=NULL;
	return TRUE;
}
//返回线性表的元素个数
int ListLength(LinkStack S)
{
	int count=0;
	LinkStack s;
	s=S->next;
	while(s!=NULL)
	{
		count++;
		s=s->next;
	}
	return count;
}

Status Push(LinkStack *S,ElemType e)
{
	LinkStack s;
	s=(Node*)malloc(sizeof(Node));
	s->data=e;
	s->next=(*S)->next;
	(*S)->next=s;
	return TRUE;
}
Status Pop(LinkStack *S,ElemType *e)
{
	LinkStack s;
	*e=(*S)->next->data;
	s=(*S)->next;
	(*S)->next=s->next;
	free(s);
	return TRUE;
}
int main()
{
	LinkStack s;
	ElemType e=1;
	InitList(&s);
    Push(&s,e);
	cout<<(ListLength(s))<<endl;
    Pop(&s,&e);
	cout<<e<<endl;
	return 0;
}
