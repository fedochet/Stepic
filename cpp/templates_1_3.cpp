struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

template <typename T>
struct ValueHolder:ICloneable // дальше самостоятельно
{
public:
	T data_;
	ValueHolder(T const &n):data_(n){};
	ValueHolder* clone() const 
	{
		return new ValueHolder<T>(*this);
	}

	~ValueHolder(){};
};

int main()
{
	ValueHolder<int> v(10);
	ICloneable *ptr = v.clone();	

	return 0;
}