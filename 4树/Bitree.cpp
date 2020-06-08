#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef char Elemtype;
//二叉链表结点结构定义
typedef struct Node  //结点结构
{
	Elemtype data;  //结点数据
	struct Node *L;  //左孩子指针
	struct Node *R;  //右孩子指针
}Node,*BTree;
int depth=0;
//二叉树前序遍历递归算法
void PreOrderTraverse(BTree T)
{
	if(T==NULL)
		return;
	cout<<T->data;
	PreOrderTraverse(T->L);
	PreOrderTraverse(T->R);
}
//二叉树中序遍历递归算法
void MiddleOrderTraverse(BTree T)
{
	if(T==NULL)
		return;
	MiddleOrderTraverse(T->L);
	cout<<T->data;
	MiddleOrderTraverse(T->R);
}
//二叉树后序遍历递归算法
void PostOrderTraverse(BTree T)
{
	if(T==NULL)
		return;
	PostOrderTraverse(T->L);
	PostOrderTraverse(T->R);
	cout<<T->data;
}
//按前序输入二叉树中结点的值，#表示空树，构造二叉链表表示二叉树T
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
//按前序计算二叉树的深度
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
	//输入ab#d##c##
	CreateBTree(&T);
	PreTreeDepth(T,1);
	cout<<depth<<endl;
	PreOrderTraverse(T);
	return 0;
}