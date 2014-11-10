#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int inf = 100001;
// проверка на степень двойки
int isPow2(int a){
  return !(a&(a-1));
}

long get_next_2pow(long x) { 
 //Ищет и возвращает ближайшую к x сверху степень двойки
 //Вообще говоря, предполагает, что число 32-разрядное
 x--;
 for (int p=1; p<32; p<<=1) x |= (x >> p);
 return ++x;
}


long get_prev_2pow(long const &curr){
	long result = get_next_2pow(curr);
	if (result != curr)
		return result/2;
	else
		return result;
}

template <class T>
class tree{

public:
	vector<T> base;
	int size;
	tree(){
		base.resize(0);
		size = 0;
	};

	~tree(){};

	// родитель
	int parent(int const &pos){
		if (pos)
			return (pos-1)/2;
		else
			return -1;
	}

	//левый потомок, в векторе он левее
	int left(int const &pos){
		if (pos*2+1 <= base.size()-1)
			return pos*2+1;
		else
			return -1;
	}

	// правый потомок
	int right(int const &pos){
		if (pos*2+2 <= base.size()-1)
			return pos*2+2;
		else
			return -1;
	}

	int min_of(int left, int right)
	{
		if (left>right)
			return right;
		else
			return left;
	}

	int left_border(int pos){
		int length = size/get_prev_2pow(pos+1);
		return ((pos+1)%get_prev_2pow(pos+1))*length;
	};

	int right_border(int pos){
		int length = size/get_prev_2pow(pos+1);
		return ((pos+1)%get_prev_2pow(pos+1))*length + length - 1;
	};

	void update(int pos){

		if (left(pos)!=-1)
			base[pos] = min_of(base[left(pos)],base[right(pos)]);
		if (parent(pos)!=-1)
			update(parent(pos));
	}

	// позиции относительно изначального массива
	void change(int pos, int new_num){
		int real_pos = size - 1 + pos;
		base[real_pos] =  new_num;
		update(real_pos);
	}

	int get_min(int l, int r, int curr_pos)
	{
		
		if ((r == right_border(curr_pos))&&(l == left_border(curr_pos))) //если границы совпали
			return base[curr_pos];
		else
		{
			if ((left_border(left(curr_pos))<=l)&&(right_border(left(curr_pos))>=r))
				return get_min(l,r,left(curr_pos));

			if ((left_border(right(curr_pos))<=l)&&(right_border(right(curr_pos))>=r))
				return get_min(l,r,right(curr_pos));

			if ((right_border(left(curr_pos))>=l)&&(left_border(right(curr_pos))<=r))
			{
				int left_min 	= get_min(l,right_border(left(curr_pos)),left(curr_pos));
				int right_min 	= get_min(left_border(right(curr_pos)), r, right(curr_pos));
				return min_of(left_min, right_min);
			}
		}
	}

	void init(vector<T> const &inp)
	{
		size = get_next_2pow(inp.size());
		base.resize(2*get_next_2pow(inp.size()) - 1);

		// заполнение начала хуитой
		int i = 0;
		for (;i<base.size()/2; i++)
			base[i] = inf;

		// заполнение самих значений
		for (;i - base.size()/2<inp.size(); i++)
		{
			base[i] = inp[i - base.size()/2];
		}

		// заполнение конца хуитой (если место осталось)
		for (;i<base.size(); i++)
			base[i] = inf;

		// заполнение начала минимумами
		for (i = size-2; i>=0; i--)
		{
			base[i] = min_of(base[left(i)],base[right(i)]);
		}
	}

};

int main()
{
	tree<int> t;
	vector<int> init;

	int n1,n2;
	cin>>n1;
	cin>>n2;

	for (int i = 0; i<n1; i++)
	{
		int temp;
		cin>>temp;
		init.push_back(temp);
	}

	t.init(init);

	for (int i=0; i<n2; i++)
	{
		string s;
		cin>>s;
		if (s == "Min")
		{
			int temp1,temp2;
			cin>>temp1>>temp2;
			cout<<t.get_min(--temp1, --temp2, 0)<<endl;
		}
		else
		{
			int temp1,temp2;
			cin>>temp1>>temp2;
			t.change(--temp1,temp2);
		}
	}

	return 0;
}