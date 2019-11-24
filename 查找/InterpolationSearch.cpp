#include<iostream>
#include<algorithm>
using namespace std;
#define Max 100
int InterpolationSearch(int *a,int n,int key)
{
	int low=0,high=n-1,mid;
	while(low<=high)
	{
		mid=low+(key-a[low])/(a[high]-a[low])*(high-low);
		if(key<a[mid])
			high=mid-1;
		else if(key>a[mid])
			low=mid+1;
		else
			return mid;
	}
	return 0;
}
int main()
{
	int a[Max]={2,5,6,8,3,1};
	int n=6,key=2;
	sort(a,a+n);
	cout<<InterpolationSearch(a,n,key)<<endl;
	return 0;

}