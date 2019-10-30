#include<iostream>
using namespace std;
#define MaxSize 100
typedef struct STR
{
	char data[MaxSize];    //数组存储串从下标1开始，下标0为空
	int length;
}STR;
//向串T插入元素e
void Insert(STR *T,char e)
{
    T->data[T->length+1]=e;
	T->length++;
}
//通过计算返回子串T的next数组，时间复杂度O(m)，m是子串T的长度
void get_next(STR T,int *next)
{
	int i,j;
	i=1;  //i是后缀字符的下标，从1到length
	j=0;  //j是前缀字符的下标，初始化0，因为i与j不匹配回溯j+1进行比较，j+1最小值是1
	next[1]=0;
	while(i<T.length)
	{
		if(j==0||T.data[i]==T.data[j])//前缀字符下标j一直回溯到0，重新开始匹配
		{
			i++;
			j++;
			next[i]=j;  //计算意义：表示后缀字符T.data[i]与前缀字符T.data[j]元素相等，则i+1如果不匹配的话就可以通过next[i+1]回溯到j+1进行比较
			            //逻辑意义：表示后缀字符T.data[i]与前缀字符T.data[j]元素相等，next[i+1]存储的就是前i的子串里面有j个字符相等，可以回溯到j+1进行比较，因为j前面都是相等的
		}
		else
			j=next[j];  //表示后缀字符T.data[i]与前缀字符T.data[j]元素不相等，则前缀字符下标j直接回溯到next[j]，回溯到1
	}
}
//返回子串T在主串S中第pos个字符之后的位置，若不存在返回值为0，时间复杂度O(n)，n是主串S的长度
int Index_KMP(STR S,STR T,int pos)
{
	int i=pos;  //i用于主串S当前位置下标值，若pos不为1，从pos位置开始匹配
	int j=1;    //j用于子串T当前位置下标值
	int next[255];    //定义next数组
	get_next(T,next);    //计算子串T的next数组
	while(i<=S.length&&j<=T.length)    //若i小于S的长度且j小于T的长度，继续匹配
	{                                  //直到j加到数值大于T的长度匹配成功，或者i加到数值大于S的长度结束匹配这种情况可能匹配不成功可能匹配成功，若成功则T是S的后缀

		if(j==0||S.data[i]==T.data[j])    //当j回溯到0时，子串重新匹配，i继续+1，i不回溯，j+1=1从头开始匹配；
		{                                 //或者当子串T与主串S匹配到了，i++和j++继续匹配
			i++;
			j++;
		}
		else
			j=next[j];    //当前位置的T元素和S元素不匹配，j回溯到前j个字符串中前缀与后缀匹配相等时前缀的后一个字符下标的位置，i不变
	}
	if(j>T.length)
		return i-T.length;    //当j加到数值大于T的长度则匹配成功，此时返回i在刚起始匹配的位置，所以i减去匹配的子串T的长度
	else
		return 0;    //匹配失败，返回0
}

int main()
{
	STR S,T;
	S.length=0;
	T.length=0;
	Insert(&S,'a');
	Insert(&S,'b');
	Insert(&S,'c');
	Insert(&S,'d');
	Insert(&T,'b');
	Insert(&T,'c');
	for(int i=1;i<=S.length;i++)
		cout<<S.data[i];
	cout<<endl;
	for(int i=1;i<=T.length;i++)
		cout<<T.data[i];
	cout<<endl;
	int pos=1;
	pos=Index_KMP(S,T,pos);
	cout<<pos<<endl;	
	return 0;
}