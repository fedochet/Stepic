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

	struct Graph
	{
	private:
		vector< vector<Link> > gr_;
		int size_;

	public:
		Graph(int size = 0):gr_(size),size_(size){}
		~Graph(){};
		int size() const {return size_;};

		vector<Link> &getLinks(int place){
			return gr_[place];
		}
		void addLink(int from, int to, int price){
			getLinks(from).push_back(Link(to, price));
		}

		vector<long> BellmanFord(int s, vector <bool> &check) 
		{
			vector<long> result(size(), INF);
			vector<int>	ancestor(size(), -1); // массив предков (их номеров)

			result[s] = 0;

			for (int j = 0; j<=size(); j++)
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
					check = vector<bool> (result.size(), false);
					return result;
				}
			}

			//true - там, где "-"
			vector<bool> control(size(), false);

			//делаем первый прогон, при этом изменятся только "входы" циклов
			for(int k = 0; k<size(); k++)
			{
				for(int i = 0; i<getLinks(k).size(); i++)
				{
					if (result[k]!=INF && result[getLinks(k)[i].to()] > result[k] + getLinks(k)[i].price())
					{
						control[getLinks(k)[i].to()] = true;
					}
				}
			}

			for (int i = 0; i<size(); i++)
			{
				
				int k = ancestor[i];
				while(k!=-1 && ancestor[k]!=-1)
				{
					if(control[ancestor[k]]!=true)
						k = ancestor[k];
					else 
					{
						control[k] = true;
						break;
					}
				}	
				
			}

			check = control;

			return result;
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

		vector<bool> check(g.size());
		vector<long> v = g.BellmanFord(--s,check);
		for (int i = 0; i<v.size(); i++)
		{
			if (v[i]!=INF)
			{
				if (!check[i])
					cout<<v[i]<<endl;
				else
					cout<<"-"<<endl;
			}
			else
				cout<<"*"<<endl;
		}

		return 0;
	}