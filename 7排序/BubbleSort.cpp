#include<iostream>
using namespace std;
#define MaxSize 10
#define TRUE 1
#define FALSE 0
typedef struct  
{
	int r[MaxSize];
	int length;
}SqList;
void swap(SqList* L, int i, int j)
{
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}
//ð����������棬��˳���L����������
void BubbleSort0(SqList* L)
{
	int i, j;
	for (i = 1; i < L->length; i++)
	{
		for (j = i + 1; j <= L->length; j++)
		{
			if (L->r[i] > L->r[j])
				swap(L, i, j);
		}
	}
}
//���ڵ�ð�����򣬽�С������ͬ���ݰ�������������
void BubbleSort1(SqList* L)
{
	int i, j;
	for (i = 1; i < L->length; i++)
	{
		for (j = L->length - 1; j >= i; j--)
		{
			if (L->r[j] > L->r[j + 1])
				swap(L, j, j + 1);
		}
	}
}
//ð�������Ż������û���κ����ݽ���˵�������Ѿ����򣬲���Ҫ�ټ��������ѭ���жϹ����ˣ��������һ����Ǳ���flag��ʵ����һ�㷨�ĸĽ�
void BubbleSort2(SqList* L)
{
	int i, j;
	int flag = TRUE;
	for (i = 1; i < L->length && flag; i++)
	{
		flag = FALSE;
		for (j = L->length - 1; j >= i; j--)
		{
			if (L->r[j] > L->r[j + 1])
			{
				swap(L, j, j + 1);
				flag = TRUE;
			}
		}
	}
}
int main()
{
	SqList L;
	int r[MaxSize] = { 9,8,7,6,5,4,3,2,1 };
	L.length = 9;
	for (int i = 0; i < L.length; i++)
		L.r[i + 1] = r[i];
	BubbleSort2(&L);
	for (int i = 1; i <= L.length; i++)
	{
		cout << L.r[i] << endl;
	}
	return 0;
}
