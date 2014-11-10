#include <iostream>

using namespace std;

int main()
{
	int n;
	cin>>n;

	long inv = 0;

	long m[n];

	for (int i = 0; i<n; i++)
		cin>>m[i];

	for (int i = 0; i<n-1; i++)
	{
		for (int j = i+1; j<n;j++)
		{
			if (m[i]>m[j])
			{
				inv++;
			}
		}
	}

	cout<<inv;

	return 0;
}