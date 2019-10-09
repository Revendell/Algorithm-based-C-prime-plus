#include<iostream>
using namespace std;
#define MaxSize 20    //存储最大空间
#define TRUE 1
#define FALSE 0
typedef int Status;    //函数的类型，函数结果状态的返回，TRUE成功FALSE失败
typedef int ElemType;    //定义线性表元素类型
typedef struct SequenceList
{
	ElemType data[MaxSize];	    //数组存储线性表
	int length;       //线性表当前长度
}SqList; //SqList=struct SequenceList=SequenceList
//初始化线性表
Status InitList(SqList *L)
{
	L->length=0;
	return TRUE;
}
//判断线性表是否为空
Status ListEmpty(SqList L)
{
	if(L.length==0)
		return FALSE;
	else
	    return TRUE;
}
//清空线性表
Status ClearList(SqList *L)
{
	L->length=0;
	return TRUE;

}
//获得线性表第i个位置元素返回给e
Status GetElem(SqList L,int i,ElemType *e)
{
	if(i<1 || i>L.length || L.length==0)
		return FALSE;
	*e=L.data[i-1];
	return TRUE;
}
//在线性表中找到与e相同的元素返回位置
int LocateElem(SqList L,ElemType e)
{
    for(int j=0;j<L.length;j++)
	{
		if(L.data[j]==e)
			return j+1;
	}
	return FALSE;
}
//在线性表中第i个位置插入e
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
//删除线性表中第i个位置元素并将e返回
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
//返回线性表的元素个数
int ListLength(SqList L)
{
    return L.length;
}
//将线性表Lb中但不在La中的元素插入La中
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