#define _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
using namespace std;


/// <summary>
//���ʶ���ϣ���е�һ��λ���ǿջ�����
/// </summary>
namespace sjp
{
	enum State//״̬
	{
		EMPTY,//��
		EXITS,//����
		DLETE//ɾ��
	};

	template<class T>
	struct HashFunc
	{
		size_t operator()(const T& k)
		{
			return k;
		}
	};

	

	template<>//ģ���ػ�
	struct HashFunc<string>
	{
		//���ַ���ɶ�Ӧ������ֵ
		//BKDRHAXI ÿ�μ���һ�������ڳ���131
		//����Ψһ
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
	//		//�����õ�ַ����ַ�ǻ���
	//		for (auto ch : s)
	//		{

	//		}
	//		reutrn 0;
	//	}
	//};



	template<class K,class V>
	class HashData//��ϣ�������
	{
	public:
		pair<K, V> _kv;
		State _state = EMPTY;
	};

	template<class K, class V, class HashFunc= HashFunc<K>>//�º���
	class HashTable
	{
	public:
		bool Insert(const pair<K, V>& kv)
		{
			if (find(kv.first) != NULL)//���kvֵ��_table,�����ʧ��
				return false;
			if (_table.capacity() == 0)
			{
				_table.resize(10);
			}

			else if ((double)_n /(double) _table.size()>=0.7)//���㸺������
			{
				//���ڸ������ӣ���ϣ���������
				HashTable<K, V, HashFunc> newHT;
				newHT._table.resize(_table.size() * 2);
				for (auto& e : _table)
				{
					if (e._state == EXITS)
					{
						newHT.Insert(e._kv);//������insert���൱�ڸ�����insert
					}
				}
				_table.swap(newHT._table);//���newHT.table�ͱ����table��������
			}
			//λ�õ�ģ��size()
			HashFunc hf;
			size_t index = hf(kv.first)%_table.size();
			size_t i = 1;
			int start = index;
			//̽������λ�� ���� ����̽�� or ����̽��
			while (_table[index]._state == EXITS)
			{
				i += 1;
				index =start+i;//����̽��
				index %= _table.size();
			}
			_table[index]._kv = kv;
			_table[index]._state = EXITS;
			++_n;
			return true;
		}

		HashData<K, V>* find(const K& k)
		{
			HashFunc fc;//�º���
			if (_table.size()== 0)//��ֹ��0
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
		size_t _n=0;//�洢��Ч���ݵĸ���
	};

}

//ֻ�����β��ܽ���%
//һ������ȥ��map/set��Key��ʲôҪ��  --��֧�ֱȽϴ�С
//һ������ȥ��undered_map/unorder
