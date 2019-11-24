#include<iostream>
#include<algorithm>
using namespace std;
#define Max 100
int *F;  //存储Fibonacci数
//生成Fibonacci数组
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
	//找到n位于斐波那契数列的位置且F[k-1]<=n<F[k]
	while(F[k]<=n)
		k++;
	//将不满的数值补全，也就是数组a下标从n到F[k]-1填充a[n-1]
	for(i=n;i<F[k];i++)
		a[i]=a[n-1];
	//斐波那契查找是以黄金分割点作为分割，F[k]=F[k-1]+F[k-2]也就是对F[k]分割成0到F[k-1]-1共F[k-1]个数字和F[k-1]到F[k]-1共F[k-2]个数字两段
	//如果key<mid则对0到F[k-1]-1段查找，也就是将这一段F[k-1]=F[k-2]+F[k-3]分成了0到F[k-2]-1和F[k-2]到F[k-1]-1，所以k=k-1
    //如果key>mid则对F[k-1]到F[k]-1段查找，也就是将这一段F[k-2]=F[k-3]+F[k-4]分成了0到F[k-2]-1和F[k-2]到F[k-1]-1，所以k=k-2
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
			//如果mid小于n，则直接返回mid
			if(mid<=n-1)
				return mid;
			//如果mid大于n，则直接返回n-1说明找到的位于填充的位置
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