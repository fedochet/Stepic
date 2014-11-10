#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

long period_length(long n, vector<long> &v)
{
	long curr, prev;
	v[0] = 0;
	curr = 1;
	v[1] = 1;
	v[2] = 1;
	prev = 1;
	long i;
	for (i=3; (i<=6*n+1)&&((curr!=1)||(prev!=0)); i++)
	{
		long temp = curr;
		curr = (curr + prev) %n;
		v[i] = curr;
		//cout<<curr<<endl;
		prev = temp;
	}
	return i-2;
}

int main()
{
	long n;
	long long k;
	cin>>k;
	cin>>n;
	vector<long> v(n*6);
	long p = period_length(n,v);
	cout<<v[k%p];
	return 0;
}