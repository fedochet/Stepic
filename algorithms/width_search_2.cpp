#include <iostream>
#include <vector>
#include <list>

using namespace std;
const int INF = 10000001;

struct Link{
private:
	int to_;
	int price_;
public:
	Link(int to = 0, long price = 0):to_(to),price_(price){};
	int to() const {return to_;}
	long price() const {return price_;}
	~Link(){};
};

struct tuple{
private:
	int v_; //узел графа
	int price_;
public:
	tuple(int v = 0, long price = 0):v_(v),price_(price){};
	~tuple(){};
	int v()const{return v_;}
	long price()const {return price_;}
};

void ChangePrice(list<tuple> &l, int v, int new_price);
tuple ExtractMin(list<tuple> &l);

struct Graph
{
private:
	vector< vector<Link> > gr_;
	int size_;

public:
	Graph(int size = 0):gr_(size),size_(size){}
	~Graph(){};
	int size(){return size_;};

	vector<Link> &getLinks(int place){
		return gr_[place];
	}
	void addLink(int from, int to, int price){
		getLinks(from).push_back(Link(to, price));
	}

	vector<long> dijksra(int s) 
	{
		vector<long> result(size(), INF);
		vector<int>	ancestor(size(), -1); // массив предков (их номеров)

		result[s] = 0;

		list<tuple> prior_query;//первое число - ссылка, второе - вес
		// заполнение очереди
		for(int i = 0; i < result.size(); i++)
		{
			prior_query.push_back(tuple(i, result[i]));
		}

		while (!prior_query.empty())
		{
			int curr_min = ExtractMin(prior_query).v(); // получение текущего минимума
			for(int i = 0; i<getLinks(curr_min).size(); i++)
			{
				if (result[getLinks(curr_min)[i].to()] > result[curr_min] + getLinks(curr_min)[i].price())
				{
					result[getLinks(curr_min)[i].to()] = result[curr_min] + getLinks(curr_min)[i].price();
					ancestor[getLinks(curr_min)[i].to()] = curr_min;
					ChangePrice(prior_query, getLinks(curr_min)[i].to(), result[getLinks(curr_min)[i].to()]);
				}
			}
		}

		return result;
	}
};


//процедура для извлечения минимума
//вроде корректна
tuple ExtractMin(list<tuple> &l)
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

// изменение приоритета
void ChangePrice(list<tuple> &l, int v, int new_price)
{
	list<tuple>::iterator it = l.begin();
	while(it->v()!=v)
		it++;
	*it = tuple(v, new_price);
}

int main()
{
	int n1,n2;
	cin>>n1>>n2;

	Graph g(n1);

	for (int i = 0; i<n2; i++)
	{
		int from,to,price;
		cin>>from>>to>>price;
		g.addLink(--from,--to,price);
	}

	int s, e;
	cin >> s >> e;
	int result = g.dijksra(--s)[--e];
	if (result!=INF)
		cout<<result<<endl;
	else
		cout<<-1<<endl;

	return 0;
}