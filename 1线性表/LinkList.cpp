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
typedef struct Node *LinkList;    //����LinkList
//��ȡ�������е�i���ڵ��Ԫ�ز����ظ�e
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
	if(p==NULL || count>i)    //���i=0�����ҵ�βָ�붼û�ҵ�������0
		return FALSE;
    *e=p->data;
	return TRUE;
}
//�������е�i��λ�ò���Ԫ��e
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
//ɾ�������е�i���ڵ㣬�����ýڵ��Ԫ�ط��ظ�e
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
//ͷ�巨����n��Ԫ�ش���ͷ�ڵ�ĵ�����L
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
//β�巨����n��Ԫ�ش���ͷ�ڵ�ĵ�����L
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
//���������������LΪ�ձ���ͷָ��NULL
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
	int n=5;    //�������ܹ�����n��Ԫ��
	int i=3;    //�������ڵ�i��λ�ò���Ԫ��
	ElemType e=66;    //���������Ԫ��e
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