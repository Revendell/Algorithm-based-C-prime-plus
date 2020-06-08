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
//��֪L->r[s...m]�м�¼�Ĺؼ��ֳ�L->r[s]֮�������ѵĶ���
//��˴�s���������ӽ��j=2*s��j+1�ҵ������滻���滻��ĺ��ӽ����Ҫ�����������Ƿ��Ǹ��������ĸ����ֱ�������m���
void HeapAdjust(SqList* L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	for (j = 2 * s; j <= m; j *= 2)
	{
		//����s�ؼ��ֽϴ�ĺ���(j=2*s��j+1�нϴ��һ��)�������ɸѡ
		if (j < m && L->r[j] < L->r[j + 1])
			j++;
		//���˫�׽��s�Ⱥ��ӽ��������
		if (temp >= L->r[j])
			break;
		//�ҵ��ϴ�ĺ��ӽ��ֵ�滻˫�׽�㣬������s��Ǵ˽���±꣬�Ȼ���˫�׽��ֵ����ȥ
		L->r[s] = L->r[j];
		s = j;
	}
	L->r[s] = temp;
}
void HeapSort(SqList* L)
{
	int i;
	for (i = L->length / 2; i > 0; i--)
		HeapAdjust(L, i, L->length);  //�����������㿪ʼ�����ϴ�����������ѡ�����ֵ���γɴ󶥶�
	for (i = L->length; i > 1; i--)
	{
		swap(L, 1, i);  //���Ѷ���¼Ҳ���Ƕ������ֵ�͵�ǰδ�����������е����һ����¼�����������ֵ�Ƶ������Ӷ�����
		HeapAdjust(L, 1, i - 1);  //�Ѷ���¼������¼�����󣬳�����Ѿ������Ԫ������Ԫ���������γɴ󶥶�
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
