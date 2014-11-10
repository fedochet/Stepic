#include <iostream>
#include <vector>

using namespace std;
const long INF = 1000000001;

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

	vector<long> BellmanFord(int s, vector<bool> &check) 
	{
		vector<long> result(size(), INF);
		vector<int>	ancestor(size(), -1); // массив предков (их номеров)

		result[s] = 0;

		for (int j = 0; j<size(); j++)
		{
			bool flag = true;
			for(int k = 0; k<size(); k++)
			{
				for(int i = 0; i<getLinks(k).size(); i++)
				{
					if (result[k]!=INF && result[getLinks(k)[i].to()] > result[k] + getLinks(k)[i].price())
					{
						flag = false;
						result[getLinks(k)[i].to()] = result[k] + getLinks(k)[i].price();
						ancestor[getLinks(k)[i].to()] = k;
					}
				}
			}
			if (flag)
			{
				check = vector<bool>(size(), false);
				return result;
			}
		}

		check = vector<bool> (size(), false);
		for(int k = 0; k<size(); k++)
		{
			for(int i = 0; i<getLinks(k).size(); i++)
			{
				if (result[k]!=INF && result[getLinks(k)[i].to()] > result[k] + getLinks(k)[i].price())
				{
					check[k] = true;
				}
			}
		}

		for (int i = 0; i<check.size(); i++)
		{
			if (check[i])
			{
				for (int k = 0; k<getLinks(i).size(); k++)
					GDF(getLinks(i)[k].to(),check);
			}
		}

		//check = vector<bool>(size(),false);
		return result;
	}

	void GDF(int s, vector<bool> &checked)
	{
		if (checked[s])
			return;
		else
		{
			checked[s] = true;
			for (int i = 0; i<getLinks(s).size(); i++)
			{
				GDF(getLinks(s)[i].to(), checked);
			}
		return;
		}

		return;
	}
};



int main()
{
	int n1,n2,s;
	cin>>n1>>n2>>s;

	Graph g(n1);

	for (int i = 0; i<n2; i++)
	{
		int from,to,price;
		cin>>from>>to>>price;
		g.addLink(--from,--to,price);
	}

	vector<bool> check;
	vector <long> result = g.BellmanFord(--s,check);

	for (int i = 0; i<result.size(); i++)
	{
		if (result[i] == INF)
			cout<<"*"<<endl;
		else
		{
			if (check[i])
				cout<<"-"<<endl;
			else
				cout<<result[i]<<endl;
		}
	}

	return 0;
}