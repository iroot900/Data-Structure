#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
#define LINE 	cout << "------------------------------------------------------------------------------" << endl;

template <typename KEY, typename DATA>
//If KEY is an class, it need support for hash function and also "==" opeartion
//For double int string, already supported 
//Also, KEY must unique. They might have same hash code, but KEY's unique
//DATA need support for copy (constructor)
class HashNode
{
public:
	HashNode(){}
	HashNode(KEY key, DATA data) :m_key(key), m_data(data){}
	KEY m_key;
	DATA m_data;
};

template<typename KEY, typename DATA>
class HashTable
{
public:
	HashTable(int size) :m_size(0)
	{
		m_capacity = nextPrime(size);
		m_htable = new HashNode<KEY, DATA>*[m_capacity]();
		m_deleted = new HashNode<KEY, DATA>;
	}

	void insert(KEY key, DATA data)
	{
		long long hashcode = HashCode(key);
		int addr = myHash(hashcode, (int)m_capacity);
		int init = addr;

		while (1)
		{
			if (m_htable[addr] == NULL || m_htable[addr] == m_deleted)  { m_htable[addr] = new HashNode<KEY, DATA>(key, data); ++m_size; return; }
			if (m_htable[addr]->m_key == key) { m_htable[addr]->m_data = data; return; }
			if (m_htable[addr]->m_key != key)
			{
				addr = myHash(addr + 1, (int)m_capacity);  
			}
			if (init == addr) { cout << "full" << endl; return; }
		}
	}

	HashNode<KEY, DATA>* search(KEY key)
	{
		long long hashcode = HashCode(key);
		int addr = myHash(hashcode, (int)m_capacity);
		int init = addr;
		while (1)
		{
			if (m_htable[addr] == NULL) return m_htable[addr];
			if (m_htable[addr]->m_key == key) { return m_htable[addr]; }
			if (m_htable[addr]->m_key != key) addr = myHash(addr + 1, (int)m_capacity);
			else if (m_htable[addr] == m_deleted) addr = myHash(addr + 1, (int)m_capacity);
			if (init == addr) { return NULL; }
		}
	}

	void remove(KEY key)
	{
		long long hashcode = HashCode(key);
		int addr = myHash(hashcode, (int)m_capacity);
		int init = addr;
		while (1)
		{
			if (m_htable[addr] == NULL) return;
			if (m_htable[addr]->m_key == key) { delete m_htable[addr]; m_htable[addr] = m_deleted; --m_size; return; }
			if (m_htable[addr]->m_key != key) addr = myHash(addr + 1, (int)m_capacity);
			else if (m_htable[addr] == m_deleted) addr = myHash(addr + 1, (int)m_capacity);
			if (init == addr) { return; }
		}
	}

	void display()
	{
		for (int i = 0; i<m_capacity; i++)
		{
			if (m_htable[i] && m_htable[i]!=m_deleted) { cout << m_htable[i]->m_key << " : " << m_htable[i]->m_data << endl; }
		}
	}

	~HashTable()
	{
		for (int i = 0; i<m_capacity; i++) if (m_htable[i] != NULL&&m_htable[i] != m_deleted) delete m_htable[i];
		delete m_htable;
	}

	size_t size() { return m_size; }
	size_t capacity() { return m_capacity; }

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
		int result = n % M;
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
			for (int i = 0; i < n; i += (n / 12 + 1))
				result = (result << 5) - 1 + str[i];
			return result;
		}

		for (int i = 0; i < n; i++)
			result = (result << 5) - 1 + str[i];

		return result;
	}

	HashNode<KEY, DATA>** m_htable;
	HashNode<KEY, DATA>* m_deleted;
	size_t m_capacity;
	size_t m_size;
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
	cout << "read data one by one and insert data in hashTable:" << endl << endl;
	cout << "size of hashTable: " << dict.size() << endl;
	cout << "Buckets of hashTable: " << dict.capacity() << endl;
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
	LINE; LINE;
	return 0;
}
