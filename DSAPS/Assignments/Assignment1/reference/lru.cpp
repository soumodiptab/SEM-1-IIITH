/*
Statement:​ Design and implement a data structure for LRU (Least
Recently Used) cache. It should support the following operations:
○ get(key) - Get the value (will always be positive) of the key if the key
exists in the cache, otherwise return -1.
○ set(key, value) - Set or insert the value if the key is not already
present. When the cache reaches its capacity, it should invalidate the
least recently used item before inserting the new item.The LRU Cache will be initialized with an integer corresponding to its
capacity in the constructor. Capacity indicates the maximum number
of unique keys it can hold at a time.
Definition of “least recently used”: An access to an item is defined as a
get or a set operation of the item. “Least recently used” item is the one
with the oldest access time. You are free to use any data structure for
the problem.
*/


#include<bits/stdc++.h>
using namespace std;

template <typename T,typename T2>
class lru	{
	private:
	int capacity;
	int size;
	deque<T> dq;
	unordered_map<T,T2> mp;
	public:
	lru(int c);
	void set(T key,T2 value);
	T2 get(T key);
	void display();
};

template <typename T,typename T2>
lru<T,T2>::lru(int c)	{
	capacity=c;
	size=0;
}

template <typename T,typename T2>
void lru<T,T2>::set(T key,T2 value)	{

	T val;
	if(mp.find(key) == mp.end())	{

		if(dq.size()>=capacity)	{
			val=dq.back();
			dq.pop_back();
			mp.erase(val);
		}

		dq.push_front(key);
		mp[key]=value;
		size++;
		if(size>capacity)
			size=capacity;
		
	}
	else 	{
		auto it=dq.begin();
		for(int i=1;i<=size;i++)	{
			if(*it == key)	{
				dq.erase(it);
				break;
			}
			it++;
		}
		dq.push_front(key);
		mp[key]=value;
	}

}	


template <typename T,typename T2>
T2 lru<T,T2>::get(T key)	{
	
	if(mp.find(key)==mp.end())
		return -1;
	else	{
		auto it=dq.begin();
		for(int i=1;i<=size;i++)	{
			if(*it == key)	{
				dq.erase(it);
				break;
			}
			it++;
		}
		dq.push_front(key);
		return abs(mp[key]);
	}
	
}	

template <typename T,typename T2>
void lru<T,T2>::display()	{
	for(auto it=dq.begin();it!=dq.end();it++)	{
		cout<<*it<<":"<<mp[*it]<<"  ";
	}
	cout<<"\n";
}

int main()	{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n,q,key;
	int value,x;
	char ch;
	cin>>n;
	cin>>q;
	lru<int,int> obj(n);
	while(q--)	{
		cin>>ch;
		if(ch=='G')	{
			cin>>key;
			x=obj.get(key);
			//obj.display();
			cout<<x<<"\n";
		}
		else if(ch=='S')	{
			cin>>key;
			cin>>value;
			obj.set(key,value);
			//obj.display();
		}
		//obj.display();
	}
	return 0;
}
