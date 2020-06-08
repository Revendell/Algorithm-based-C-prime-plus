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
//交换顺序表L中子表的记录，是枢轴记录到位，并返回所在的位置
//此时在枢轴之前的记录均不大于它，之后的记录不小于它
int Partition(SqList* L, int low, int high)
{
	int pivotkey;
	pivotkey = L->r[low];  //用子表的第一个记录作枢轴记录
	while (low < high)
	{
		while (low < high && L->r[high] >= pivotkey)
			high--;
		swap(L, low, high);
		while (low < high && L->r[low] <= pivotkey)
			low++;
		swap(L, low, high);
	}
	return low;
}
//对顺序表L中的子序列L->r[low..high]作快速排序
void QSort(SqList* L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(L, low, high);
		QSort(L, low, pivot - 1);
		QSort(L, pivot + 1, high);
	}
}
void QuickSort(SqList* L)
{
	QSort(L, 1, L->length);
}
int main()
{
	SqList L;
	int r[MaxSize] = { 9,8,7,6,5,4,3,2,1 };
	L.length = 9;
	for (int i = 0; i < L.length; i++)
		L.r[i + 1] = r[i];
	QuickSort(&L);
	for (int i = 1; i <= L.length; i++)
	{
		cout << L.r[i] << endl;
	}
	return 0;
}