#include<iostream>
using namespace std;
typedef int Status;
#define TRUE 1
#define FALSE 0
#define  NULLKEY -32768
#define HASHSIZE 12
typedef struct {
	int* elem;  //����Ԫ�ش洢��ַ����̬��������
	int count;  //��ǰ����Ԫ�ظ���
}HashTable;
int m = 0;  //ɢ�б����ȫ�ֱ���
//��ʼ��Hash��
Status InitHashTable(HashTable* H)
{
	int i;
	m = HASHSIZE;
	H->count = m;
	H->elem = (int*)malloc(m * sizeof(int));
	for (i = 0; i < m; i++)
		H->elem[i] = NULLKEY;
	return TRUE;
}
//��������������Hashֵ��ͨ���ؼ��ּ���洢��ַ
int Hash(int key)
{
	return key % m;
}
//��Hash�����ؼ��ֲ���
void InsertHash(HashTable* H, int key)
{
	int addr = Hash(key);
	while (H->elem[addr] != NULLKEY)
		addr = (addr + 1) % m;
	H->elem[addr] = key;
}
//��Hash���������ؼ��֣����عؼ��ִ洢��ַ
Status SearchHash(HashTable H, int key, int* addr)
{
	*addr = Hash(key);
	while (H.elem[*addr] != key)
	{
		*addr = (*addr + 1) % m;
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key))  //ѭ���ص�ԭ�㣬�ؼ��ֲ�����
			return FALSE;
	}
	return TRUE;
}
int main()
{
	HashTable H;
	InitHashTable(&H);
	int elem[HASHSIZE] = { 12,67,56,16,25,37,22,29,15,47,48,34 };
	for (int i = 0; i < HASHSIZE; i++)
		InsertHash(&H, elem[i]);
	int addr;
	int key = 67;
	if (SearchHash(H, key, &addr) == TRUE)
		cout << addr << endl;
	else
		cout << "Search Nothing." << endl;
	return 0;
}
