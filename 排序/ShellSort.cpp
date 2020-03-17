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
void ShellSort(SqList* L)
{
	int i, j;
	int increment = L->length;  //��ʼ��������L���ȣ�����increment=length/3+1����С����������increment = increment/3+1�ķ�ʽ
	while (increment > 1)
	{
		increment = increment / 3 + 1;
		//�±��1��9����0��ʼ�ģ�����i=increment+1
		for (i = increment + 1; i <= L->length; i++)
		{
			if (L->r[i] < L->r[i - increment])
			{
				L->r[0] = L->r[i];
				for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
					L->r[j + increment] = L->r[j];
				L->r[j + increment] = L->r[0];
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
	ShellSort(&L);
	for (int i = 1; i <= L.length; i++)
	{
		cout << L.r[i] << endl;
	}
	return 0;
}