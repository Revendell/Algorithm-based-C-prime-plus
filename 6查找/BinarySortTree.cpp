#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
typedef char Elemtype;
//����������ṹ����
typedef struct Node  //���ṹ
{
	Elemtype data;  //�������
	struct Node* L;  //����ָ��
	struct Node* R;  //�Һ���ָ��
}Node, * BTree;
//��ǰ������������н���ֵ��#��ʾ������������������ʾ������T
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
//�������������Ҳ���
int SearchBST(BTree T, int key, BTree f, BTree* p)  //TΪ���ڵ㣬keyΪ��������fָ��T�ĸ���㣨Ϊ�˲���ʱ�ҵ����ڵ㷽�����Ϊ�ӽڵ㣩��pΪ���ҳɹ���Ľ�㣬��*p��ԭ���Ǵ����øı�p��ֵ����
{
	if (T == NULL)  //���Ҳ��ɹ������صĽ��pָ������Ҷ�ӽ��f
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
		return SearchBST(T->L, key, T, p);  //������������
	else
		return SearchBST(T->R, key, T, p);  //������������
}
//�����������������
int InsertBST(BTree* T, int key)
{
	BTree p, s;
	if (SearchBST(*T, key, NULL, &p) == NULL)  //���Ҳ��ɹ�������key��㣬��*T��ԭ���ǲ�����ı�T�������������
	{
		s = (Node*)malloc(sizeof(Node));
		s->data = key;
		s->L = s->R = NULL;
		if (p == NULL)  //T��Ϊ�գ������¸��ڵ�
			*T = s;
		else if (key < p->data)  //����sΪ����
			p->L = s;
		else
			p->R = s;
		return TRUE;
	}
	else
		return FALSE;
}
//�ҵ�keyԪ�صĽ�㲢����Delete����ɾ���ý��
/*
ɾ���������������з�����
Ҷ�ӽ�㣺
���������������㣺
�����������н�㣺
*/
int Delete(BTree* p)
{
	BTree q, s;
	//������Ϊ�գ�ֻ�轫�ý����������ؽ���ȥ���ý��ɾ��free
	if ((*p)->R == NULL)
	{
		q = *p;
		*p = (*p)->L;
		free(q);
	}
	//������Ϊ�գ�ֻ�轫�ý����������ؽ���ȥ���ý��ɾ��free
	else if ((*p)->L == NULL)
	{
		q = *p;
		*p = (*p)->R;
		free(q);
	}
	else  //������������Ϊ��
	{
		q = *p;
		s = (*p)->L;
		while ((s->R) != NULL)  //�ҵ�ɾ�����*p�����ӵ����ҽ��s
		{
			q = s;
			s = s->R;
		}
		(*p)->data = s->data;  //��ɾ�����*p�����ӵ����ҽ��s��ֵ���ɾ�����*p��ֵ
		if (q != *p)  //���������ɾ�����*p������������������Ϊɾ�����*p�����ӵ����ҽ��s��ֵ���ɾ�����*p��ֵ����ôs->L���s��㣬����q->R=s->L
		{
			q->R = s->L;
		}
		else  //���������ɾ�����*p������û����������q����*pҪɾ���Ľ�㣬����q->L = s->L
		{
			q->L = s->L;
		}
		free(s);  //�ͷ�s���
	}
	return TRUE;
}
//����������ɾ������
int DeleteBST(BTree* T, int key)
{
	if ((*T) == NULL)  //������key��Ԫ��
		return FALSE;
	else
	{
		//�ҵ�keyԪ�صĽ�㲢����Delete����ɾ���ý��
		if (key == (*T)->data)
			return Delete(T);
		else if (key < (*T)->data)  //���keyС��(*T)->data������������
			return DeleteBST(&(*T)->L, key);
		else    //���key����(*T)->data������������
			return DeleteBST(&(*T)->R, key);
	}
}
int main()
{
	BTree T;
	//����d##
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