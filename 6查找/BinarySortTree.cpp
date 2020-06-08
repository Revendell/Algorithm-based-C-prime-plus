#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef char Elemtype;
//二叉链表结点结构定义
typedef struct Node  //结点结构
{
	Elemtype data;  //结点数据
	struct Node* L;  //左孩子指针
	struct Node* R;  //右孩子指针
}Node, * BTree;
//按前序输入二叉树中结点的值，#表示空树，构造二叉链表表示二叉树T
void CreateBTree(BTree* T)
{
	Elemtype e;
	cin >> e;
	if (e == '#')
		*T = NULL;
	else
	{
		(*T) = (Node*)malloc(sizeof(Node));
		(*T)->data = e;
		CreateBTree(&(*T)->L);
		CreateBTree(&(*T)->R);
	}
}
//二叉排序树查找操作
int SearchBST(BTree T, int key, BTree f, BTree* p)  //T为根节点，key为查找数，f指向T的父结点（为了插入时找到父节点方便插入为子节点），p为查找成功后的结点，用*p的原因是传引用改变p的值返回
{
	if (T == NULL)  //查找不成功，返回的结点p指向最后的叶子结点f
	{
		*p = f;
		return FALSE;
	}
	else if (key == T->data)
	{
		*p = T;
		return TRUE;
	}
	else if (key < T->data)
		return SearchBST(T->L, key, T, p);  //在左子树查找
	else
		return SearchBST(T->R, key, T, p);  //在右子树查找
}
//二叉排序树插入操作
int InsertBST(BTree* T, int key)
{
	BTree p, s;
	if (SearchBST(*T, key, NULL, &p) == NULL)  //查找不成功，插入key结点，用*T的原因是插入结点改变T的整个结果返回
	{
		s = (Node*)malloc(sizeof(Node));
		s->data = key;
		s->L = s->R = NULL;
		if (p == NULL)  //T树为空，创建新根节点
			*T = s;
		else if (key < p->data)  //插入s为左孩子
			p->L = s;
		else
			p->R = s;
		return TRUE;
	}
	else
		return FALSE;
}
//找到key元素的结点并进入Delete函数删除该结点
/*
删除结点三种情况进行分析：
叶子结点：
仅有左或右子树结点：
左右子树都有结点：
*/
int Delete(BTree* p)
{
	BTree q, s;
	//右子树为空，只需将该结点的左子树重接上去，该结点删除free
	if ((*p)->R == NULL)
	{
		q = *p;
		*p = (*p)->L;
		free(q);
	}
	//左子树为空，只需将该结点的右子树重接上去，该结点删除free
	else if ((*p)->L == NULL)
	{
		q = *p;
		*p = (*p)->R;
		free(q);
	}
	else  //左右子树都不为空
	{
		q = *p;
		s = (*p)->L;
		while ((s->R) != NULL)  //找到删除结点*p的左孩子的最右结点s
		{
			q = s;
			s = s->R;
		}
		(*p)->data = s->data;  //将删除结点*p的左孩子的最右结点s的值替代删除结点*p的值
		if (q != *p)  //这种情况是删除结点*p的左孩子有右子树，因为删除结点*p的左孩子的最右结点s的值替代删除结点*p的值，那么s->L替代s结点，所以q->R=s->L
		{
			q->R = s->L;
		}
		else  //这种情况是删除结点*p的左孩子没有右子树，q就是*p要删除的结点，所以q->L = s->L
		{
			q->L = s->L;
		}
		free(s);  //释放s结点
	}
	return TRUE;
}
//二叉排序树删除操作
int DeleteBST(BTree* T, int key)
{
	if ((*T) == NULL)  //不存在key的元素
		return FALSE;
	else
	{
		//找到key元素的结点并进入Delete函数删除该结点
		if (key == (*T)->data)
			return Delete(T);
		else if (key < (*T)->data)  //如果key小于(*T)->data，从左子树找
			return DeleteBST(&(*T)->L, key);
		else    //如果key大于(*T)->data，从右子树找
			return DeleteBST(&(*T)->R, key);
	}
}
int main()
{
	BTree T;
	//输入d##
	CreateBTree(&T);
	InsertBST(&T, 'b');
	cout << T->L->data << endl;
	InsertBST(&T, 'e');
	InsertBST(&T, 'f');
	InsertBST(&T, 'c');
	InsertBST(&T, 'a');
	DeleteBST(&T, 'b');
	cout << T->L->data << endl;
	return 0;
}