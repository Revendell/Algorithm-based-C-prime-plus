#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define LH 1  //left high���Ϊ1
#define EH 0  //equal high�ȸ�Ϊ0
#define RH -1  //right high�Ҹ�Ϊ-1
typedef char Elemtype;
//����������ṹ����
typedef struct Node  //���ṹ
{
	Elemtype data;  //�������
	int bf;  //����ƽ������bf=�������߶�-�������߶�
	struct Node* L;  //����ָ��
	struct Node* R;  //�Һ���ָ��
}Node, * BTree;
//����p���Ϊ���Ľ����������
void R_Rotate(BTree* p)
{
	BTree pL;
	pL = (*p)->L;
	(*p)->L = pL->R;
	pL->R = (*p);
	*p = pL;
}
//����p���Ϊ���Ľ����������
void L_Rotate(BTree* p)
{
	BTree pR;
	pR = (*p)->R;
	(*p)->R = pR->L;
	pR->L = (*p);
	*p = pR;
}
//��ƽ����ת����
/*
��ƽ�⴦��ǰ������TΪ�����Ķ�������T��bfΪ1��ߣ���Ȼ��T������������һ����㣬ʹ��T��bf����1���������Ͳ�ƽ��
�����¼����������
T�����ӽ��bfΪLH��ߣ����½�������T�����ӵ��������ϣ�Ҫ����������Ҳ����T��T�����Ӷ���LHͬ������ֻ��Ҫ����������
T�����ӽ��bfΪRH�Ҹߣ����½�������T�����ӵ��������ϣ�Ҫ˫��������������������Ҳ����TΪLH��T��������RH��ͬ������Ҫ˫������
����T�����ӽ��ΪRH�������������
һT����L����������LrΪLH:��L�����ٶ�T������T��bf��ΪRH��L��bf��ΪEH
��T����L����������LrΪEH:��L�����ٶ�T������T��bf��ΪEH��L��bf��ΪEH
��T����L����������LrΪRH:��L�����ٶ�T������T��bf��ΪEH��L��bf��ΪLH
���Ͼ��ǰ���Ҫ��ƽ������д������������
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
//��ƽ����ת����
/*
��ƽ�⴦��ǰ������TΪ�����Ķ�������T��bfΪ-1�Ҹߣ���Ȼ��T������������һ����㣬ʹ��T��bfС��-1���������Ͳ�ƽ��
�����¼����������
T���Һ��ӽ��bfΪRH�Ҹߣ����½�������T���Һ��ӵ��������ϣ�Ҫ����������Ҳ����T��T���Һ��Ӷ���RHͬ������ֻ��Ҫ����������
T���Һ��ӽ��bfΪLH��ߣ����½�������T���Һ��ӵ��������ϣ�Ҫ˫��������������������Ҳ����TΪRH��T��������LH��ͬ������Ҫ˫������
����T���Һ��ӽ��ΪRH�������������
һT�Һ���L����������RlΪRH:��L�����ٶ�T������T��bf��ΪLH��R��bf��ΪEH
��T�Һ���L����������RlΪEH:��L�����ٶ�T������T��bf��ΪEH��R��bf��ΪEH
��T�Һ���L����������RlΪLH:��L�����ٶ�T������T��bf��ΪEH��R��bf��ΪRH
���Ͼ��ǰ���Ҫ��ƽ������д������������
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
//�ڶ���ƽ�����в��ϵݹ���ò�����e������taller��ӦT�Ƿ񳤸�
int InsertAVL(BTree* T, Elemtype e, int* taller)
{
	//���T���Ϊ�ղ���e��ͨ���ݹ鲻���ҵ��ʺϲ���e��Ҷ�ӽ��λ�ã�Ȼ�����ƽ�⴦��
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
		//T���Ѵ�����e��ͬ��Ԫ�صĽ�����ٲ���
		if (e == (*T)->data)
		{
			*taller = FALSE;
			return FALSE;
		}
		//��T�������������ʵ��Ĳ���λ��
		if (e < (*T)->data)
		{
			if (InsertAVL(&(*T)->L, e, taller) == FALSE)
				return FALSE;
			//T�в�����e��taller��ΪTRUE
			if (*taller)
			{
				//���T��ƽ���
				switch ((*T)->bf)
				{
				case LH:  //T����LH����Ҫ��e��������������Ҫ��ƽ�⴦��
					LeftBalance(T);
					*taller = FALSE;
					break;
				case EH:  //T����EH����e������������T��bf��ΪLH
					(*T)->bf = LH;
					*taller = TRUE;
					break;
				case RH:  //T����RH����e������������T��bf��ΪEH
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				}
			}
		}
		else  //��T�������������ʵ��Ĳ���λ��
		{
			if (InsertAVL(&(*T)->R, e, taller) == FALSE)
				return FALSE;
			//T�в�����e��taller��ΪTRUE
			if (*taller)
			{
				//���T��ƽ���
				switch ((*T)->bf)
				{
				case LH:  //T����LH����e������������T��bf��ΪEH
					(*T)->bf = EH;
					*taller = FALSE;
					break;
				case EH:  //T����EH����e������������T��bf��ΪRH
					(*T)->bf = RH;
					*taller = TRUE;
					break;
				case RH:  //T����RH����Ҫ��e��������������Ҫ��ƽ�⴦��
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
