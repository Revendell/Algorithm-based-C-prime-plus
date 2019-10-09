#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define MaxSize 1000
typedef int ElemType;
typedef int Status;
//�����һ��Ԫ�ص�cur��ű�������ĵ�һ���ڵ���±�
//�������һ��Ԫ�ص�cur��ŵ�һ������ֵ��Ԫ�ص��±꣬�൱�ڵ������ͷ������ã�Ϊ��ʱcur=0
typedef struct LinkList
{
	ElemType data;
	int cur;    //�α�cursor��Ϊ0ʱ��ʾ��ָ��
}Component,StaticLinkList[MaxSize];
//��ʼ������״̬��ʹ�����һ��Ԫ�ص�cur=0����һ��Ԫ�ص������ڶ���Ԫ�ص�cur=i+1
Status InitList(StaticLinkList space)
{
	int i;
	for(i=0;i<MaxSize-1;i++)
	    space[i].cur=i+1;
    space[MaxSize-1].cur=0;
	return TRUE;
}
//�����㣬�����ÿռ�����ǿգ��򷵻ص�һ��Ԫ�ص�cur��Ϊ����Ľ����±�
int Malloc_StaticlinkList(StaticLinkList space)
{
    int i=space[0].cur;
	if(space[0].cur!=0)
		space[0].cur=space[i].cur;
	return i;
}
//���ؾ�̬�����Ԫ�ظ���
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
//��L�е�i��λ�ò����µ�����Ԫ��e
Status ListInsert(StaticLinkList L,int i,ElemType e)
{
    int j,k,l;
	k=MaxSize-1;
	//������Բ��������ȵĺ�һ��Ԫ�صط�����i>ListLength(L)+1
	if(i<1 || i>ListLength(L)+1)
		return FALSE;
	j=Malloc_StaticlinkList(L);    //��ÿ���λ�õ��±�
    if(j==0)
		return FALSE;
	L[j].data=e;
	for(l=1;l<=i-1;l++)
		k=L[k].cur;
	L[j].cur=L[k].cur;    //����Ԫ�ص���һ��cur=ǰһ��Ԫ�ص�cur
	L[k].cur=j;    //ǰһ��Ԫ�ص�cur=����Ԫ�ص��±�
	return TRUE;
}
//���±�Ϊk�Ŀ��н����յ���������
void Free_StaticLinkList(StaticLinkList space,int k)
{
    space[k].cur=space[0].cur;
	space[0].cur=k;
}
//ɾ����i��λ�õ�Ԫ��e
Status ListDelete(StaticLinkList L,int i)
{
	int j,k;
	//ɾ�����ɾ���������һ��λ������i>ListLength(L)
	if(i<1 || i>ListLength(L))
		return FALSE;
	k=MaxSize-1;
	//Ҫɾ����i��λ�õ��ҵ���i-1��λ�õ�cur����L[k].cur
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
	//��̬�����1��λ�ò���Ԫ��1
	ListInsert(L,1,1);
	//��̬�����2��λ�ò���Ԫ��2
	ListInsert(L,2,2);
	//��̬�����3��λ�ò���Ԫ��3
	ListInsert(L,3,3);
	int k=MaxSize-1;
	for(int i=0;i<ListLength(L);i++)
	{
		k=L[k].cur;
		cout<<L[k].data<<endl;
	}
	//ɾ����̬�����1��λ��Ԫ��
    ListDelete(L,1);
	return 0;
}