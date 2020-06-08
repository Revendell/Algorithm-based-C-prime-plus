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
//已知L->r[s...m]中记录的关键字除L->r[s]之外均满足堆的定义
//因此从s的两个孩子结点j=2*s和j+1找到最大的替换，替换后的孩子结点需要继续考虑它是否是该子树最大的根结点直到最后结点m结点
void HeapAdjust(SqList* L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	for (j = 2 * s; j <= m; j *= 2)
	{
		//沿着s关键字较大的孩子(j=2*s和j+1中较大的一个)结点向下筛选
		if (j < m && L->r[j] < L->r[j + 1])
			j++;
		//如果双亲结点s比孩子结点大就算了
		if (temp >= L->r[j])
			break;
		//找到较大的孩子结点值替换双亲结点，并且用s标记此结点下标，等会用双亲结点值换回去
		L->r[s] = L->r[j];
		s = j;
	}
	L->r[s] = temp;
}
void HeapSort(SqList* L)
{
	int i;
	for (i = L->length / 2; i > 0; i--)
		HeapAdjust(L, i, L->length);  //必须从最大根结点开始，不断从最下面往上选出最大值，形成大顶堆
	for (i = L->length; i > 1; i--)
	{
		swap(L, 1, i);  //将堆顶记录也就是堆中最大值和当前未经排序子序列的最后一个记录交换，将最大值移到了最后从而排序
		HeapAdjust(L, 1, i - 1);  //堆顶记录和最后记录交换后，除最后已经排序的元素其他元素再重新形成大顶堆
	}
}
int main()
{
	SqList L;
	int r[MaxSize] = { 9,8,7,6,5,4,3,2,1 };
	L.length = 9;
	for (int i = 0; i < L.length; i++)
		L.r[i + 1] = r[i];
	HeapSort(&L);
	for (int i = 1; i <= L.length; i++)
	{
		cout << L.r[i] << endl;
	}
	return 0;
}
