#include <iostream>
#include <vector>
#include <string>

using namespace std;

class uncrossed_groups{

public:
	vector<int> base;

	uncrossed_groups(){};

	// заполняет вектор номерами ячеек, т.е. ссылками на самих себя
	uncrossed_groups(int const &a){
		for (int i = 0; i++; i<a)
			base.push_back(i);
	}

	~uncrossed_groups(){};

};

int main()
{
	return 0;
}