#include<iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define MaxSize 20
typedef int Elemtype;
typedef int Status;
typedef struct SqStack
{
	Elemtype data[MaxSize];
	int top;
}SqStack;
//初始化顺序存储结构的栈
Status InitStack(SqStack *S)
{
	S->top=-1;
	return TRUE;
}
//获取栈顶元素
Status GetTop(SqStack S,Elemtype *e)
{
	if(S.top==-1)
		return FALSE;
	*e=S.data[S.top];
	return TRUE;
}
//将元素e进栈，栈顶指针top++
Status Push(SqStack *S,Elemtype e)
{
	if(S->top==MaxSize-1)
		return FALSE;
	S->top++;
	S->data[S->top]=e;
	return TRUE;
}
//将栈顶元素e出栈，栈顶指针top--
Status Pop(SqStack *S,Elemtype *e)
{
	if(S->top==-1)
		return FALSE;
	*e=S->data[S->top];
	S->top--;
	return TRUE;
}
int main()
{
	SqStack S;
	Elemtype e=1;
    InitStack(&S);
    Push(&S,e);
	Pop(&S,&e);
    cout<<e<<endl;
	return 0;
}