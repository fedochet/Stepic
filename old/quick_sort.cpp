#include <iostream>
#include <vector>

using namespace std;

struct line{

private:
	int x_b, x_e;
	
public:
	line (int b = 0, int e = 0):x_b(b),x_e(e){}
	~line(){}

	void print(){
		cout<<"x_b == "<<x_b<<"; x_e == "<<x_e<<endl;
	}

	bool includes(int x)
	{
		return ((x>=x_b) && (x<=x_e));
	}
};

int main()
{
	vector<line> v(0);

	int n1,n2;
	cin>>n1;
	cin>>n2;

	for(int i = 0; i<n1; i++)
	{
		int b,e;
		cin>>b>>e;
		v.push_back(line(b,e));
	}

	for(int i = 0; i<n2; i++)
	{
		int point;
		cin>>point;

		int inceptions(0);

		for (int j = 0; j<n1; j++)
		{
			if (v[j].includes(point))
			{
				inceptions++;
			}
		}

		cout<<inceptions<<" ";
	}

	return 0;
}