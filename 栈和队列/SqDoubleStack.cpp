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
//初始化顺序存储结构的栈
Status InitStack(SqDoubleStack *S)
{
	S->top1=-1;
	S->top2=MaxSize;
	return TRUE;
}
//获取栈顶元素,stackNumber用来标记栈号
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
//将元素e进栈，stackNumber用来标记进栈的栈号
Status Push(SqDoubleStack *S,Elemtype e,int stackNumber)
{
	if(S->top1+1==S->top2)//栈已满不能push新元素了
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
//将栈顶元素e出栈，stackNumber用来标记出栈的栈号
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