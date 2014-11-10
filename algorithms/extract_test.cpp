#include <list>
#include <iostream>

using namespace std;

struct tuple{
private:
	int v_; //узел графа
	int price_;
public:
	tuple(int v = 0, int price = 0):v_(v),price_(price){};
	~tuple(){};
	int v()const{return v_;}
	int price()const {return price_;}
};

tuple extractMin(list<tuple> &l)
{
	list<tuple>::iterator min = l.begin();
	for (list<tuple>::iterator it = l.begin(); it!=l.end(); it++)
	{
		if (it->price() < min->price())
			min = it;
	}

	tuple result = *min;
	l.erase(min);

	return result;
}

int main()
{
	list<tuple> l;
	l.push_back(tuple(1,15));
	l.push_back(tuple(2,10));
	l.push_back(tuple(3,13));

	cout<<extractMin(l).v()<<endl;
	cout<<extractMin(l).v()<<endl;
	cout<<extractMin(l).v()<<endl;
	return 0;
}