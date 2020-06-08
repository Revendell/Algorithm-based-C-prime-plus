#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define LH 1  //left high左高为1
#define EH 0  //equal high等高为0
#define RH -1  //right high右高为-1
typedef char Elemtype;
//二叉链表结点结构定义
typedef struct Node  //结点结构
{
	Elemtype data;  //结点数据
	int bf;  //结点的平衡因子bf=左子树高度-右子树高度
	struct Node* L;  //左孩子指针
	struct Node* R;  //右孩子指针
}Node, * BTree;
//对以p结点为根的结点右旋操作
void R_Rotate(BTree* p)
{
	BTree pL;
	pL = (*p)->L;
	(*p)->L = pL->R;
	pL->R = (*p);
	*p = pL;
}
//对以p结点为根的结点左旋操作
void L_Rotate(BTree* p)
{
	BTree pR;
	pR = (*p)->R;
	(*p)->R = pR->L;
	pR->L = (*p);
	*p = pR;
}
//左平衡旋转处理
/*
左平衡处理前提是以T为根结点的二叉树，T的bf为1左高，仍然在T的左子树插入一个结点，使得T的bf大于1，二叉树就不平衡
分以下几种情况处理：
T的左孩子结点bf为LH左高：则新结点插入在T的左孩子的左子树上，要单右旋处理，也就是T和T的左孩子都是LH同符号则只需要单右旋处理
T的左孩子结点bf为RH右高：则新结点插入在T的左孩子的右子树上，要双旋处理先左旋再右旋，也就是T为LH和T的左孩子是RH不同符号需要双旋处理
对于T的左孩子结点为RH分三种情况处理：
一T左孩子L的右子树根Lr为LH:对L左旋再对T右旋，T的bf变为RH，L的bf变为EH
二T左孩子L的右子树根Lr为EH:对L左旋再对T右旋，T的bf变为EH，L的bf变为EH
三T左孩子L的右子树根Lr为RH:对L左旋再对T右旋，T的bf变为EH，L的bf变为LH
以上就是把需要左平衡的所有处理情况包括了
*/
void LeftBalance(BTree* T)
{
	BTree TL, TLr;
	TL = (*T)->L;
	switch (TL->bf)
	{
	case LH:
		(*T)->bf = TL->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		TLr = TL->R;
		switch (TLr->bf)
		{
		case LH:
			(*T)->bf = RH;
			TL->bf = EH;
			break;
		case EH:
			(*T)->bf = TL->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			TL->bf = LH;
			break;
		default:
			break;
		}
		TLr->bf = EH;
		L_Rotate(&(*T)->L);
		R_Rotate(T);
	default:
		break;
	}
}
//右平衡旋转处理
/*
右平衡处理前提是以T为根结点的二叉树，T的bf为-1右高，仍然在T的右子树插入一个结点，使得T的bf小于-1，二叉树就不平衡
分以下几种情况处理：
T的右孩子结点bf为RH右高：则新结点插入在T的右孩子的右子树上，要单右旋处理，也就是T和T的右孩子都是RH同符号则只需要单左旋处理
T的右孩子结点bf为LH左高：则新结点插入在T的右孩子的左子树上，要双旋处理先右旋再左旋，也就是T为RH和T的左孩子是LH不同符号需要双旋处理
对于T的右孩子结点为RH分三种情况处理：
一T右孩子L的左子树根Rl为RH:对L右旋再对T左旋，T的bf变为LH，R的bf变为EH
二T右孩子L的左子树根Rl为EH:对L右旋再对T左旋，T的bf变为EH，R的bf变为EH
三T右孩子L的左子树根Rl为LH:对L右旋再对T左旋，T的bf变为EH，R的bf变为RH
以上就是把需要左平衡的所有处理情况包括了
*/
void RightBalance(BTree* T)
{
	BTree TR, TRl;
	TR = (*T)->R;
	switch (TR->bf)
	{
	case RH:
		(*T)->bf = TR->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		TRl = TR->L;
		switch (TRl->bf)
		{
		case RH:
			(*T)->bf = LH;
			TR->bf = EH;
			break;
		case EH:
			(*T)->bf = TR->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			TR->bf = RH;
			break;
		default:
			break;
		}
		TRl->bf = EH;
		R_Rotate(&(*T)->R);
		L_Rotate(T);
	default:
		break;
	}
}
//在二叉平衡树中不断递归调用插入结点e，布尔taller反应T是否长高
int InsertAVL(BTree* T, Elemtype e, int* taller)
{
	//如果T结点为空插入e，通过递归不断找到适合插入e的叶子结点位置，然后就行平衡处理
	if (*T == NULL)
	{
		*T = (Node*)malloc(sizeof(Node));
		(*T)->data = e;
		(*T)->L = (*T)->R = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		//T中已存在与e相同的元素的结点则不再插入
		if (e == (*T)->data)
		{
			*taller = FALSE;
			return FALSE;
		}
		//在T的左子树搜索适当的插入位置
		if (e < (*T)->data)
		{
			if (InsertAVL(&(*T)->L, e, taller) == FALSE)
				return FALSE;
			//T中插入结点e后taller变为TRUE
			if (*taller)
			{
				//检查T的平衡度
				switch ((*T)->bf)
				{
				case LH:  //T本来LH，又要将e插入左子树，需要左平衡处理
					LeftBalance(T);
					*taller = FALSE;
					break;
				case EH:  //T本来EH，将e插入左子树，T的bf变为LH
					(*T)->bf = LH;
					*taller = TRUE;
					break;
				case RH:  //T本来RH，将e插入左子树，T的bf变为EH
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				}
			}
		}
		else  //在T的右子树搜索适当的插入位置
		{
			if (InsertAVL(&(*T)->R, e, taller) == FALSE)
				return FALSE;
			//T中插入结点e后taller变为TRUE
			if (*taller)
			{
				//检查T的平衡度
				switch ((*T)->bf)
				{
				case LH:  //T本来LH，将e插入右子树，T的bf变为EH
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				case EH:  //T本来EH，将e插入右子树，T的bf变为RH
					(*T)->bf = RH;
					*taller = TRUE;
					break;
				case RH:  //T本来RH，又要将e插入右子树，需要右平衡处理
					RightBalance(T);
					*taller = FALSE;
					break;
				}
			}
		}
	}
	return TRUE;
}
int main()
{
	BTree T=NULL;
	int taller;
	char a[10] = { 'd','b','e','f','c','a','g','h' };
	for (int i = 0; i < 8; i++)
	{
		InsertAVL(&T, a[i], &taller);
		cout << T->bf << endl;
	}
	return 0;
}
