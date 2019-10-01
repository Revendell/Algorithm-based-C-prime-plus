#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define MaxSize 1000
typedef int ElemType;
typedef int Status;
//数组第一个元素的cur存放备用链表的第一个节点的下标
//数组最后一个元素的cur存放第一个有数值的元素的下标，相当于单链表的头结点作用，为空时cur=0
typedef struct LinkList
{
	ElemType data;
	int cur;    //游标cursor，为0时表示无指向
}Component,StaticLinkList[MaxSize];
//初始化数组状态，使得最后一个元素的cur=0，第一个元素到倒数第二个元素的cur=i+1
Status InitList(StaticLinkList space)
{
	int i;
	for(i=0;i<MaxSize-1;i++)
	    space[i].cur=i+1;
    space[MaxSize-1].cur=0;
	return TRUE;
}
//申请结点，若备用空间链表非空，则返回第一个元素的cur作为分配的结点的下标
int Malloc_StaticlinkList(StaticLinkList space)
{
    int i=space[0].cur;
	if(space[0].cur!=0)
		space[0].cur=space[i].cur;
	return i;
}
//返回静态链表的元素个数
int ListLength(StaticLinkList L)
{
	int j,count=0;
	j=L[MaxSize-1].cur;
	while(j!=0)
	{
		count++;
		j=L[j].cur;
	}
	return count;
}
//在L中第i个位置插入新的数据元素e
Status ListInsert(StaticLinkList L,int i,ElemType e)
{
    int j,k,l;
	k=MaxSize-1;
	//插入可以插在链表长度的后一个元素地方所以i>ListLength(L)+1
	if(i<1 || i>ListLength(L)+1)
		return FALSE;
	j=Malloc_StaticlinkList(L);    //获得空闲位置的下标
    if(j==0)
		return FALSE;
	L[j].data=e;
	for(l=1;l<=i-1;l++)
		k=L[k].cur;
	L[j].cur=L[k].cur;    //插入元素的下一个cur=前一个元素的cur
	L[k].cur=j;    //前一个元素的cur=插入元素的下标
	return TRUE;
}
//将下标为k的空闲结点回收到备用链表
void Free_StaticLinkList(StaticLinkList space,int k)
{
    space[k].cur=space[0].cur;
	space[0].cur=k;
}
//删除第i个位置的元素e
Status ListDelete(StaticLinkList L,int i)
{
	int j,k;
	//删除最多删除链表最长的一个位置所以i>ListLength(L)
	if(i<1 || i>ListLength(L))
		return FALSE;
	k=MaxSize-1;
	//要删除第i个位置得找到第i-1个位置的cur，即L[k].cur
    for(j=1;j<=i-1;j++)
		k=L[k].cur;
	j=L[k].cur;
	L[k].cur=L[j].cur;
    Free_StaticLinkList(L,j);
	return TRUE;
}
int main()
{
	StaticLinkList L;
	InitList(L);
	//向静态链表第1个位置插入元素1
	ListInsert(L,1,1);
	//向静态链表第2个位置插入元素2
	ListInsert(L,2,2);
	//向静态链表第3个位置插入元素3
	ListInsert(L,3,3);
	int k=MaxSize-1;
	for(int i=0;i<ListLength(L);i++)
	{
		k=L[k].cur;
		cout<<L[k].data<<endl;
	}
	//删除静态链表第1个位置元素
    ListDelete(L,1);
	return 0;
}