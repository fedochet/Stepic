#include <iostream>
#include <vector>
#include <string>

using namespace std;

class uncrossed_groups{

public:
	vector<int> base,ranks;

	uncrossed_groups(){};

	// заполняет вектор номерами ячеек, т.е. ссылками на самих себя
	uncrossed_groups(int const &a){
		base.resize(0);
		for (int i = 0; i<a; i++)
		{
			base.push_back(i);
			ranks.push_back(0);
		}
	}

	~uncrossed_groups(){};

	// операция поиска (уже норм)
	int find(int const &k){
		int curr = k;


		if (base[curr]!=curr) 	// пока элемент не указывает сам на себя
			base[curr] = find(base[curr]);

		return base[curr];
	}

	// операция слияния двух групп
	void unite(int const &l, int const &r){
		int lr = find(l);
		int rr = find(r);

		if (lr == rr)
			return;

		if (ranks[lr]>ranks[rr])
			base[rr] = lr;
		else
			base[lr] = rr;

		if (ranks[lr]==ranks[rr])
			ranks[lr]++;

	}

};

int main()
{
	int n1,n2;
	cin>>n1;
	cin>>n2;

	uncrossed_groups g(n1);

	for (int i = 0; i<n2; i++)
	{
		string s;
		cin>>s;
		if (s == "Check")
		{
			int temp1, temp2;
			cin>>temp1>>temp2;
			if (temp1==temp2)
				cout<<1<<endl;
			else
			{	
				if (g.find(--temp1) == g.find(--temp2))
					cout<<1<<endl;
				else
					cout<<0<<endl;
			}
		}

		else
		{
			int temp1, temp2;
			cin>>temp1>>temp2;

			g.unite(--temp1,--temp2);

		}
	}

	return 0;
}