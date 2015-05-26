#include <iostream>
#include  <string>
#include <unordered_map>
using namespace std;

template <class T>
//int is the key, and T is the data;
class heap
{
public:
	void insert(pair<int, T> num);
	void pop();
	bool inHeap(T first)
	{
		return  position.find(first) != position.end();
	}
	void decrease(pair<int, T> num, int val);
	pair<int, T> top();
	bool empty() { return data.empty(); }
	int size(){ return data.size(); }
private:
	vector<pair<int, T> > data;
	unordered_map<T, int>  position;
};

template <class T>
void heap<T>::insert(pair<int, T> num)
{
	data.push_back(num);
	int i = data.size() - 1;// cur
	position[num.second] = i;
	int parent = 0;
	while (i - 1 >= 0)
	{
		parent = (i - 1) / 2;
		if (data[parent].first>data[i].first)
		{
			swap(data[parent], data[i]);
			position[data[parent].second] = parent;
			position[data[i].second] = i;
			i = parent;
		}
		else break;
	}
}

template<class T>
pair<int, T> heap<T>::top()
{
	if (!empty())
		return data[0];
	else throw - 1;
}

template<class T>
void heap<T>::pop()
{
	if (!empty())
	{
		swap(data[0], data.back());
		position.erase(data.back().second);
		data.pop_back();
		if (empty()) return;

		position[data[0].second] = 0;

		int n = data.size();
		int i = 0;
		while (i * 2 + 1<n)
		{
			if (i * 2 + 2<n)
			{
				if (data[i * 2 + 2].first<data[i].first&&data[i * 2 + 1].first<data[i].first)
				{
					int inc = 0;
					if (data[i * 2 + 1].first<data[i * 2 + 2].first)   inc = 1;
					else inc = 2;

					swap(data[i * 2 + inc], data[i]);
					position[data[i * 2 + inc].second] = i * 2 + inc;
					position[data[i].second] = i;
					i = i * 2 + inc;
					continue;

				}

				else if (data[i * 2 + 2].first<data[i].first)
				{
					swap(data[i * 2 + 2], data[i]);
					position[data[i * 2 + 2].second] = i * 2 + 2;
					position[data[i].second] = i;
					i = i * 2 + 2;
					continue;
				}

				else if (data[i * 2 + 1].first<data[i].first)
				{
					swap(data[i * 2 + 1], data[i]);
					position[data[i * 2 + 1].second] = i * 2 + 1;
					position[data[i].second] = i;
					i = i * 2 + 1;
					continue;
				}


			}
			else
			{
				if (data[i * 2 + 1].first<data[i].first)
				{
					swap(data[i * 2 + 1], data[i]);
					position[data[i * 2 + 1].second] = i * 2 + 1;
					position[data[i].second] = i;
					i = i * 2 + 1;
					continue;
				}
			}
			break;
		}
	}
}

template<class T>
void heap<T>::decrease(pair<int, T> num, int val)
{
	auto it = position.find(num.second);
	if (it != position.end())
	{
		data[position[num.second]].first = val;

		int parent = 0, i = position[num.second];
		while (i - 1 >= 0)
		{
			parent = (i - 1) / 2;
			if (data[parent].first>data[i].first)
			{
				swap(data[parent], data[i]);
				position[data[parent].second] = parent;
				position[data[i].second] = i;
				i = parent;
			}
			else break;
		}
	}
}

int main()
{
	heap <string> cities;
	cities.insert(make_pair(70, "Chicago"));  
	cities.insert(make_pair(55, "New York"));
	cities.insert(make_pair(80 , "San Fran"));
	cities.insert(make_pair(90, "Ann Arbor"));
	cities.insert(make_pair(90, "San Jose"));
	cities.insert(make_pair(80, "LA"));
	cities.insert(make_pair(70, "Boston"));
	cities.decrease(make_pair(70, "Boston"), 50);

	while (!cities.empty())
	{
		auto it = cities.top();
		cout << it.first << " " << it.second << endl; 
		cities.pop();
	}
}