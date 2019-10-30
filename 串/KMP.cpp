#include<iostream>
using namespace std;
#define MaxSize 100
typedef struct STR
{
	char data[MaxSize];    //����洢�����±�1��ʼ���±�0Ϊ��
	int length;
}STR;
//��T����Ԫ��e
void Insert(STR *T,char e)
{
    T->data[T->length+1]=e;
	T->length++;
}
//ͨ�����㷵���Ӵ�T��next���飬ʱ�临�Ӷ�O(m)��m���Ӵ�T�ĳ���
void get_next(STR T,int *next)
{
	int i,j;
	i=1;  //i�Ǻ�׺�ַ����±꣬��1��length
	j=0;  //j��ǰ׺�ַ����±꣬��ʼ��0����Ϊi��j��ƥ�����j+1���бȽϣ�j+1��Сֵ��1
	next[1]=0;
	while(i<T.length)
	{
		if(j==0||T.data[i]==T.data[j])//ǰ׺�ַ��±�jһֱ���ݵ�0�����¿�ʼƥ��
		{
			i++;
			j++;
			next[i]=j;  //�������壺��ʾ��׺�ַ�T.data[i]��ǰ׺�ַ�T.data[j]Ԫ����ȣ���i+1�����ƥ��Ļ��Ϳ���ͨ��next[i+1]���ݵ�j+1���бȽ�
			            //�߼����壺��ʾ��׺�ַ�T.data[i]��ǰ׺�ַ�T.data[j]Ԫ����ȣ�next[i+1]�洢�ľ���ǰi���Ӵ�������j���ַ���ȣ����Ի��ݵ�j+1���бȽϣ���Ϊjǰ�涼����ȵ�
		}
		else
			j=next[j];  //��ʾ��׺�ַ�T.data[i]��ǰ׺�ַ�T.data[j]Ԫ�ز���ȣ���ǰ׺�ַ��±�jֱ�ӻ��ݵ�next[j]�����ݵ�1
	}
}
//�����Ӵ�T������S�е�pos���ַ�֮���λ�ã��������ڷ���ֵΪ0��ʱ�临�Ӷ�O(n)��n������S�ĳ���
int Index_KMP(STR S,STR T,int pos)
{
	int i=pos;  //i��������S��ǰλ���±�ֵ����pos��Ϊ1����posλ�ÿ�ʼƥ��
	int j=1;    //j�����Ӵ�T��ǰλ���±�ֵ
	int next[255];    //����next����
	get_next(T,next);    //�����Ӵ�T��next����
	while(i<=S.length&&j<=T.length)    //��iС��S�ĳ�����jС��T�ĳ��ȣ�����ƥ��
	{                                  //ֱ��j�ӵ���ֵ����T�ĳ���ƥ��ɹ�������i�ӵ���ֵ����S�ĳ��Ƚ���ƥ�������������ƥ�䲻�ɹ�����ƥ��ɹ������ɹ���T��S�ĺ�׺

		if(j==0||S.data[i]==T.data[j])    //��j���ݵ�0ʱ���Ӵ�����ƥ�䣬i����+1��i�����ݣ�j+1=1��ͷ��ʼƥ�䣻
		{                                 //���ߵ��Ӵ�T������Sƥ�䵽�ˣ�i++��j++����ƥ��
			i++;
			j++;
		}
		else
			j=next[j];    //��ǰλ�õ�TԪ�غ�SԪ�ز�ƥ�䣬j���ݵ�ǰj���ַ�����ǰ׺���׺ƥ�����ʱǰ׺�ĺ�һ���ַ��±��λ�ã�i����
	}
	if(j>T.length)
		return i-T.length;    //��j�ӵ���ֵ����T�ĳ�����ƥ��ɹ�����ʱ����i�ڸ���ʼƥ���λ�ã�����i��ȥƥ����Ӵ�T�ĳ���
	else
		return 0;    //ƥ��ʧ�ܣ�����0
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