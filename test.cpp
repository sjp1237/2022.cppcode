#define _CRT_SECURE_NO_WARNINGS 1
#include"Hash.h"



void test()
{
	sjp::HashTable<int, int> ht;
	ht.Insert(make_pair(4, 4));
	ht.Insert(make_pair(4, 4));
	ht.Insert(make_pair(10, 10));
	ht.Insert(make_pair(1000, 1000));
	ht.Insert(make_pair(20, 20));
	ht.Insert(make_pair(9, 9));
	ht.Insert(make_pair(7, 7));
	ht.Insert(make_pair(6, 6));
	ht.Insert(make_pair(8, 8));
	ht.Insert(make_pair(3, 3));

	ht.erase(7);
	sjp::HashData<int, int>* it1 = ht.find(7);
	if (it1 != NULL)
		cout << "找到了" << endl;
	else
		cout << "找不到" << endl;

	sjp::HashData<int, int>* it = ht.find(8);
	
	if (it != NULL)
		cout << "找到了" << endl;
	else
		cout << "找不到" << endl;
}

void test1()
{
	sjp::HashTable<string, int> ht;
	string arr[] = { "苹果","香蕉","香蕉" ,"苹果" ,"香蕉" };
	for (auto e : arr)
	{
		sjp::HashData<string, int>* it = ht.find(e);
		if (it == NULL)
		{
			ht.Insert(make_pair(e,1));
		}
		else
		{
			(*it)._kv.second++;
		}
	}
}
int main()
{
	test();
	test1();
	//sjp::test3();
	return 0;
}