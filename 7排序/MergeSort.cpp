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
//将有序的TR2[s..m]和TR2[m+1..t]合并为有序的TR1[s..t]
void Merge(int SR[], int TR[], int s, int m, int t)
{
	int i, j, k = s;  //k指向TR的下标，i指向SR从s到m的下标，j指向SR从m+1到t的下标
	for (i = s, j = m + 1; i <= m && j <= t; k++)
	{
		if (SR[i] < SR[j])
			TR[k] = SR[i++];
		else
			TR[k] = SR[j++];
	}
    //将剩余的SR[i..m]复制到TR
	if (i <= m)
		for (int l = 0; l <= m - i; l++)
			TR[k+l] = SR[i+l];
	//将剩余的SR[j..n]复制到TR
	if (j <= t)
		for (int l = 0; l <= t - i; l++)
			TR[k+l] = SR[j+l];
}
//将SR[s..t]归并排序为有序的TR1[s..t]
void MSort(int SR[], int TR1[], int s, int t)
{
	int m;
	int TR2[MaxSize + 1];
	if (s == t)
		TR1[s] = SR[s];
	else
	{
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);  //递归将SR[s..m]递归为有序的TR2[s..m]
		MSort(SR, TR2, m+1, t);  //递归将SR[m+1..t]递归为有序的TR2[m+1..t]
		Merge(TR2, TR1, s, m, t);  //将有序的TR2[s..m]和TR2[m+1..t]合并为有序的TR1[s..t]
	}
}
void MergeSort(SqList* L)
{
	MSort(L->r, L->r, 1, L->length);
}
int main()
{
	SqList L;
	int r[MaxSize] = { 9,8,7,6,5,4,3,2,1 };
	L.length = 9;
	for (int i = 0; i < L.length; i++)
		L.r[i + 1] = r[i];
	MergeSort(&L);
	for (int i = 1; i <= L.length; i++)
	{
		cout << L.r[i] << endl;
	}
	return 0;
}