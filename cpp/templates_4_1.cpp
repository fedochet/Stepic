#include <cstddef> // size_t

// реализуйте шаблонную функцию array_size,
// которая возвращает значение типа size_t.

// put your code here

template<typename T, size_t S>
size_t array_size(T (&a)[S]){return S;}

int main()
{
	int arr[] = {0,1,3,5};
	array_size(arr);
	return 0;
}