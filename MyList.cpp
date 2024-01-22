#include <iostream>
#include <memory>

template <typename... T>
void print(const T& ...args)
{
	((std::cout << args << ' '), ...) << std::endl;
}

template <typename _ValueType>
class MyList
{
public:
	using ValueType = _ValueType;
private:
	struct _Node
	{
		ValueType value {};
		std::shared_ptr<_Node> next;
		std::shared_ptr<_Node> prev;
		_Node()
		{
//			print(nowInfo);
			next = nullptr;
			prev = nullptr;
		}
		~_Node()
		{
//			print(nowInfo);
		}
	};
	std::shared_ptr<_Node> _head = std::make_shared<_Node>();
	std::size_t _size = 0;	
public:
	class Iterator : public std::iterator<std::bidirectional_iterator_tag,ValueType>
	{
	private:
		_Node* data; 
		friend class MyList;
	public:
		Iterator& operator ++()
		{
			data = data->next.get();
			return *this;
		}
		Iterator& operator --()
		{
			data = data->prev.get();
			return *this;
		}
		ValueType* operator ->()
		{
			return &(data->value);
		}
		ValueType& operator *()
		{
			return data->value;
		}
		bool operator !=(const Iterator& iter) const
		{
			return data != iter.data;
		}
	};
	
	MyList()
	{
//		print(nowInfo);
		_head->next = _head;
		_head->prev = _head;
	}
	
	template<typename U>
	MyList(const MyList<U>& ml)
	{
		for(auto e : ml)
		{
			push_back(e);
		}
	}
	
	MyList(MyList&& ml)
	{
		_head = ml._head;
		_size = ml._size;
		
		ml._head = nullptr;
	}
	
	void swap(MyList& ml)
	{
		std::swap(_head,ml._head);
		std::swap(_size,ml._size);
	}
	
	MyList& operator =(const MyList& ml)
	{
		MyList temp(ml);
		this->swap(temp);
	}
	
	MyList& operator =(MyList&& ml)
	{
		this->swap(ml);
	}
	
	~MyList()
	{
		while(_size > 0)
		{
			pop_front();
		}
	}
	
	Iterator insert(const Iterator& pos,ValueType v)
	{
//		print(nowInfo);
		std::shared_ptr<_Node> prevNode = pos.data->prev;
		
//		print(nowInfo);
		std::shared_ptr<_Node> nextNode = prevNode->next;
		std::shared_ptr<_Node> nodePtr = std::make_shared<_Node>();
		
		nodePtr->value = v;
		nodePtr->next = nextNode;
		nodePtr->prev = prevNode;
		
		prevNode->next = nodePtr;
		nextNode->prev = nodePtr;
		
		_size ++;
		
		Iterator iter;
		iter.data = nodePtr.get();
		return iter;
	}
	
	Iterator erase(const Iterator& pos)
	{
		Iterator ret;
		ret.data = pos.data->prev.get();
		
		std::shared_ptr<_Node> prevPtr = pos.data->prev;
		std::shared_ptr<_Node> nextPtr = pos.data->next;
		
		prevPtr->next = nextPtr;
		nextPtr->prev = prevPtr;
		
		_size --;
		
		return ret;
	}
	
	Iterator begin()
	{
//		print(nowInfo);
		Iterator _begin;
		_begin.data = _head->next.get();
		return _begin;
	}
	
	Iterator end()
	{
//		print(nowInfo);
		Iterator _end;
		_end.data = _head.get();
		return _end;
	}
	
	void push_front(ValueType v)
	{
		insert(begin(),std::move(v));
	}
	
	void push_back(ValueType v)
	{
//		print(nowInfo);
		insert(end(),std::move(v));
	}
	
	void pop_front()
	{
		erase(begin());
	}
};

//int main()
//{
//	MyList<int> ml {};
//	ml.push_front(1);
//	ml.push_front(2);
//	ml.push_front(3);
//	ml.push_front(4);
//	for(auto e : ml)
//	{
//		std::cout << e << ' ';
//	}
//	return 0;
//}
