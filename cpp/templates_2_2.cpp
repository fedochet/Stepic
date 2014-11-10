#include <cstddef>

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T());
    Array(const Array& other);
    ~Array();
    Array& operator=(Array other);
    void swap(Array &other);
    size_t size() const;
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

private:
    size_t size_;
    T *data_;
};

// put your code here

template<typename T, typename Comp>
T minimum (Array<T> a, Comp f)
{
    T min = a[0];
    for (int i = 0; i<a.size(); i++)
        if (f(min, a[i]))
            min = a[i];
    return min;
}
