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
//����˳���L���ӱ�ļ�¼���������¼��λ�����������ڵ�λ��
//��ʱ������֮ǰ�ļ�¼������������֮��ļ�¼��С����
int Partition(SqList* L, int low, int high)
{
	int pivotkey;
	pivotkey = L->r[low];  //���ӱ�ĵ�һ����¼�������¼
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
//��˳���L�е�������L->r[low..high]����������
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