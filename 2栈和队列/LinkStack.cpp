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
//��ջ�ĵ�һ�����top����Ϊ��㣬top->next����Ϊ��ջ�ĵ�һ�����
Status InitList(LinkStack *S)
{
	*S=(Node*)malloc(sizeof(Node));
	(*S)->next=NULL;
	return TRUE;
}
//�������Ա��Ԫ�ظ���
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
