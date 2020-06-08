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
	struct Node* next;
	struct Node* prior;
}Node, * DulLinkList;    //相当于typedef struct Node *DulLinkList;
//尾插法建立双向链表
void CreateListTail(DulLinkList* L, int n)
{
	DulLinkList p, q;
	//初始化双向链表
	*L = (DulLinkList)malloc(sizeof(Node));
	//头结点的data为0标志区别
	(*L)->data = 0;
	(*L)->next = *L;
	(*L)->prior = *L;
	q = *L;
	for (int i = 0; i < n; i++)
	{
		p = (DulLinkList)malloc(sizeof(Node));
		p->data = rand() % 100 + 1;
		p->next = q->next;
		q->next->prior = p;
		p->prior = q;
		q->next = p;
		q = p;
	}
}
//向链表中第i的位置插入元素e
Status DulListInsert(DulLinkList* L, int i, Elemtype e)
{
	int count = 1;
	DulLinkList p, s;
	p = *L;
	while (p->next->data != 0 && count < i)
	{
		p = p->next;
		count++;
	}
	if (p->next->data == 0 || count > i)
		return FALSE;
	s = (DulLinkList)malloc(sizeof(Node));
	s->data = e;
	s->prior = p;
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return TRUE;
}
//删除链表中第i个节点，并将该节点的元素返回给e
Status DulListDelete(DulLinkList* L, int i)
{
	DulLinkList p, q;
	p = (*L)->next;
	int count = 1;
	while (p->data != 0 && count < i)
	{
		p = p->next;
		count++;
	}
	if (p->data == 0 || count > i)
		return FALSE;
	q = p->next;
	p->prior->next = q;
	q->prior = p->prior;
	free(p);
	return TRUE;
}
int main()
{
	//这里讨论的是带头结点的循环双向链表
	DulLinkList L, p;
	srand((unsigned)time(NULL));
	int n = 3;
	CreateListTail(&L, n);
	DulListInsert(&L, 1, 1);
	DulListDelete(&L, 1);
	p = L->next;
	while (p->data != 0)
	{
		cout << p->data << endl;
		p = p->next;
	}
	return 0;
}