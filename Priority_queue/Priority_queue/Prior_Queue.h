#pragma once

#include <iostream>
#include <deque>

using namespace std;

template<class T>
class Greater
{
public:
	bool operator()(const T& x, const T& y)const
	{
		return x > y;
	}
};

template<class T>
class Less
{
public:
	bool operator()(const T& x, const T& y)const
	{
		return x < y;
	}
};

template<class T,class Container = deque<T>,class Compare = Greater<T>>
class Priority_Queue
{
private:
	void AdjustUp(size_t size)
	{
		size_t child = size;
		size_t parent = (child - 1) / 2;
		while (child > 0)
		{
			Compare com;
			if (com(_con[child], _con[parent]))
			{
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustDown(size_t size)
	{
		size_t parent = size;
		size_t child = parent * 2 + 1;
		while (child < _con.size())
		{
			Compare com;
			if (child + 1 < _con.size() && com(_con[child + 1], _con[child]))
			{
				child++;
			}
			if (com(_con[child], _con[parent]))
			{
				swap(_con[child], _con[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

public:

	void Push(const T& x)
	{
		_con.push_back(x);
		AdjustUp(_con.size() - 1);
		_size++;
	}

	void Pop()
	{
		swap(_con[0], _con[_size - 1]);
		_con.pop_back();
		AdjustDown(0);
		_size--;
	}

	size_t  Size()
	{
		return _size;
	}

	bool Empty()
	{
		return _con.empty();
	}

	T& Top()
	{
		return _con[0];
	}

private:
	Container _con;
	size_t _size = 0;
};

void TestPrior_Queue()
{
	//Priority_Queue<int>q;
	Priority_Queue<int,deque<int>,Less<int>> q;
	q.Push(13);
	q.Push(8);
	q.Push(255);
	q.Push(125);
	q.Push(3);

	cout << q.Size() << endl;
	while (!q.Empty())
	{
		cout << q.Top() << " ";
		q.Pop();
	}
	cout << endl;
}
