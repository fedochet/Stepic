#include <iostream>

using namespace std;

//void sorting()

int main(void)
{
	int n;
	cin>>n;

	long int arr[n];

	for (int i = 0; i<n; i++)
	{
		cin>>arr[i];
	}

	for (int i=0; i<n-1; i++)
	{
		for (int j=i+1; j<n; j++)
		{
			if (arr[i]>arr[j])
			{
				arr[i] += arr[j];
				arr[j] = arr[i] - arr[j];
				arr[i] = arr[i] - arr[j];
			}
		}
	}

	int k = 1;
	for (int i=1; i<n; i++)
	{
		if (arr[i] == arr[i-1])
		{
			k++;
			if (k>n/2)
			{
				cout<<1;
				return 0;
			}
		}
		else
		{
			k = 1;
		}
	}

	cout<<0;

	return 0;
}