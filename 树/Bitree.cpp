#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef char Elemtype;
//����������ṹ����
typedef struct Node  //���ṹ
{
	Elemtype data;  //�������
	struct Node *L;  //����ָ��
	struct Node *R;  //�Һ���ָ��
}Node,*BTree;
int depth=0;
//������ǰ������ݹ��㷨
void PreOrderTraverse(BTree T)
{
	if(T==NULL)
		return;
	cout<<T->data;
	PreOrderTraverse(T->L);
	PreOrderTraverse(T->R);
}
//��������������ݹ��㷨
void MiddleOrderTraverse(BTree T)
{
	if(T==NULL)
		return;
	MiddleOrderTraverse(T->L);
	cout<<T->data;
	MiddleOrderTraverse(T->R);
}
//��������������ݹ��㷨
void PostOrderTraverse(BTree T)
{
	if(T==NULL)
		return;
	PostOrderTraverse(T->L);
	PostOrderTraverse(T->R);
	cout<<T->data;
}
//��ǰ������������н���ֵ��#��ʾ������������������ʾ������T
void CreateBTree(BTree *T)
{
	Elemtype e;
	cin>>e;
	if(e=='#')
		*T=NULL;
	else
	{
        (*T)=(Node*)malloc(sizeof(Node));
		(*T)->data=e;
		CreateBTree(&(*T)->L);
		CreateBTree(&(*T)->R);
	}
}
//��ǰ���������������
void PreTreeDepth(BTree T,int h)
{
	if(T==NULL)
		return;
	if(h>depth)
		depth=h;
	PreTreeDepth(T->L,h+1);
	PreTreeDepth(T->R,h+1);
}
int main()
{
	BTree T;
	//����ab#d##c##
	CreateBTree(&T);
	PreTreeDepth(T,1);
	cout<<depth<<endl;
	PreOrderTraverse(T);
	return 0;
}