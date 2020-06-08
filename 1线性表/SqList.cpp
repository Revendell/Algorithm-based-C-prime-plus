#include<iostream>
using namespace std;
#define MaxSize 20    //�洢���ռ�
#define TRUE 1
#define FALSE 0
typedef int Status;    //���������ͣ��������״̬�ķ��أ�TRUE�ɹ�FALSEʧ��
typedef int ElemType;    //�������Ա�Ԫ������
typedef struct SequenceList
{
	ElemType data[MaxSize];	    //����洢���Ա�
	int length;       //���Ա�ǰ����
}SqList; //SqList=struct SequenceList=SequenceList
//��ʼ�����Ա�
Status InitList(SqList *L)
{
	L->length=0;
	return TRUE;
}
//�ж����Ա��Ƿ�Ϊ��
Status ListEmpty(SqList L)
{
	if(L.length==0)
		return FALSE;
	else
	    return TRUE;
}
//������Ա�
Status ClearList(SqList *L)
{
	L->length=0;
	return TRUE;

}
//������Ա��i��λ��Ԫ�ط��ظ�e
Status GetElem(SqList L,int i,ElemType *e)
{
	if(i<1 || i>L.length || L.length==0)
		return FALSE;
	*e=L.data[i-1];
	return TRUE;
}
//�����Ա����ҵ���e��ͬ��Ԫ�ط���λ��
int LocateElem(SqList L,ElemType e)
{
    for(int j=0;j<L.length;j++)
	{
		if(L.data[j]==e)
			return j+1;
	}
	return FALSE;
}
//�����Ա��е�i��λ�ò���e
Status ListInsert(SqList *L,int i,ElemType e)
{
    if(i>L->length+1 || L->length==MaxSize || i<1)
		return FALSE;
	if(i<=L->length)
	{
		for(int j=L->length-1;j>=i-1;j--)
		{
			L->data[j+1]=L->data[j];
		}
		L->data[i-1]=e;
	}
	else{
		L->data[i-1]=e;
	}
	L->length++;
	return TRUE;
}
//ɾ�����Ա��е�i��λ��Ԫ�ز���e����
Status ListDelete(SqList *L,int i,ElemType *e)
{
	if(i<1 || i>L->length || L->length==0)
		return FALSE;
	*e=L->data[i-1];
	if(i<L->length)
	{
		for(int j=i;j<=L->length-1;j++)
			L->data[j-1]=L->data[j];
	}
	L->length--;
    return TRUE;
}
//�������Ա��Ԫ�ظ���
int ListLength(SqList L)
{
    return L.length;
}
//�����Ա�Lb�е�����La�е�Ԫ�ز���La��
void unionL(SqList *La,SqList Lb)
{
    ElemType e;
	int i,j,La_len,Lb_len;
	La_len=ListLength(*La);
	Lb_len=ListLength(Lb);
	for(i=0;i<Lb_len;i++)
	{
		GetElem(Lb,i,&e);
		if(LocateElem(*La,e)==FALSE)
			ListInsert(La,++La_len,e);
	}
}
int main()
{
    SqList La;
	InitList(&La);
	ElemType e=1;
	ListInsert(&La,1,e);
	for(int i=0;i<ListLength(La);i++)
		cout<<La.data[i]<<endl;
	return 0;
}