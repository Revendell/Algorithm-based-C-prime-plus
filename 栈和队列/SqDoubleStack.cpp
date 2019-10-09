#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define MaxSize 20
typedef int Elemtype;
typedef int Status;
typedef struct SqDoubleStack
{
	Elemtype data[MaxSize];
	int top1;
	int top2;
}SqDoubleStack;
//��ʼ��˳��洢�ṹ��ջ
Status InitStack(SqDoubleStack *S)
{
	S->top1=-1;
	S->top2=MaxSize;
	return TRUE;
}
//��ȡջ��Ԫ��,stackNumber�������ջ��
Status GetTop(SqDoubleStack S,Elemtype *e,int stackNumber)
{
	if(stackNumber==1)
	{
		if(S.top1==-1)
			return FALSE;
		*e=S.data[S.top1];
	}
	if(stackNumber==2)
	{
		if(S.top2==MaxSize-1)
			return FALSE;
		*e=S.data[S.top2];
	}
	return TRUE;
}
//��Ԫ��e��ջ��stackNumber������ǽ�ջ��ջ��
Status Push(SqDoubleStack *S,Elemtype e,int stackNumber)
{
	if(S->top1+1==S->top2)//ջ��������push��Ԫ����
		return FALSE;
	if(stackNumber==1)
	{
		S->top1++;
        S->data[S->top1]=e;
	}
	if(stackNumber==2)
	{
		S->top2--;
		S->data[S->top2]=e;
	}
	return TRUE;
}
//��ջ��Ԫ��e��ջ��stackNumber������ǳ�ջ��ջ��
Status Pop(SqDoubleStack *S,Elemtype *e,int stackNumber)
{
	if(stackNumber==1)
	{
		if(S->top1==-1)
			return FALSE;
		*e=S->data[S->top1];
		S->top1--;
	}
	if(stackNumber==2)
	{
		if(S->top2==MaxSize-1)
			return FALSE;
		*e=S->data[S->top2];
		S->top2++;
	}
	return TRUE;
}
int main()
{
	SqDoubleStack S;
	Elemtype e=1;
	int stackNumber=1;
	InitStack(&S);
	Push(&S,e,stackNumber);
	Pop(&S,&e,stackNumber);
	cout<<e<<endl;
	return 0;
}