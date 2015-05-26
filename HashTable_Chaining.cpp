#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#define LINE 	cout << "------------------------------------------------------------------------------" << endl;

template<typename KEY,typename DATA>
//if KEY is an class, it need support for hash function and also "==" opeartion
//For double int string, already supported 
//Also, KEY must unique. They might have same hash code, but KEY's unique
//DATA need support for copy (constructor)

class hashNode
{
public:
	hashNode(KEY key, DATA data, hashNode* next = NULL) :m_key(key), m_data(data) , m_next(next)
	{
	}
	hashNode* m_next;
	KEY m_key;
	DATA m_data;
};

template<typename KEY, typename DATA>
class HashTable
{
public:
	HashTable(int size) :m_size(0), m_bucket(0)
	{
		m_capacity = nextPrime(size);
		m_hTable = new hashNode<KEY, DATA>*[m_capacity]();
	}

	void insert(KEY key, const DATA &data)
	{
		long long hashcode = HashCode(key);
		size_t addr = myHash(hashcode, m_capacity);

		auto head = m_hTable[addr];

		if (head == NULL)
		{
			m_hTable[addr] = new hashNode<KEY, DATA>(key, data); ++m_size; ++m_bucket; return;
		}

		while (head->m_next != NULL)
		{
			if (head->m_key == key) { head->m_data = data; return; }
			head = head->m_next;
		}
		if (head->m_key == key) { head->m_data = data; return; }
		head->m_next = new hashNode<KEY, DATA>(key, data);
		++m_size;
	}

	hashNode<KEY, DATA>* search(KEY key)
	{
		long long hashcode = HashCode(key);
		size_t addr = myHash(hashcode, m_capacity);

		auto head = m_hTable[addr];

		if (head != NULL)
		{

			if (head->m_key == key) return head;
			head = head->m_next;
		}
		cout << "nul" << endl;
		return NULL;
	}

	void remove(KEY key)
	{
		long long hashcode = HashCode(key);
		size_t addr = myHash(hashcode, m_capacity);

		auto head = m_hTable[addr];
		if (!head) return;

		if (head->m_key == key) { m_hTable[addr] = head->m_next; delete head; --m_size; if (m_hTable[addr] == NULL) --m_bucket; return; }
		//
		auto prev = head;
		auto cur = head->m_next;

		while (cur != NULL)
		{
			if (cur->m_key == key) { auto temp = cur; prev->m_next = cur->m_next; delete temp; --m_size; return; }
			prev = prev->m_next;
			cur = cur->m_next;
		}
	}

	void display()
	{
		for (size_t i = 0; i < m_capacity; i++)
		{
			auto pcur = m_hTable[i];
			if (pcur != NULL) cout << endl << endl;
			while (pcur != NULL)
			{
				cout << pcur->m_key << " : " << pcur->m_data << " -> ";
				pcur = pcur->m_next;
			}
		}
	}

	~HashTable()
	{
		for (size_t i = 0; i < m_capacity; i++)
		{
			auto head=m_hTable[i];
			hashNode<KEY,DATA>* next= NULL;
			while (head != NULL)
			{
				next = head->m_next;
				delete head;
				head = next;
			}
		}
	}

	size_t size()
	{
		return m_size;
	}

	size_t capacity()
	{
		return m_capacity;
	}

	size_t bucket()
	{
		return m_bucket;
	}

private:

    bool prime(int n)
	{
		if (n < 2) return false;
		if (n < 4) return true;
		if (n % 2 == 0 || n % 3 == 0)  return false;
		int i = 5;
		for (; i*i < n; i += 6)
			if (n%i == 0 || n % (i + 2) == 0) return false;
		return true;
	}

	int nextPrime(int n)
	{
		if (n < 2) return -1;
		if (n == 2) return 2;
		if (!(n & 1)) n += 1;
		for (int i = n;; i += 2)
			if (prime(i)) return i;
	}

	int myHash(long long n, int M)
	{
		int result= (long long)(n*0.618) % M;
		return result;
	}

	long long hashCode(long long n) { return n; }

	long long HashCode(double num)
	{
		return (long long)(num*(2 << 28));
	}

	long long HashCode(const string& str)
	{
		long long result = 0;
		int n = str.size();
		if (n > 12)
		{
			for (int i = 0; i < n; i+=(n/12+1))
			result = (result << 5) - 1 + str[i];
			return result;
		}

		for (int i = 0; i < n; i++)
			result = (result << 5) - 1 + str[i];

		return result;
	}

	hashNode<KEY, DATA>** m_hTable;
	size_t m_size;
	size_t m_bucket;
	size_t m_capacity;
};
 
int main()
{
	fstream in("testing.txt");
	HashTable<string, string> dict(1000);
	string key, value; int i = 0;
	while (in)
	{
		++i;
		in >> key >> value;
		dict.insert(key, value);
	}
	dict.display();
	cout << endl;
	LINE; LINE;
	cout <<"read data one by one and insert data in hashTable:" << endl<<endl;
	cout <<"size of hashTable: " <<dict.size() << endl;
	cout <<"Buckets of hashTable: " << dict.capacity() << endl;
	cout <<"Buckets used by hashTable: " <<dict.bucket() << endl;
	in.clear();
	in.seekg(0);
	in.seekp(0);

	while (in >> key)
	{
		in >> value;
		dict.remove(key);
	}
	LINE; LINE;
	dict.display();
	cout << endl;
	cout << "read data one by one and delete data in hashTable:" << endl << endl;
	cout << "size of hashTable: " << dict.size() << endl;
	cout << "Buckets of hashTable: " << dict.capacity() << endl;
	cout << "Buckets used by hashTable: " << dict.bucket() << endl;
	LINE; LINE;
	return 0;
}