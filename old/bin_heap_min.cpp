#include <iostream>
#include <vector>
#include <string>

using namespace std;

// вершина кучи - максимум

class heap{

	//вектор, в котором будут храниться данные
	vector<long> base;
public:
	
	heap(){
	}

	~heap(){
	}

	//проверка на пустоту
	int is_empty(){
		if (base.size())
			return 0;
		else
			return 1;
	}

	//процедура для рокировки двух элементов вектора
	void swap(int const &first, int const &second){
		long temp 			= base[first];
		base[first] 	= base[second];
		base[second] 	= temp;
	}

	//возвращает номер элемента, являбщегося предком элемента с номером pos
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

	// возвращает позицию, на которой оказался элемент в итоге
	int sift_up(int const &pos){
		if (pos) 								//если не нулевая позиция
			if (base[parent(pos)] > base[pos]) 	//если условие кучи нарушено
			{									//то меняем местами
				swap(pos, parent(pos));
				return sift_up(parent(pos));
			}

		return pos;								//если условие кучи не нарушено или pos=0, то вернуть
	}

	int sift_down(int const &pos){
		if (left(pos) != -1)		//если существует левый предок
			if (right(pos) != -1)	//если существует правый потомок (нам нужно сравнить, что эффективнее)
			{
				if ((base[pos]>base[left(pos)])&&(base[pos]>base[right(pos)]))	//если меньше, чем каждый из потомков
				{	
					if (base[left(pos)]<=base[right(pos)]) //если левый потомок - больше, чем правый, то мы ставим наверх его
					{
						swap(pos, left(pos));
						return sift_down(left(pos));
					}
					else								//иначе -ставим наверх правый
					{
						swap(pos, right(pos));
						return sift_down(right(pos));
					}
				}
				else
				{
					if (base[pos]>base[left(pos)])		// если левый потомок больше
					{
						swap(pos, left(pos));
						return sift_down(left(pos));
					}
					else	
					{	
						if (base[pos]>base[right(pos)])	//если больше только правый
						{
							swap(pos, right(pos));
							return sift_down(right(pos));
						}
						else 							// если условия кучи не нарушены
							return pos;
					}
				}
			}
			else										//если есть только левый, то работаем с ним
			{
				if (base[pos]>base[left(pos)])
				{
					swap(pos, left(pos));
					return sift_down(left(pos));
				}
				else									//если условия кучи не нарушены
					return pos;							
			}

		return pos;									//если лист то вернуть позицию
	}

	int insert(long N)
	{
		base.push_back(N);
		return sift_up(base.size()-1);
	}

	long get_min()
	{
		int result = base[0];
		if (base.size()!=1)
		{
			swap(0,base.size()-1);
			base.pop_back();
			sift_down(0);

		}
		else
		{
			base.pop_back();
		}

		return result;
	}
};

int main()
{

	heap h;
	int n;
	cin>>n;

	for (int i = 0; i<n; i++)
	{
		long curr;
		cin>>curr;
		h.insert(curr);	
	}


	while (!h.is_empty())
	{
		cout<<h.get_min()<<" ";
	}

	return 0;
}