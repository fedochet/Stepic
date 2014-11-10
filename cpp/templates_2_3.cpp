#include <iostream>

// Весь вывод должен осущствляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогаетльные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.

template <typename T>
class Array
{
    int size(){return 0;}
    T& operator[](int p){return 0;}

};

template <typename T>
void flatten(const T &n, std::ostream& out)
{
    out<<n<<" ";
}

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{
    for (int i = 0; i<array.size(); i++)
        flatten(array[i], out);
}

int main()
{
    int i=0;
    return 0;
} 