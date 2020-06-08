#include<iostream>
using namespace std;
enum PointTag{child,thread};  //link=0��ʾָ��ָ�����Һ��ӣ�thread=1��ʾָ��ָ��ǰ�����̵�����
typedef char Elemtype;
//������������洢�ṹ����
typedef struct Node
{
	Elemtype data;  //�������
	struct Node *L;  //���Һ���ָ��
	struct Node *R;
	PointTag Ltag;  //���ұ�ǣ�0��ʾָ��ָ�����Һ��ӣ�1��ʾָ��ָ��ǰ�����̵�����
	PointTag Rtag;
}Node,*BThrTree;
BThrTree pre=NULL;//ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ�㣬�ݹ��ʱ�򾭳��õ�ȫ�ֱ���
//��������������ǰ������������н���ֵ��#��ʾ������������������ʾ������T
void CreateBThrTree(BThrTree *T)
{
	Elemtype e;
	cin>>e;
	if(e=='#')
		*T=NULL;
	else
	{
		(*T)=(Node*)malloc(sizeof(Node));
		(*T)->data=e;
		(*T)->Ltag=child;
		(*T)->Rtag=child;
		CreateBThrTree(&(*T)->L);
		CreateBThrTree(&(*T)->R);
	}
}
//����������ж�����������������ʹ��������ɶ���������������˳����������
/*
��ǰ���p��ǰ�������pre�����Ե�ǰ���p������ָ��ǰ�����pre��p->L=pre
ͬʱ��ǰ���pҲ��ǰ�����pre�ĺ�̣�����ǰ�����pre���Һ���ָ��ǰ���p��pre->R=p
*/
void MiddleThreading(BThrTree p)
{
	
	if(p!=NULL)
	{
		MiddleThreading(p->L);
		//��Ϊ��ǰ���p��ǰ���Ѿ����ʵ�����pre
		if(p->L==NULL)  //�����ǰ���û�����ӣ�p->L������ָ��ǰ�����pre
		{
			p->Ltag=thread;
			p->L=pre;
		}
		//��Ϊ��ǰ���p�ĺ�̻�û�з��ʵ�������ֻ�ܶ�����ǰ�����pre���ж�
		if(pre!=NULL && pre->R==NULL)  //pre��ʼ��NULL�����ҵ���һ�����ʱ��pre��û�и�ֵ����NULL�����Ա�����pre->R==NULL֮ǰ���ж�һ�£����ǰ�����û���Һ��ӣ���pre->R������ָ��pre�ĺ�̽��Ҳ���ǵ�ǰ���p
		{
			pre->Rtag=thread;
			pre->R=p;
		}
		pre=p;  //�����굱ǰ���p֮������һ����㣬���Ե�ǰ�����pre���
		MiddleThreading(p->R);
	}
}
//�����������������
void MiddleOrderTraverse(BThrTree T)
{
	BThrTree p;
	p=T;  //pָ����ڵ�
	while(p!=NULL)  //�������߱�������p�ص�T��������Ϊ���������н�㣬������������һ�����ָ��ͷ���
	{
		while(p->Ltag==child)  //ѭ���ҵ���pΪ���ڵ���������ĵ�һ����㣬Ҳ����������Ǹ����
			p=p->L;
		cout<<p->data;
		while(p->Rtag==thread && p->R!=NULL)  //��ӡ�����ӣ���ӡ�м��㣬���û���Һ���һֱ��ӡ�м��㣬���Ҳ���ָ��ͷ��㣬�����ӡ������Ϊͷ���û��������
		{
			p=p->R;
			cout<<p->data;
		}
		p=p->R;  //��ӡ���󺢺��м��㣬p����������������������Ĳ�������Ϊ���������һֱ�����ұ�����˳��
	}
	return;
}
int main()
{
	BThrTree T;
	//����ab#d##c##
	CreateBThrTree(&T);
	MiddleThreading(T);
	MiddleOrderTraverse(T);
	return 0;
}

