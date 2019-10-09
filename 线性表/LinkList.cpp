#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
typedef struct Node
{
    ElemType data;
	struct Node *next;
}Node;
typedef struct Node *LinkList;    //定义LinkList
//获取到链表中第i个节点的元素并返回给e
Status GetElem(LinkList L,int i,ElemType *e)
{
	int count=1;
	LinkList p;
	p=L->next;
	while(p!=NULL && count<i)
	{
		p=p->next;
		count++;
	}
	if(p==NULL || count>i)    //如果i=0或者找到尾指针都没找到，返回0
		return FALSE;
    *e=p->data;
	return TRUE;
}
//向链表中第i的位置插入元素e
Status ListInsert(LinkList *L,int i,ElemType e)
{
	int count=1;
	LinkList p,s;
	p=*L;
	while(p!=NULL && count<i)
	{
		p=p->next;
		count++;
	}
	if(p==NULL || count>i)
		return FALSE;
	s=(LinkList)malloc(sizeof(Node));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return TRUE;
}
//删除链表中第i个节点，并将该节点的元素返回给e
Status ListDelete(LinkList *L,int i,ElemType *e)
{
	LinkList p,q;
	p=*L;
	int count=1;
	while(p->next!=NULL && count<i)
	{
		p=p->next;
		count++;
	}
	if(p->next==NULL || count>i)
		return FALSE;
	q=p->next;
	p->next=q->next;
	*e=q->data;
	free(q);
	return TRUE;
}
//头插法建立n个元素带表头节点的单链表L
void CreateListHead(LinkList *L,int n)
{
	LinkList p;
	int i;
	srand((unsigned)time(0));
	*L=(LinkList)malloc(sizeof(Node));
	(*L)->next=NULL;
	for(i=0;i<n;i++)
	{
		p=(LinkList)malloc(sizeof(Node));
		p->data=rand()%100+1;
		p->next=(*L)->next;
		(*L)->next=p;
	}
}
//尾插法建立n个元素带表头节点的单链表L
void CreateListTail(LinkList *L,int n)
{
	LinkList p,q;
	int i;
	srand((unsigned)time(0));
	*L=(LinkList)malloc(sizeof(Node));
	(*L)->next=NULL;
	q=*L;
	for(i=0;i<n;i++)
	{
		p=(LinkList)malloc(sizeof(Node));
		p->data=rand()%100+1;
		p->next=NULL;
		q->next=p;
		q=p;
	}

}
//清空整个单链表，置L为空表，表头指向NULL
Status ClearList(LinkList *L)
{
	LinkList p,q;
	p=(*L)->next;
	while(p!=NULL)
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;
	return TRUE;
}
int main()
{
	LinkList L,p;
	int n=5;    //单链表总共生成n个元素
	int i=3;    //单链表在第i个位置插入元素
	ElemType e=66;    //单链表插入元素e
	CreateListHead(&L,n);
	ListInsert(&L,i,e);
	ListDelete(&L,i,&e);
	p=L->next;
	while(p!=NULL)
	{
		cout<<p->data<<endl;
		p=p->next;
	}
	return 0;
}