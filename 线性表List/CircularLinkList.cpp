
#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int Elemtype;
typedef struct Node
{
	Elemtype data;
	struct Node *next;
}Node;
typedef struct Node *CircularLinkList;
//尾插法建立循环链表，循环链表的尾指针是最后一个结点，最后返回的是尾指针
void CreateListTail(CircularLinkList *L,int n)
{
	CircularLinkList p,q,rear,head;

	//初始化循环链表，自己指向自己，尾指针也指向自己
	*L=(CircularLinkList)malloc(sizeof(Node));
	//头结点的data为0标志区别
	(*L)->data=0;
	(*L)->next=*L;
	rear=*L;
	head=*L;
	for(int i=0;i<n;i++)
	{
		p=(CircularLinkList)malloc(sizeof(Node));
		p->data=rand()%100+1;
		p->next=head;
		rear->next=p;
		rear=p;
	}
	*L=rear;
}
Status MergeLinkList(CircularLinkList *La,CircularLinkList *Lb)
{
	CircularLinkList Heada,Headb,p,q;
	Heada=(*La)->next;
	Headb=(*Lb)->next;
	(*La)->next=Headb->next;
	(*Lb)->next=Heada;
	*La=*Lb;
	free(Headb);
	return TRUE;
}
int main()
{
	srand((unsigned)time(NULL));
	CircularLinkList La,Lb,head;
	int n=3;
	CreateListTail(&La, n);
	CreateListTail(&Lb, n);
	MergeLinkList(&La,&Lb);
	//La是尾指针，La->next是头指针
	head=La->next->next;
	while(head->data!=0)
	{
		cout<<head->data<<endl;
		head=head->next;
	}
	return 0;
}