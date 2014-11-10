#include <iostream>
#include <vector>
#include <list>

using namespace std;
const int INF = 100001;

struct Graph
{
private:
	vector< vector<int> > gr_;
	int size_;

public:
	Graph(int size = 0):gr_(size),size_(size){}
	~Graph(){};
	int size(){return size_;};

	vector<int> &getLinks(int place){
		return gr_[place];
	}
	void addLink(int from, int to){
		getLinks(from).push_back(to);
	}
	vector<int> BFS(int s){
		vector<int> result(size(), INF);
		list<int>	query;

		result[s] = 0;
		query.push_back(s);

		while (!query.empty())
		{
			int curr = query.front();
			query.pop_front();

			for (int i = 0; i < getLinks(curr).size(); i++)
			{
				if (result[ getLinks(curr)[i] ]==INF)
				{
					query.push_back(getLinks(curr)[i]);
					result[ getLinks(curr)[i] ] = result[curr]+1;
				}
			}
		}

		return result;
	}
};

int main()
{
	int n1,n2;
	cin>>n1>>n2;

	Graph g(n1);

	for (int i = 0; i<n2; i++)
	{
		int from,to;
		cin>>from>>to;
		g.addLink(--from,--to);
		g.addLink(to,from);
	}

	int s,e;
	cin>>s>>e;

	int result = g.BFS(--s)[--e];
	if (INF != result)
		cout<<result<<endl;
	else
		cout<<-1<<endl;

	return 0;
}