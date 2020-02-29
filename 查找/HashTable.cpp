#include<iostream>
using namespace std;
typedef int Status;
#define TRUE 1
#define FALSE 0
#define  NULLKEY -32768
#define HASHSIZE 12
typedef struct {
	int* elem;  //数据元素存储基址，动态分配数组
	int count;  //当前数据元素个数
}HashTable;
int m = 0;  //散列表表长，全局变量
//初始化Hash表
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
//除留余数法计算Hash值，通过关键字计算存储地址
int Hash(int key)
{
	return key % m;
}
//向Hash表插入关键字操作
void InsertHash(HashTable* H, int key)
{
	int addr = Hash(key);
	while (H->elem[addr] != NULLKEY)
		addr = (addr + 1) % m;
	H->elem[addr] = key;
}
//在Hash表中搜索关键字，返回关键字存储地址
Status SearchHash(HashTable H, int key, int* addr)
{
	*addr = Hash(key);
	while (H.elem[*addr] != key)
	{
		*addr = (*addr + 1) % m;
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key))  //循环回到原点，关键字不存在
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
