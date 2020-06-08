#include<iostream>
#include<algorithm>
using namespace std;
#define Max 100
int *F;  //�洢Fibonacci��
//����Fibonacci����
void Fibonacci(int n)
{
	F=(int*)malloc(n*sizeof(int));
    if(n>2)
	{
		F[0]=0;
		F[1]=1;
		int i=2;
		while(i<=n)
		{
			F[i]=F[i-1]+F[i-2];
			i++;
		}
	}
}
int FibonacciSearch(int *a,int n,int key)
{
	int low=0,mid,high=n-1,i,k=0;
	//�ҵ�nλ��쳲��������е�λ����F[k-1]<=n<F[k]
	while(F[k]<=n)
		k++;
	//����������ֵ��ȫ��Ҳ��������a�±��n��F[k]-1���a[n-1]
	for(i=n;i<F[k];i++)
		a[i]=a[n-1];
	//쳲������������Իƽ�ָ����Ϊ�ָF[k]=F[k-1]+F[k-2]Ҳ���Ƕ�F[k]�ָ��0��F[k-1]-1��F[k-1]�����ֺ�F[k-1]��F[k]-1��F[k-2]����������
	//���key<mid���0��F[k-1]-1�β��ң�Ҳ���ǽ���һ��F[k-1]=F[k-2]+F[k-3]�ֳ���0��F[k-2]-1��F[k-2]��F[k-1]-1������k=k-1
    //���key>mid���F[k-1]��F[k]-1�β��ң�Ҳ���ǽ���һ��F[k-2]=F[k-3]+F[k-4]�ֳ���0��F[k-2]-1��F[k-2]��F[k-1]-1������k=k-2
	while(low<=high)
	{
		mid=low+F[k-1]-1;
		if(key<a[mid])
		{
			high=mid-1;
			k=k-1;
		}
		else if(key>a[mid])
		{
			low=mid+1;
			k=k-2;
		}
		else
		{
			//���midС��n����ֱ�ӷ���mid
			if(mid<=n-1)
				return mid;
			//���mid����n����ֱ�ӷ���n-1˵���ҵ���λ������λ��
			else
				return n-1;
		}
	}
	return 0;	
}
int main()
{
	int a[Max]={2,5,6,8,3,1,17,39,70,90};
	int n=10,key=1;
	sort(a,a+n);
	Fibonacci(n);
	cout<<FibonacciSearch(a,n,key)<<endl;
	return 0;
}