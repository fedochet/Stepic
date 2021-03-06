#include <cstddef>
#include <new>
#include <iostream>

using namespace std;

template <typename T>
class Array
{
private:
    size_t size_;
    T* arr_;
    // Список операций:
    //
public:
    Array(size_t size, const T& value = T()):size_(size)
    {
        arr_ = (T*)new char[size_ * sizeof(T)];
    

        for (int i = 0; i<size_; i++)
        {
            new(arr_ + i) T(value);
        }
    }
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    Array():size_(0)
    {       
    }
    //   конструктор класса, который можно вызвать
    //   без параметров. Должен создавать пустой
    //   Array.
    //
    Array(const Array &a):size_(a.size())
    {
        arr_ = (T*) new char[size_ * sizeof(T)];

        for (int i = 0; i<size_; i++)
        {
            new (arr_ + i) T(a[i]);
        }
    }
    //   конструктор копирования, который создает
    //   копию параметра. Для типа T оператор
    //   присвивания не определен.
    //
    ~Array()
    {
        for (int i = 0; i<size_; i++)
        {
            arr_[i].~T();
        }
        if (size_)
            delete [] ((char*)arr_);
    }
    //   деструктор, если он вам необходим.
    //
    Array& operator=(const Array &a)
    {
        //для начала уничтожаем предыдущее
        for (int i = 0; i<size_; i++)
        {
            arr_[i].~T();
        }

        if (size_)
            delete [] ((char*)arr_);
        //заполняем
        size_ = a.size();
        arr_ = (T*)new char[size_ * sizeof(T)];

        for (int i = 0; i<size_; i++)
        {
            new (arr_ + i) T(a[i]);
        }

    }
    //   оператор присваивания.
    //
    size_t size() const
    {
        return size_;
    }
    //   возвращает размер массива (количество
    //                              элемнтов).
    //
    T& operator[](size_t p)
    {
        return arr_[p];
    }

    const T& operator[](size_t p) const
    {
        return arr_[p];
    }
    //   две версии оператора доступа по индексу.
};

int main()
{

    Array<int> A;

    Array<int> C(5,7);

    cout<<"A"<<endl;
    for(int i = 0; i<A.size(); i++)
        cout<<A[i]<<endl;

    Array<int> B(A);

    cout<<"A"<<endl;
    for(int i = 0; i<A.size(); i++)
        cout<<A[i]<<endl;

    cout<<"B"<<endl;
    for(int i = 0; i<B.size(); i++)
        cout<<B[i]<<endl;



    cout<<"B"<<endl;
    for(int i = 0; i<B.size(); i++)
        cout<<B[i]<<endl;

    //A = B;

    cout<<"A"<<endl;
    for(int i = 0; i<A.size(); i++)
        cout<<A[i]<<endl;

    cout<<"Finish!"<<endl;



    return 0;
}