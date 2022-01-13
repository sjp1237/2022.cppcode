#define _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
using namespace std;


/// <summary>
//如何识别哈希表中的一个位置是空还是满
/// </summary>
namespace sjp
{
	enum State//状态
	{
		EMPTY,//空
		EXITS,//存在
		DLETE//删除
	};

	template<class T>
	struct HashFunc
	{
		size_t operator()(const T& k)
		{
			return k;
		}
	};

	

	template<>//模板特化
	struct HashFunc<string>
	{
		//将字符变成对应的整形值
		//BKDRHAXI 每次加上一个数，在乘上131
		//近似唯一
		size_t  operator()(const string& st)
		{
			size_t ret = 0;
			for (auto e : st)
			{
				ret += e;
				ret *= 131;
			}
			return ret;
		}
	};

	//void test3()
	//{
	//	stringHashFunc sH;
	//	cout << sH("abcd") << endl;
	//	cout << sH("acbd") << endl;
	//	cout << sH("abbe") << endl;
	//}

	//struct StudentHashFunc
	//{
	//	size_t operator()()
	//	{
	//		size_t value = 0;
	//		//不能用地址，地址是会变的
	//		for (auto ch : s)
	//		{

	//		}
	//		reutrn 0;
	//	}
	//};



	template<class K,class V>
	class HashData//哈希点的数据
	{
	public:
		pair<K, V> _kv;
		State _state = EMPTY;
	};

	template<class K, class V, class HashFunc= HashFunc<K>>//仿函数
	class HashTable
	{
	public:
		bool Insert(const pair<K, V>& kv)
		{
			if (find(kv.first) != NULL)//如果kv值在_table,则插入失败
				return false;
			if (_table.capacity() == 0)
			{
				_table.resize(10);
			}

			else if ((double)_n /(double) _table.size()>=0.7)//计算负载因子
			{
				//大于负载因子，哈希表进行增容
				HashTable<K, V, HashFunc> newHT;
				newHT._table.resize(_table.size() * 2);
				for (auto& e : _table)
				{
					if (e._state == EXITS)
					{
						newHT.Insert(e._kv);//在运行insert，相当于复用了insert
					}
				}
				_table.swap(newHT._table);//最后将newHT.table和本身的table交换即可
			}
			//位置得模上size()
			HashFunc hf;
			size_t index = hf(kv.first)%_table.size();
			size_t i = 1;
			int start = index;
			//探测后面的位置 —— 线性探测 or 二次探测
			while (_table[index]._state == EXITS)
			{
				i += 1;
				index =start+i;//二次探测
				index %= _table.size();
			}
			_table[index]._kv = kv;
			_table[index]._state = EXITS;
			++_n;
			return true;
		}

		HashData<K, V>* find(const K& k)
		{
			HashFunc fc;//仿函数
			if (_table.size()== 0)//防止除0
				return nullptr;
			int index = fc(k) % _table.size();
			int i = 1;
			while (_table[index]._state !=EMPTY )
			{
				if (_table[index]._state == EXITS&&_table[index]._kv.first == k)
				{
					return &_table[index];

				}
				else 
				{
					index += i;
					index %= _table.size();
				}
			}
			return NULL;
		}

		bool erase(const K& k)
		{
			HashData<K, V>* kv = find(k);
			if (kv == NULL)
			{
				return false;
			}
			else if (kv != NULL)
			{
				kv->_state = DLETE;
				return true;
			}
		}
	private:
		vector<HashData<K,V>> _table;
		size_t _n=0;//存储有效数据的个数
	};

}

//只有整形才能进行%
//一个类型去做map/set的Key有什么要求  --能支持比较大小
//一个类型去做undered_map/unorder
