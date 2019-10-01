
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
//β�巨����ѭ������ѭ�������βָ�������һ����㣬��󷵻ص���βָ��
void CreateListTail(CircularLinkList *L,int n)
{
	CircularLinkList p,q,rear,head;

	//��ʼ��ѭ�������Լ�ָ���Լ���βָ��Ҳָ���Լ�
	*L=(CircularLinkList)malloc(sizeof(Node));
	//ͷ����dataΪ0��־����
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
	//La��βָ�룬La->next��ͷָ��
	head=La->next->next;
	while(head->data!=0)
	{
		cout<<head->data<<endl;
		head=head->next;
	}
	return 0;
}