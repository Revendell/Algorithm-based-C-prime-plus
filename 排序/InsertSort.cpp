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
//对顺序表L作直接插入排序，依次循环将每个记录插入到已经排好序的有序表中
void InsertSort(SqList* L)
{
	int i, j;
	for (i = 2; i <= L->length; i++)
	{
		if (L->r[i] < L->r[i - 1])
		{
			L->r[0] = L->r[i];
			for (j = i - 1; L->r[j] > L->r[0]; j--)
				L->r[j + 1] = L->r[j];
			L->r[j + 1] = L->r[0];
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
	InsertSort(&L);
	for (int i = 1; i <= L.length; i++)
	{
		cout << L.r[i] << endl;
	}
	return 0;
}