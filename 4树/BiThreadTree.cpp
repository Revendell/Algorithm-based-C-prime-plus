#include<iostream>
using namespace std;
enum PointTag{child,thread};  //link=0表示指针指向左右孩子，thread=1表示指针指向前驱或后继的线索
typedef char Elemtype;
//二叉线索链表存储结构定义
typedef struct Node
{
	Elemtype data;  //结点数据
	struct Node *L;  //左右孩子指针
	struct Node *R;
	PointTag Ltag;  //左右标记，0表示指针指向左右孩子，1表示指针指向前驱或后继的线索
	PointTag Rtag;
}Node,*BThrTree;
BThrTree pre=NULL;//全局变量，始终指向刚刚访问过的结点，递归的时候经常用到全局变量
//创建二叉树，按前序输入二叉树中结点的值，#表示空树，构造二叉链表表示二叉树T
void CreateBThrTree(BThrTree *T)
{
	Elemtype e;
	cin>>e;
	if(e=='#')
		*T=NULL;
	else
	{
		(*T)=(Node*)malloc(sizeof(Node));
		(*T)->data=e;
		(*T)->Ltag=child;
		(*T)->Rtag=child;
		CreateBThrTree(&(*T)->L);
		CreateBThrTree(&(*T)->R);
	}
}
//中序遍历进行二叉树中序线索化，使二叉树变成二叉线索树，中序顺序是左中右
/*
当前结点p的前驱结点是pre，所以当前结点p的左孩子指向前驱结点pre，p->L=pre
同时当前结点p也是前驱结点pre的后继，所以前驱结点pre的右孩子指向当前结点p，pre->R=p
*/
void MiddleThreading(BThrTree p)
{
	
	if(p!=NULL)
	{
		MiddleThreading(p->L);
		//因为当前结点p的前驱已经访问到就是pre
		if(p->L==NULL)  //如果当前结点没有左孩子，p->L线索化指向前驱结点pre
		{
			p->Ltag=thread;
			p->L=pre;
		}
		//因为当前结点p的后继还没有访问到，所以只能对它的前驱结点pre做判断
		if(pre!=NULL && pre->R==NULL)  //pre初始是NULL，当找到第一个结点时，pre还没有赋值还是NULL，所以必须在pre->R==NULL之前先判断一下；如果前驱结点没有右孩子，则pre->R线索化指向pre的后继结点也就是当前结点p
		{
			pre->Rtag=thread;
			pre->R=p;
		}
		pre=p;  //处理完当前结点p之后处理下一个结点，所以当前结点变成pre结点
		MiddleThreading(p->R);
	}
}
//中序遍历二叉线索树
void MiddleOrderTraverse(BThrTree T)
{
	BThrTree p;
	p=T;  //p指向根节点
	while(p!=NULL)  //空树或者遍历结束p回到T结束，因为遍历完所有结点，中序遍历的最后一个结点指向头结点
	{
		while(p->Ltag==child)  //循环找到以p为根节点的左子树的第一个结点，也就是最左的那个结点
			p=p->L;
		cout<<p->data;
		while(p->Rtag==thread && p->R!=NULL)  //打印完左孩子，打印中间结点，如果没有右孩子一直打印中间结点，并且不是指向头结点，否则打印出错，因为头结点没有数据域
		{
			p=p->R;
			cout<<p->data;
		}
		p=p->R;  //打印完左孩和中间结点，p进至右子树根，继续上面的操作，因为中序遍历是一直左中右遍历的顺序
	}
	return;
}
int main()
{
	BThrTree T;
	//输入ab#d##c##
	CreateBThrTree(&T);
	MiddleThreading(T);
	MiddleOrderTraverse(T);
	return 0;
}

