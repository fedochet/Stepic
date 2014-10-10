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

	// операция поиска (пока просто)
	int find(int const &k){
		int curr = k;

		while (base[curr]!=curr) 	// пока элемент не указывает сам на себя
			curr = base[curr];		// переходим к его предку

		return curr;
	}

	// операция слияния двух групп
	void unite(int const &l, int const &r){
		base[r] = l;
	}

};

int main()
{
	return 0;
}